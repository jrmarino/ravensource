--- libguile/gen-scmconfig.c.orig	2016-06-17 09:37:10 UTC
+++ libguile/gen-scmconfig.c
@@ -138,6 +138,9 @@
 
 #include <libguile/gen-scmconfig.h>
 
+#if defined __FreeBSD__ || defined __DragonFly__
+#define _ANSI_SOURCE
+#endif
 #include <stdio.h>
 #include <string.h>
 
