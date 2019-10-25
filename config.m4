dnl config.m4 for extension morton

PHP_ARG_ENABLE(morton, whether to enable morton support,
[  --enable-morton          Enable morton support], no)

if test "$PHP_MORTON" != "no"; then
  EXTRA_CFLAGS="-mbmi2"

  AC_DEFINE(HAVE_MORTON, 1, [ Have morton support ])

  PHP_NEW_EXTENSION(morton, morton.c, $ext_shared)

  PHP_SUBST(EXTRA_CFLAGS)

  PHP_ADD_MAKEFILE_FRAGMENT
fi
