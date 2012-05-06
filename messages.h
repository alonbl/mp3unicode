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
	extern const char* copyright;
	extern const char* usage;
	extern const char* wrong_senc;
	extern const char* wrong_1enc;
	extern const char* wrong_2enc;
	extern const char* enc_error;
	extern const char* nosenc;
	extern const char* seehelp;
	extern const char* nofiles;
	extern const char* v1unicode;
	
	std::string nofile(const std::string filename);
	std::string emptyfile(const std::string filename);
	std::string writefail(const std::string filename);
	std::string filedone(const std::string filename);
	std::string error(const std::string message);
}

#endif
