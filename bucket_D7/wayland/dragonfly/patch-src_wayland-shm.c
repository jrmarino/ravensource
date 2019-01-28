Index: src/wayland-shm.c
--- src/wayland-shm.c.orig
+++ src/wayland-shm.c
@@ -30,6 +30,12 @@
 
 #define _GNU_SOURCE
 
+#include "../config.h"
+
+#ifdef HAVE_SYS_PARAM_H
+#include <sys/param.h>
+#endif
+
 #include <stdbool.h>
 #include <stdio.h>
 #include <stdlib.h>
@@ -40,6 +46,7 @@
 #include <assert.h>
 #include <signal.h>
 #include <pthread.h>
+#include <errno.h>
 
 #include "wayland-util.h"
 #include "wayland-private.h"
@@ -59,6 +66,9 @@ struct wl_shm_pool {
 	char *data;
 	int32_t size;
 	int32_t new_size;
+#ifdef HAVE_SYS_UCRED_H
+	int fd;
+#endif
 };
 
 struct wl_shm_buffer {
@@ -84,8 +94,25 @@ shm_pool_finish_resize(struct wl_shm_pool *pool)
 	if (pool->size == pool->new_size)
 		return;
 
-	data = mremap(pool->data, pool->size, pool->new_size, MREMAP_MAYMOVE);
+#ifdef HAVE_MREMAP
+ 	data = mremap(pool->data, pool->size, size, MREMAP_MAYMOVE);
+#else
+	int32_t osize = (pool->size + PAGE_SIZE - 1) & ~PAGE_MASK;
+	if (pool->new_size <= osize) {
+		pool->size = pool->new_size;
+		return;
+	}
+	data = mmap(pool->data + osize, pool->new_size - osize, PROT_READ,
+	    MAP_SHARED | MAP_TRYFIXED, pool->fd, osize);
 	if (data == MAP_FAILED) {
+		munmap(pool->data, pool->size);
+		data = mmap(NULL, pool->new_size, PROT_READ, MAP_SHARED, pool->fd, 0);
+	} else {
+		pool->size = pool->new_size;
+		return;
+	}
+#endif
+	if (data == MAP_FAILED) {
 		wl_resource_post_error(pool->resource,
 				       WL_SHM_ERROR_INVALID_FD,
 				       "failed mremap");
@@ -111,6 +138,9 @@ shm_pool_unref(struct wl_shm_pool *pool, bool external
 		return;
 
 	munmap(pool->data, pool->size);
+#ifdef HAVE_SYS_UCRED_H
+	close(pool->fd);
+#endif
 	free(pool);
 }
 
@@ -235,6 +265,8 @@ shm_pool_resize(struct wl_client *client, struct wl_re
 				       "shrinking pool invalid");
 		return;
 	}
+	if (size == pool->size)
+		return;
 
 	pool->new_size = size;
 
@@ -276,21 +308,28 @@ shm_create_pool(struct wl_client *client, struct wl_re
 	pool->external_refcount = 0;
 	pool->size = size;
 	pool->new_size = size;
-	pool->data = mmap(NULL, size,
-			  PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
+	pool->data = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
 	if (pool->data == MAP_FAILED) {
 		wl_resource_post_error(resource,
 				       WL_SHM_ERROR_INVALID_FD,
-				       "failed mmap fd %d: %m", fd);
+				       "failed mmap fd %d: %s", fd,
+				       strerror(errno));
 		goto err_free;
 	}
-	close(fd);
+#ifdef HAVE_SYS_UCRED_H
+	pool->fd = fd;
+#else
+ 	close(fd);
+#endif
 
 	pool->resource =
 		wl_resource_create(client, &wl_shm_pool_interface, 1, id);
 	if (!pool->resource) {
 		wl_client_post_no_memory(client);
 		munmap(pool->data, pool->size);
+#ifdef HAVE_SYS_UCRED_H
+		close(fd);
+#endif
 		free(pool);
 		return;
 	}
@@ -495,13 +534,22 @@ sigbus_handler(int signum, siginfo_t *info, void *cont
 	sigbus_data->fallback_mapping_used = 1;
 
 	/* This should replace the previous mapping */
+#ifdef HAVE_SYS_UCRED_H
 	if (mmap(pool->data, pool->size,
+		 PROT_READ, MAP_PRIVATE | MAP_FIXED | MAP_ANON,
+		 0, 0) == MAP_FAILED) {
+		reraise_sigbus();
+		return;
+	}
+#else
+	if (mmap(pool->data, pool->size,
 		 PROT_READ | PROT_WRITE,
 		 MAP_PRIVATE | MAP_FIXED | MAP_ANONYMOUS,
 		 0, 0) == (void *) -1) {
 		reraise_sigbus();
 		return;
 	}
+#endif
 }
 
 static void
