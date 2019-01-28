Index: tests/test-runner.c
--- tests/test-runner.c.orig
+++ tests/test-runner.c
@@ -25,9 +25,16 @@
 
 #define _GNU_SOURCE
 
+#include "../config.h"
+
+#ifdef HAVE_SYS_PARAM_H
+#include <sys/param.h>
+#endif
+
 #include <unistd.h>
 #include <stdio.h>
 #include <stdlib.h>
+#include <signal.h>
 #include <sys/types.h>
 #include <sys/wait.h>
 #include <sys/stat.h>
@@ -37,7 +44,9 @@
 #include <errno.h>
 #include <limits.h>
 #include <sys/ptrace.h>
+#ifdef HAVE_SYS_PRCTL_H
 #include <sys/prctl.h>
+#endif
 #ifndef PR_SET_PTRACER
 # define PR_SET_PTRACER 0x59616d61
 #endif
@@ -45,11 +54,20 @@
 #include "test-runner.h"
 
 static int num_alloc;
+
+extern const struct test __start_test_section, __stop_test_section;
+
 static void* (*sys_malloc)(size_t);
 static void (*sys_free)(void*);
 static void* (*sys_realloc)(void*, size_t);
 static void* (*sys_calloc)(size_t, size_t);
 
+#ifndef __linux__
+#define PTRACE_ATTACH PT_ATTACH
+#define PTRACE_CONT PT_CONTINUE
+#define PTRACE_DETACH PT_DETACH
+#endif
+
 /* when set to 1, check if tests are not leaking memory and opened files.
  * It is turned on by default. It can be turned off by
  * WAYLAND_TEST_NO_LEAK_CHECK environment variable. */
@@ -282,6 +300,10 @@ stderr_reset_color(void)
 static int
 is_debugger_attached(void)
 {
+#ifdef __OpenBSD__
+	/* OpenBSD doesn't allow to trace parent process */
+	return 0;
+#else
 	int status;
 	int rc;
 	pid_t pid;
@@ -312,13 +334,14 @@ is_debugger_attached(void)
 			_exit(1);
 		if (!waitpid(-1, NULL, 0))
 			_exit(1);
-		ptrace(PTRACE_CONT, NULL, NULL);
+		ptrace(PTRACE_CONT, ppid, NULL, NULL);
 		ptrace(PTRACE_DETACH, ppid, NULL, NULL);
 		_exit(0);
 	} else {
 		close(pipefd[0]);
 
 		/* Enable child to ptrace the parent process */
+#ifdef HAVE_SYS_PRCTL_H
 		rc = prctl(PR_SET_PTRACER, pid);
 		if (rc != 0 && errno != EINVAL) {
 			/* An error prevents us from telling if a debugger is attached.
@@ -332,6 +355,7 @@ is_debugger_attached(void)
 			/* Signal to client that parent is ready by passing '+' */
 			write(pipefd[1], "+", 1);
 		}
+#endif
 		close(pipefd[1]);
 
 		waitpid(pid, &status, 0);
@@ -339,6 +363,7 @@ is_debugger_attached(void)
 	}
 
 	return rc;
+#endif
 }
 
 int main(int argc, char *argv[])
@@ -346,7 +371,11 @@ int main(int argc, char *argv[])
 	const struct test *t;
 	pid_t pid;
 	int total, pass;
+#ifdef HAVE_WAITID
 	siginfo_t info;
+#else
+	int status;
+#endif
 
 	/* Load system malloc, free, and realloc */
 	sys_calloc = dlsym(RTLD_NEXT, "calloc");
@@ -395,6 +424,7 @@ int main(int argc, char *argv[])
 		if (pid == 0)
 			run_test(t); /* never returns */
 
+#ifdef HAVE_WAITID
 		if (waitid(P_PID, pid, &info, WEXITED)) {
 			stderr_set_color(RED);
 			fprintf(stderr, "waitid failed: %m\n");
@@ -426,6 +456,26 @@ int main(int argc, char *argv[])
 
 			break;
 		}
+#else
+		if (wait(&status)) {
+			fprintf(stderr, "waitid failed: %m\n");
+			abort();
+		}
+
+		fprintf(stderr, "test \"%s\":\t", t->name);
+		if (WIFEXITED(status)) {
+			fprintf(stderr, "exit status %d", WEXITSTATUS(status));
+			if (WEXITSTATUS(status) == EXIT_SUCCESS)
+				success = 1;
+			break;
+		} else if (WIFSIGNALED(status) || WCOREDUMP(status)) {
+			fprintf(stderr, "signal %d", WTERMSIG(status));
+			break;
+		}
+#endif
+
+		if (t->must_fail)
+			success = !success;
 
 		if (success) {
 			pass++;
