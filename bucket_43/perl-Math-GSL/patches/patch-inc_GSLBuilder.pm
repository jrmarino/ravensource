--- inc/GSLBuilder.pm.orig	2018-12-10 17:11:25 UTC
+++ inc/GSLBuilder.pm
@@ -31,6 +31,8 @@ sub process_swig_files {
     my $swig_flags      = $self->{properties}->{swig_flags};
     my $swig_version    = $self->{properties}->{swig_version};
 
+    push @$gsl_ldflags, ("@EXT1@", "@EXT2@");
+
     if ($binding_ver ne $current_version) {
         print "VERSION MISMATCH: Let's hope for the best.\n";
     }
@@ -262,7 +264,7 @@ sub link_c {
       }
     }
 
-    my @lddlflags = $self->split_like_shell($cf->{lddlflags});
+    my @lddlflags = $self->split_like_shell($Config{lddlflags});
     my @shrp      = $self->split_like_shell($cf->{shrpenv});
     my @ld        = $self->split_like_shell($cf->{ld} || $Config{cc});
 
@@ -294,7 +296,7 @@ sub compile_c {
 
   $cf->{installarchlib} = $Config{archlib};
 
-  my @include_dirs = @{$p->{include_dirs}}
+  my @include_dirs = ( @{$p->{include_dirs}} && ( ${@{$p->{include_dirs}}}[0] ne "" ) )
 			? map {"-I$_"} (@{$p->{include_dirs}}, catdir($cf->{installarchlib}, 'CORE'))
 			: map {"-I$_"} ( catdir($cf->{installarchlib}, 'CORE') ) ;
 
