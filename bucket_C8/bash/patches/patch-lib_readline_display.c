--- lib/readline/display.c.orig	2020-09-08 12:56:42 UTC
+++ lib/readline/display.c
@@ -932,7 +932,10 @@ rl_redisplay (void)
      the line breaks in the prompt string in expand_prompt, taking invisible
      characters into account, and if lpos exceeds the screen width, we copy
      the data in the loop below. */
+  if (local_prompt)
   lpos = prompt_physical_chars + modmark;
+  else
+    lpos = 0;
 
 #if defined (HANDLE_MULTIBYTE)
   memset (line_state_invisible->wrapped_line, 0, line_state_invisible->wbsize * sizeof (int));
