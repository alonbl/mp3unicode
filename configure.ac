#
# Copyright (c) 2005-2006 Alon Bar-Lev <alon.barlev@gmail.com>
# All rights reserved.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2
# as published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program (see the file COPYING.GPL included with this
# distribution); if not, write to the Free Software Foundation, Inc.,
# 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#

AC_PREREQ([2.60])
AC_INIT([mp3unicode], [1.2])
AM_INIT_AUTOMAKE([${PACKAGE_NAME}], [${PACKAGE_VERSION}])
AM_CONFIG_HEADER([config.h])
AC_CONFIG_SRCDIR([mp3unicode.cpp])

AC_CANONICAL_HOST

AC_ARG_WITH(
	[cygwin-native],
	[AC_HELP_STRING([--with-cygwin-native], [Compile native win32])],
	,
	[with_cygwin_native="no"]
)

test -z "${WIN32}" && WIN32="no"
test -z "${CYGWIN}" && CYGWIN="no"
case "${host}" in
	*-mingw32*)
		WIN32="yes"
	;;
	*-winnt*)
		WIN32="yes"
	;;
	*-cygwin*)
		AC_MSG_CHECKING([cygwin mode to use])
		CYGWIN="yes"
		if test "${with_cygwin_native}" = "yes"; then
			AC_MSG_RESULT([Using native win32])
			CPPFLAGS="${CFLAGS} -mno-cygwin"
			WIN32="yes"
		else
			AC_MSG_RESULT([Using cygwin])
		fi
	;;
	*)
	;;
esac

AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
PKG_PROG_PKG_CONFIG
AC_CHECK_PROGS([M4], [m4])
AC_CHECK_PROGS([XSLTPROC], [xsltproc]) # Required only for svn package

if test "${WIN32}" = "yes"; then
	AC_CHECK_PROGS([MAN2HTML], [man2html])
	test -z "${MAN2HTML}" && AC_MSG_ERROR([man2html is required for win32])
fi

AC_ARG_ENABLE(
	[pedantic],
	[AC_HELP_STRING([--enable-pedantic], [Enable pedantic compiler warnings, will not generate a working executable (debugging option)])],
	,
	[enable_pedantic="no"]
)

PKG_CHECK_MODULES([TAGLIB], [taglib >= 1.4],, [AC_MSG_ERROR([Cannot locate taglib])])
CPPFLAGS="${CPPFLAGS} ${TAGLIB_CFLAGS}"
LIBS="${LIBS} ${TAGLIB_LIBS}"

AC_ARG_VAR([ICONV_CFLAGS], [C compiler flags for iconv])
AC_ARG_VAR([ICONV_LIBS], [linker flags for iconv])
CPPFLAGS="${CPPFLAGS} ${ICONV_CFLAGS}"
LIBS="${LIBS} ${ICONV_LIBS}"

AM_CONDITIONAL([WIN32], [test "${WIN32}" = "yes"])
AC_CONFIG_FILES([
	Makefile
	distro/Makefile
	distro/rpm/Makefile
	distro/rpm/mp3unicode.spec
	distro/debian/Makefile
])
AC_OUTPUT
