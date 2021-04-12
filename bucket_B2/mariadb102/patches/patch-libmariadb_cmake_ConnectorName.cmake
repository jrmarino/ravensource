--- libmariadb/cmake/ConnectorName.cmake.orig	2021-02-18 18:07:53 UTC
+++ libmariadb/cmake/ConnectorName.cmake
@@ -22,7 +22,7 @@ IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
     SET(MACHINE_NAME "x64")
   ELSE()
     SET(MACHINE_NAME "32")
-  END()
+  ENDIF()
 ENDIF()
 
 SET(product_name "mysql-connector-c-${CPACK_PACKAGE_VERSION}-${PLATFORM_NAME}${CONCAT_SIGN}${MACHINE_NAME}")
