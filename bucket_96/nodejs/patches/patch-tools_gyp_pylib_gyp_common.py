--- tools/gyp/pylib/gyp/common.py.orig	2020-09-29 16:58:15 UTC
+++ tools/gyp/pylib/gyp/common.py
@@ -436,6 +436,8 @@ def GetFlavor(params):
     return 'solaris'
   if sys.platform.startswith(('dragonfly', 'freebsd')):
     return 'freebsd'
+  if sys.platform.startswith('dragon'):
+    return 'freebsd'
   if sys.platform.startswith('openbsd'):
     return 'openbsd'
   if sys.platform.startswith('netbsd'):
