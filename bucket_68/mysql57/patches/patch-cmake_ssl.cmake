--- cmake/ssl.cmake.orig	2020-12-10 03:01:55 UTC
+++ cmake/ssl.cmake
@@ -193,17 +193,10 @@ MACRO (MYSQL_CHECK_SSL)
       )
     SET(OPENSSL_VERSION ${OPENSSL_VERSION} CACHE INTERNAL "")
 
-    IF("${OPENSSL_VERSION}" VERSION_GREATER "1.1.0")
-       ADD_DEFINITIONS(-DHAVE_TLSv13)
-       SET(HAVE_TLSv13 1)
-       IF(SOLARIS)
-         SET(FORCE_SSL_SOLARIS "-Wl,--undefined,address_of_sk_new_null")
-       ENDIF()
-    ENDIF()
     IF(OPENSSL_INCLUDE_DIR AND
        OPENSSL_LIBRARY   AND
        CRYPTO_LIBRARY      AND
-       OPENSSL_MAJOR_VERSION STREQUAL "1"
+       OPENSSL_MAJOR_VERSION VERSION_GREATER_EQUAL "1"
       )
       SET(OPENSSL_FOUND TRUE)
     ELSE()
