# work-around for https://bugs.freedesktop.org/show_bug.cgi?id=100627
#
--- src/glx/glxext.c.orig	2021-06-30 18:18:55 UTC
+++ src/glx/glxext.c
@@ -925,6 +925,9 @@ __glXInitialize(Display * dpy)
 #if defined(GLX_USE_DRM)
    if (glx_direct && glx_accel) {
 #if defined(HAVE_DRI3)
+#if (defined(__FreeBSD__) || defined(__FreeBSD_kernel__)) && !defined(__DRM_NEXT__)
+      if (env_var_as_boolean("LIBGL_DRI3_ENABLE", false))
+#endif
       if (!env_var_as_boolean("LIBGL_DRI3_DISABLE", false))
          dpyPriv->dri3Display = dri3_create_display(dpy);
 #endif /* HAVE_DRI3 */
