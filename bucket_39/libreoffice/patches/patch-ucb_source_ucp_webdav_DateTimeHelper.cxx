--- ucb/source/ucp/webdav/DateTimeHelper.cxx.orig	2021-06-04 14:36:10 UTC
+++ ucb/source/ucp/webdav/DateTimeHelper.cxx
@@ -17,6 +17,8 @@
  *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
  */
 
+#include <cstdio>
+
 #include <osl/time.h>
 #include <com/sun/star/util/DateTime.hpp>
 #include "DateTimeHelper.hxx"
