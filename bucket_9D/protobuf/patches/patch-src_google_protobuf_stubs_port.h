--- ../src/google/protobuf/stubs/port.h.orig	2021-02-18 19:50:15 UTC
+++ ../src/google/protobuf/stubs/port.h
@@ -60,7 +60,11 @@
 #ifdef __APPLE__
 #include <machine/endian.h>  // __BYTE_ORDER
 #else
+# if defined(__DragonFly__) || defined(__FreeBSD__)
+#include <sys/endian.h>
+# else
 #include <endian.h>  // __BYTE_ORDER
+# endif
 #endif
 #if ((defined(__LITTLE_ENDIAN__) && !defined(__BIG_ENDIAN__)) ||   \
      (defined(__BYTE_ORDER) && __BYTE_ORDER == __LITTLE_ENDIAN) || \
