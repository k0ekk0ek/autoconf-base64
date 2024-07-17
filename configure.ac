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

AC_CHECK_HEADERS([stddef.h, stdint.h])

# GCC and Clang
AX_CHECK_COMPILE_FLAG([-MMD],DEPFLAGS="-MMD -MP")
# Oracle Developer Studio (no -MP)
AX_CHECK_COMPILE_FLAG([-xMMD],DEPFLAGS="-xMMD")

AC_SUBST([DEPFLAGS])

AC_CANONICAL_TARGET

AC_CHECK_HEADERS([resolv.h])

# Check if b64_pton and b64_pton are declared.dd
AC_CHECK_DECLS([b64_pton, b64_ntop],,,[[#include <resolv.h>]])

# b64_pton and b64_ntop are typically defined to __b64_pton and __b64_ntop.
# b64_* symbols are not likely to exist, search for __b64_* symbols if that
# is the case. __b64_* symbols may reside in libresolv (Linux) or libc (BSDs).
AC_SEARCH_LIBS([b64_pton],[resolv],,[
  AC_SEARCH_LIBS([__b64_pton],[resolv],,[AC_LIBOBJ(b64_pton)])
])

AC_SEARCH_LIBS([b64_ntop],[resolv],,[
  AC_SEARCH_LIBS([__b64_ntop],[resolv],,[AC_LIBOBJ(b64_ntop)])
])

AC_SUBST([HAVE_DECL_B64_PTON])
AC_SUBST([HAVE_DECL_B64_NTOP])

AH_BOTTOM([
#include <stddef.h>
#ifdef HAVE_STDINT_H
# include <stdint.h>
#endif

#ifdef HAVE_RESOLV_H
# include <resolv.h>
#endif

#ifndef HAVE_DECL_B64_NTOP
int b64_ntop(uint8_t const *src, size_t srclength,
	     char *target, size_t targsize);
#endif /* !HAVE_B64_NTOP */
#ifndef HAVE_DECL_B64_PTON
int b64_pton(char const *src, uint8_t *target, size_t targsize);
#endif /* !HAVE_B64_PTON */
])

AC_OUTPUT
