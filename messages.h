/*
	Copyright (c) 2006-2007 Alon Bar-Lev <alon.barlev@gmail.com>
	Copyright (c) 2006-2007 Andrey Dubovik <andu@inbox.ru>
	All rights reserved.

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License version 2
	as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program (see the file COPYING.GPL included with this
	distribution); if not, write to the Free Software Foundation, Inc.,
	59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef MESSAGES_H
#define MESSAGES_H

#include <string>

namespace msg {

const char* copyright = "\
Copyright (c) 2006-2007 Alon Bar-Lev <alon.barlev@gmail.com>\n\
Copyright (c) 2006-2007 Andrey Dubovik <http://www.yellowsite.ru>\n\
\n\
This is free software; see the source for copying conditions.\n\
There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n\n";


const char* usage = "\
Usage:\n\
  mp3unicode [options] file1 file2 ...\n\
\n\
Options:\n\
  -h, --help                   This help\n\
  -v, --version                Version information\n\
  -s, --source-encoding        Current encoding, required\n\
  -1, --id3v1-encoding         Target encoding, can be 'none' or an ANSI code page\n\
  -2, --id3v2-encoding         Target encoding, can be 'none', an ANSI code page or 'unicode'\n\
  -p, --preserve-unicode       Try not to reencode unicode.\n\
\n\
To view available ANSI code pages, execute:\n\
  iconv --list\n\
\n\
Important: use 'unicode' instead of utf-8 or utf-16\n\n";


const char* wrong_senc = "Cannot open source encoding.\n";

const char* wrong_1enc = "Cannot open id3v1 encoding.\n";

const char* wrong_2enc = "Cannot open id3v2 encoding.\n";

const char* enc_error = "Error during encoding.\n";

const char* nosenc = "Please specify source encoding.\n";

const char* seehelp = "For help, type mp3unicode --help.\n";

const char* nofiles = "No files are given.\n";

std::string nofile(const std::string filename) {
	return "Cannot open file: " + filename + ".";
}

std::string error(const std::string message) {
	return "Error: " + message + "\n";
}

}

#endif
