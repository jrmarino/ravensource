--- inflate.c.orig	2008-07-30 01:31:08 UTC
+++ inflate.c
@@ -473,7 +473,11 @@ int UZinflate(__G__ is_defl64)
                     retval = 2;
                 } else {
                     /* output write failure */
+#ifdef FUNZIP
+                    retval = PK_DISK;
+#else
                     retval = (G.disk_full != 0 ? PK_DISK : IZ_CTRLC);
+#endif
                 }
             } else {
                 Trace((stderr, "oops!  (inflateBack9() err = %d)\n", err));
@@ -538,7 +542,11 @@ int UZinflate(__G__ is_defl64)
                     retval = 2;
                 } else {
                     /* output write failure */
+#ifdef FUNZIP
+                    retval = PK_DISK;
+#else
                     retval = (G.disk_full != 0 ? PK_DISK : IZ_CTRLC);
+#endif
                 }
             } else {
                 Trace((stderr, "oops!  (inflateBack() err = %d)\n", err));
