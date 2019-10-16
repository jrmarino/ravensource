--- cmake/ssl.cmake.orig	2019-09-20 08:30:51 UTC
+++ cmake/ssl.cmake
@@ -220,7 +220,7 @@ MACRO (MYSQL_CHECK_SSL)
     IF(OPENSSL_INCLUDE_DIR AND
        OPENSSL_LIBRARY   AND
        CRYPTO_LIBRARY      AND
-       OPENSSL_MAJOR_VERSION STREQUAL "1"
+       (OPENSSL_MAJOR_VERSION STREQUAL "1" OR OPENSSL_MAJOR_VERSION STREQUAL "2")
       )
       SET(OPENSSL_FOUND TRUE)
       FIND_PROGRAM(OPENSSL_EXECUTABLE openssl
@@ -305,7 +305,7 @@ ENDMACRO()
 # then copy the dlls to runtime_output_directory, and add INSTALL them.
 # Currently only relevant for Windows, Mac and Linux.
 MACRO(MYSQL_CHECK_SSL_DLLS)
-  IF (WITH_SSL_PATH AND (APPLE OR WIN32 OR LINUX_STANDALONE))
+  IF (FALSE)
     MESSAGE(STATUS "WITH_SSL_PATH ${WITH_SSL_PATH}")
     IF(LINUX_STANDALONE)
       GET_FILENAME_COMPONENT(CRYPTO_EXT "${CRYPTO_LIBRARY}" EXT)
