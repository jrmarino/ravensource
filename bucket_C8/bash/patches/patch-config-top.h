--- config-top.h.orig	2018-10-12 19:35:23 UTC
+++ config-top.h
@@ -78,7 +78,7 @@
 #endif
 
 /* Default primary and secondary prompt strings. */
-#define PPROMPT "\\s-\\v\\$ "
+#define PPROMPT "[\\u@\\h \\w]\\$ "
 #define SPROMPT "> "
 
 /* Undefine this if you don't want the ksh-compatible behavior of reprinting
