--- ext/readline/extconf.rb.orig	2020-10-01 12:15:38 UTC
+++ ext/readline/extconf.rb
@@ -32,6 +32,7 @@ enable_libedit = enable_config("libedit"
 
 have_library("user32", nil) if /cygwin/ === RUBY_PLATFORM
 have_library("ncurses", "tgetnum") ||
+  have_library("tinfo", "tgetnum") ||
   have_library("termcap", "tgetnum") ||
   have_library("curses", "tgetnum")
 