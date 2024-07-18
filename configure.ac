#
# configure.ac -- Autoconf script for b64_pton checks in configure
#
# Copyright (c) 2022-2023, NLnet Labs. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

AC_INIT([b64],[0.1.0])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])

m4_include(m4/ax_check_compile_flag.m4)
m4_version_prereq([2.70], [AC_PROG_CC], [AC_PROG_CC_STDC])

AC_CHECK_HEADERS([stddef.h stdint.h])

# GCC and Clang
AX_CHECK_COMPILE_FLAG([-MMD],DEPFLAGS="-MMD -MP")
# Oracle Developer Studio (no -MP)
AX_CHECK_COMPILE_FLAG([-xMMD],DEPFLAGS="-xMMD")

AC_SUBST([DEPFLAGS])

AC_CANONICAL_TARGET


define([INCLUDES_BASE64],[
AC_INCLUDES_DEFAULT
#ifdef HAVE_NETINET_IN_H
# include <netinet/in.h>
#endif
#ifdef HAVE_RESOLV_H
# include <resolv.h>
#endif
])

AC_CHECK_HEADERS([netinet/in.h]) # needed to check for resolv.h on FreeBSD
AC_CHECK_HEADERS([resolv.h],,,[INCLUDES_BASE64])


# b64_pton and b64_ntop are typically defined to __b64_pton and __b64_ntop.
# b64_* symbols are not likely to exist, search for __b64_* symbols if that
# is the case. __b64_* symbols may reside in libresolv (Linux) or libc (BSDs).
AC_SEARCH_LIBS([b64_ntop],[resolv],[
  AC_CHECK_DECLS([b64_ntop],,,[INCLUDES_BASE64])],[
  AC_SEARCH_LIBS([__b64_ntop],[resolv],[
    AC_CHECK_DECLS([__b64_ntop],,,[INCLUDES_BASE64])],[AC_LIBOBJ(b64_ntop)])
])

AC_SEARCH_LIBS([b64_pton],[resolv],[
  AC_CHECK_DECLS([b64_pton],,,[INCLUDES_BASE64])],[
  AC_SEARCH_LIBS([__b64_pton],[resolv],[
    AC_CHECK_DECLS([__b64_pton],,,[INCLUDES_BASE64])],[AC_LIBOBJ(b64_pton)])
])

AC_SUBST([HAVE_B64_PTON])
AC_SUBST([HAVE_B64_NTOP])
AC_SUBST([HAVE_DECL_B64_PTON])
AC_SUBST([HAVE_DECL___B64_PTON])
AC_SUBST([HAVE_DECL_B64_NTOP])
AC_SUBST([HAVE_DECL___B64_NTOP])

AH_BOTTOM([
#ifdef HAVE_NETINET_IN_H
# include <netinet/in.h>
#endif
#ifdef HAVE_RESOLV_H
# include <resolv.h>
#endif

#if !HAVE_DECL_B64_NTOP
# if HAVE_DECL___B64_NTOP
#   define b64_ntop __b64_ntop
# else
int b64_ntop(uint8_t const *src, size_t srclength,
	     char *target, size_t targsize);
# endif
#endif

#if !HAVE_DECL_B64_PTON
# if HAVE_DECL___B64_PTON
#   define b64_pton __b64_pton
# else
int b64_pton(char const *src, uint8_t *target, size_t targsize);
# endif
#endif
])

AC_OUTPUT
