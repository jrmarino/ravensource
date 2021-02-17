--- Modules/FindSDL.cmake.orig	2021-02-15 16:48:33 UTC
+++ Modules/FindSDL.cmake
@@ -116,6 +116,11 @@ else()
   set(VC_LIB_PATH_SUFFIX lib/x86)
 endif()
 
+# On FreeBSD SDL depends on libiconv and SDL_stdinc.h includes iconv.h, which is
+# located in ${LOCALBASE}/include. Append {LOCALBASE}/include to
+# the SDL_INCLUDE_DIR, thus allow to build SDL apps out of box.
+list(APPEND SDL_INCLUDE_DIR /usr/local/include)
+
 # SDL-1.1 is the name used by FreeBSD ports...
 # don't confuse it for the version number.
 find_library(SDL_LIBRARY_TEMP
