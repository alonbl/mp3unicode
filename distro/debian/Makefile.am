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

SUFFIXES=.m4
MAINTAINERCLEANFILES = $(srcdir)/Makefile.in
CLEANFILES=copyright

BUILT_SOURCES=copyright

EXTRA_DIST= \
	changelog \
	README.Debian \
	compat \
	control \
	copyright.m4 \
	copyright \
	rules \
	watch \
	mp3unicode.install

.m4:
	$(M4) -Dtop_srcdir="$(top_srcdir)" "$^" > "$@"
