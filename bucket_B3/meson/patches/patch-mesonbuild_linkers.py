--- mesonbuild/linkers.py.orig	2021-06-07 17:35:22 UTC
+++ mesonbuild/linkers.py
@@ -1256,7 +1256,12 @@ class SolarisDynamicLinker(PosixDynamicL
     def get_link_whole_for(self, args: T.List[str]) -> T.List[str]:
         if not args:
             return args
-        return self._apply_prefix('--whole-archive') + args + self._apply_prefix('--no-whole-archive')
+        result = [self.prefix_arg + '-z', self.prefix_arg + 'allextract']
+        for a in args:
+            result.append(a)
+        result.append(self.prefix_arg + '-z')
+        result.append(self.prefix_arg + 'defaultextract')
+        return result
 
     def get_pie_args(self) -> T.List[str]:
         # Available in Solaris 11.2 and later
