diff --git src/wayland-server.c src/wayland-server.c
index eae8d2e..78af4f0 100644
--- src/wayland-server.c
+++ src/wayland-server.c
@@ -25,6 +25,13 @@
 
 #define _GNU_SOURCE
 
+#include "../config.h"
+
+#ifdef HAVE_SYS_UCRED_H
+#include <sys/types.h>
+#include <sys/ucred.h>
+#endif
+
 #include <stdlib.h>
 #include <stdint.h>
 #include <stddef.h>
@@ -77,7 +84,11 @@ struct wl_client {
 	struct wl_list link;
 	struct wl_map objects;
 	struct wl_priv_signal destroy_signal;
+#ifdef HAVE_SYS_UCRED_H
+	struct xucred xucred;
+#else
 	struct ucred ucred;
+#endif
 	int error;
 	struct wl_priv_signal resource_created_signal;
 };
@@ -303,7 +314,11 @@ wl_resource_post_error(struct wl_resource *resource,
 static void
 destroy_client_with_error(struct wl_client *client, const char *reason)
 {
+#ifdef HAVE_SYS_UCRED_H
+	wl_log("%s (uid %u)\n", reason, client->xucred.cr_uid);
+#else
 	wl_log("%s (pid %u)\n", reason, client->ucred.pid);
+#endif
 	wl_client_destroy(client);
 }
 
@@ -517,9 +532,19 @@ wl_client_create(struct wl_display *display, int fd)
 	if (!client->source)
 		goto err_client;
 
+#ifndef __DragonFly__
+# ifdef HAVE_SYS_UCRED_H
+	len = sizeof client->xucred;
+# else
 	len = sizeof client->ucred;
+# endif
 	if (getsockopt(fd, SOL_SOCKET, SO_PEERCRED,
+# ifdef HAVE_SYS_UCRED_H
+		       &client->xucred, &len) < 0)
+# else
 		       &client->ucred, &len) < 0)
+# endif
+#endif
 		goto err_source;
 
 	client->connection = wl_connection_create(fd);
@@ -574,12 +599,21 @@ WL_EXPORT void
 wl_client_get_credentials(struct wl_client *client,
 			  pid_t *pid, uid_t *uid, gid_t *gid)
 {
+#ifdef HAVE_SYS_UCRED_H
+	if (pid)
+		*pid = 0;
+	if (uid)
+		*uid = client->xucred.cr_uid;
+	if (gid)
+		*gid = client->xucred.cr_gid;
+#else
 	if (pid)
 		*pid = client->ucred.pid;
 	if (uid)
 		*uid = client->ucred.uid;
 	if (gid)
 		*gid = client->ucred.gid;
+#endif
 }
 
 /** Get the file descriptor for the client
@@ -1329,7 +1363,7 @@ socket_data(int fd, uint32_t mask, void *data)
 	client_fd = wl_os_accept_cloexec(fd, (struct sockaddr *) &name,
 					 &length);
 	if (client_fd < 0)
-		wl_log("failed to accept: %m\n");
+		wl_log("failed to accept: %s\n", strerror(errno));
 	else
 		if (!wl_client_create(display, client_fd))
 			close(client_fd);
@@ -1434,12 +1468,12 @@ _wl_display_add_socket(struct wl_display *display, struct wl_socket *s)
 
 	size = offsetof (struct sockaddr_un, sun_path) + strlen(s->addr.sun_path);
 	if (bind(s->fd, (struct sockaddr *) &s->addr, size) < 0) {
-		wl_log("bind() failed with error: %m\n");
+		wl_log("bind() failed with error: %s\n", strerror(errno));
 		return -1;
 	}
 
 	if (listen(s->fd, 128) < 0) {
-		wl_log("listen() failed with error: %m\n");
+		wl_log("listen() failed with error: %s\n", strerror(errno));
 		return -1;
 	}
 
