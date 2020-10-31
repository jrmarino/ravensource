--- src/util/u_thread.h.orig	2020-10-14 18:34:53 UTC
+++ src/util/u_thread.h
@@ -37,6 +37,7 @@
 #include <signal.h>
 #ifdef HAVE_PTHREAD_NP_H
 #include <pthread_np.h>
+#undef ALIGN
 #endif
 #endif
 
@@ -77,9 +78,9 @@ static inline thrd_t u_thread_create(int
 static inline void u_thread_setname( const char *name )
 {
 #if defined(HAVE_PTHREAD)
-#if DETECT_OS_LINUX || DETECT_OS_CYGWIN || DETECT_OS_SOLARIS
+#if DETECT_OS_LINUX || DETECT_OS_CYGWIN
    pthread_setname_np(pthread_self(), name);
-#elif DETECT_OS_FREEBSD || DETECT_OS_OPENBSD
+#elif DETECT_OS_FREEBSD || DETECT_OS_OPENBSD || DETECT_OS_DRAGONFLY
    pthread_set_name_np(pthread_self(), name);
 #elif DETECT_OS_NETBSD
    pthread_setname_np(pthread_self(), "%s", (void *)name);
@@ -87,8 +88,6 @@ static inline void u_thread_setname( con
    pthread_setname_np(name);
 #elif DETECT_OS_HAIKU
    rename_thread(find_thread(NULL), name);
-#else
-#warning Not sure how to call pthread_setname_np
 #endif
 #endif
    (void)name;
@@ -159,7 +158,7 @@ util_get_L3_for_pinned_thread(thrd_t thr
 static inline int64_t
 u_thread_get_time_nano(thrd_t thread)
 {
-#if defined(HAVE_PTHREAD) && !defined(__APPLE__) && !defined(__HAIKU__)
+#if defined(HAVE_PTHREAD) && !defined(__APPLE__) && !defined(__HAIKU__) && !defined(__sun)
    struct timespec ts;
    clockid_t cid;
 
