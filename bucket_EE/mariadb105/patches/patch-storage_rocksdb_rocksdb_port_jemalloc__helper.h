--- storage/rocksdb/rocksdb/port/jemalloc_helper.h.orig	2021-05-05 21:00:21 UTC
+++ storage/rocksdb/rocksdb/port/jemalloc_helper.h
@@ -26,6 +26,10 @@
 #include <jemalloc/jemalloc.h>
 #endif
 
+#ifdef __FreeBSD__
+#define JEMALLOC_USABLE_SIZE_CONST const
+#endif
+
 #ifndef JEMALLOC_CXX_THROW
 #define JEMALLOC_CXX_THROW
 #endif