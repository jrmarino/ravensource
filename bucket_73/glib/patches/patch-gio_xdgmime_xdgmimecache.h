--- gio/xdgmime/xdgmimecache.h.orig	2020-05-20 10:46:43 UTC
+++ gio/xdgmime/xdgmimecache.h
@@ -44,6 +44,9 @@ typedef struct _XdgMimeCache XdgMimeCach
 #define _xdg_mime_cache_get_icon                      XDG_RESERVED_ENTRY(cache_get_icon)
 #define _xdg_mime_cache_get_generic_icon              XDG_RESERVED_ENTRY(cache_get_generic_icon)
 #define _xdg_mime_cache_glob_dump                     XDG_RESERVED_ENTRY(cache_glob_dump)
+#define _xdg_mime_cache_is_valid_mime_type            XDG_RESERVED_ENTRY(cache_is_valid_mime_type)
+#define _xdg_mime_cache_mime_type_equal               XDG_RESERVED_ENTRY(cache_mime_type_equal)
+#define _xdg_mime_cache_media_type_equal              XDG_RESERVED_ENTRY(cache_media_type_equal)
 #endif
 
 extern XdgMimeCache **_caches;
