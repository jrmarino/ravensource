--- lib/util.c.orig	2021-05-10 04:34:24 UTC
+++ lib/util.c
@@ -1035,6 +1035,7 @@ EXPORTED int parsehex(const char *p, con
 
 /* buffer handling functions */
 
+#undef roundup
 #ifdef HAVE_DECLARE_OPTIMIZE
 static inline size_t roundup(size_t size)
     __attribute__((pure, always_inline, optimize("-O3")));
