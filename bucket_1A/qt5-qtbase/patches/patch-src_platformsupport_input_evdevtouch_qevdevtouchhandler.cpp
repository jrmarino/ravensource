--- src/platformsupport/input/evdevtouch/qevdevtouchhandler.cpp.orig	2020-09-02 10:15:07 UTC
+++ src/platformsupport/input/evdevtouch/qevdevtouchhandler.cpp
@@ -52,11 +52,7 @@
 
 #include <mutex>
 
-#ifdef Q_OS_FREEBSD
-#include <dev/evdev/input.h>
-#else
 #include <linux/input.h>
-#endif
 
 #ifndef input_event_sec
 #define input_event_sec time.tv_sec
