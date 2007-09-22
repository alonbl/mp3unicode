#
# Copyright (c) 2005-2007 Alon Bar-Lev <alon.barlev@gmail.com>
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

# This option prevents autoreconf from overriding our COPYING and
# INSTALL targets:
AUTOMAKE_OPTIONS=foreign dist-bzip2

BUILT_SOURCES=ChangeLog
DISTCLEANFILES=ChangeLog
EXTRA_DIST=ChangeLog ChangeLog.xsl releases.xml

ChangeLog:	ChangeLog.xsl releases.xml
	$(XSLTPROC) -o ChangeLog ChangeLog.xsl releases.xml

dist_doc_DATA=README COPYING

SUBDIRS= \
	distro

bin_PROGRAMS= \
	mp3unicode

mp3unicode_SOURCES= \
	mp3unicode.cpp messages.h

dist-hook:
	ln -s distro/rpm/mp3unicode.spec $(distdir)/mp3unicode.spec

clean-generic:
	-rm pkcs11-helper.spec
	-rm -f *.html

if WIN32
mp3unicode.1.html:
	$(MAN2HTML) < mp3unicode.1 > $@

nodist_html_DATA=mp3unicode.1.html

EXTRA_DIST+=mp3unicode.1

else
dist_man_MANS=mp3unicode.1
endif

