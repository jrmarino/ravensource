--- Source/cmSystemTools.cxx.orig	2021-01-28 15:28:45 UTC
+++ Source/cmSystemTools.cxx
@@ -6,6 +6,7 @@
 #  define _POSIX_C_SOURCE 200809L
 #endif
 #if defined(__OpenBSD__) || defined(__FreeBSD__) || defined(__NetBSD__) ||    \
+  defined(__DragonFly__) || \
   defined(__QNX__)
 // For isascii
 #  define _XOPEN_SOURCE 700
