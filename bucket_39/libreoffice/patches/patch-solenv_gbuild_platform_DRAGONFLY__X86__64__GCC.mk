--- solenv/gbuild/platform/DRAGONFLY_X86_64_GCC.mk.orig	2019-01-23 19:35:25 UTC
+++ solenv/gbuild/platform/DRAGONFLY_X86_64_GCC.mk
@@ -11,6 +11,6 @@
 
 include $(GBUILDDIR)/platform/unxgcc.mk
 
-gb_CppunitTest_CPPTESTPRECOMMAND := LD_LIBRARY_PATH=$(WORKDIR)/UnpackedTarball/cppunit/src/cppunit/.libs:/usr/pkg/lib
+gb_CppunitTest_CPPTESTPRECOMMAND := LD_LIBRARY_PATH=$(INSTDIR)/program
 
 # vim: set noet sw=4:
