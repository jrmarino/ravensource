Index: tests/test-compositor.c
--- tests/test-compositor.c.orig
+++ tests/test-compositor.c
@@ -86,8 +86,8 @@ get_socket_name(void)
 	static char retval[64];
 
 	gettimeofday(&tv, NULL);
-	snprintf(retval, sizeof retval, "wayland-test-%d-%ld%ld",
-		 getpid(), tv.tv_sec, tv.tv_usec);
+	snprintf(retval, sizeof retval, "wayland-test-%d-%lld%lld",
+		 getpid(), (long long)tv.tv_sec, (long long)tv.tv_usec);
 
 	return retval;
 }
@@ -97,10 +97,15 @@ handle_client_destroy(void *data)
 {
 	struct client_info *ci = data;
 	struct display *d;
+#ifdef HAVE_WAITID
 	siginfo_t status;
+#else
+	int status;
+#endif
 
 	d = ci->display;
 
+#ifdef HAVE_WAITID
 	assert(waitid(P_PID, ci->pid, &status, WEXITED) != -1);
 
 	switch (status.si_code) {
@@ -118,6 +123,20 @@ handle_client_destroy(void *data)
 		ci->exit_code = status.si_status;
 		break;
 	}
+#else
+	assert(waitpid(ci->pid, &status, 0) != -1);
+
+	if (WIFEXITED(status)) {
+		if (WEXITSTATUS(status) != EXIT_SUCCESS)
+			fprintf(stderr, "Client '%s' exited with code %d\n",
+				ci->name, WEXITSTATUS(status));
+		ci->exit_code = WEXITSTATUS(status);
+	} else if (WIFSIGNALED(status) || WCOREDUMP(status)) {
+		fprintf(stderr, "Client '%s' was killed by signal %d\n",
+			ci->name, WTERMSIG(status));
+		ci->exit_code = WEXITSTATUS(status);
+	}
+#endif
 
 	++d->clients_terminated_no;
 	if (d->clients_no == d->clients_terminated_no) {
