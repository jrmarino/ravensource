--- erts/aclocal.m4.orig	2021-02-04 11:14:58 UTC
+++ erts/aclocal.m4
@@ -3055,7 +3055,7 @@ case $host_os in
 			DED_LDFLAGS="-m32 $DED_LDFLAGS"
 		fi
 	;;	
-	freebsd*)
+	freebsd*|dragonfly*)
 		DED_LD="$CC"
 		DED_LD_FLAG_RUNTIME_LIBRARY_PATH="$CFLAG_RUNTIME_LIBRARY_PATH"
 		DED_LDFLAGS="-shared"
