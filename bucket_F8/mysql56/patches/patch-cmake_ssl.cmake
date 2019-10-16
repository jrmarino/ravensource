--- cmake/ssl.cmake.orig	2019-09-27 07:04:56 UTC
+++ cmake/ssl.cmake
@@ -189,13 +189,10 @@ MACRO (MYSQL_CHECK_SSL)
         OPENSSL_FIX_VERSION "${OPENSSL_VERSION_NUMBER}"
         )
     ENDIF()
-    IF("${OPENSSL_MAJOR_VERSION}.${OPENSSL_MINOR_VERSION}.${OPENSSL_FIX_VERSION}" VERSION_GREATER "1.1.0")
-       ADD_DEFINITIONS(-DHAVE_TLSv13)
-    ENDIF()
     IF(OPENSSL_INCLUDE_DIR AND
        OPENSSL_LIBRARY   AND
        CRYPTO_LIBRARY      AND
-       OPENSSL_MAJOR_VERSION STREQUAL "1"
+       OPENSSL_MAJOR_VERSION VERSION_GREATER_EQUAL "1"
       )
       SET(OPENSSL_FOUND TRUE)
     ELSE()
