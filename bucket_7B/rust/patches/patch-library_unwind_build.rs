--- library/unwind/build.rs.orig	2021-05-09 02:52:39 UTC
+++ library/unwind/build.rs
@@ -35,7 +35,7 @@ fn main() {
     } else if target.contains("illumos") {
         println!("cargo:rustc-link-lib=gcc_s");
     } else if target.contains("dragonfly") {
-        println!("cargo:rustc-link-lib=gcc_pic");
+        println!("cargo:rustc-link-lib=gcc_s");
     } else if target.contains("pc-windows-gnu") {
         // This is handled in the target spec with late_link_args_[static|dynamic]
     } else if target.contains("uwp-windows-gnu") {
