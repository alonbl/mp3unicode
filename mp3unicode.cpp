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

#include "messages.h"
#include "config.h"
#include <stdio.h>
#include <getopt.h>
#include <fileref.h>
#include <mpegfile.h>
#include <tag.h>
#include <id3v1tag.h>
#include <id3v2tag.h>
#include <iconv.h>
#include <errno.h>
#include <cctype>

void tolower(std::string& s) {
	std::transform(s.begin(), s.end(), s.begin(), (int(*)(int))std::tolower);
}

class Converter {

protected:
	bool m_id3v1;
	bool m_id3v2;
	bool m_src_utf8;
	bool m_id3v2_utf8;
	iconv_t m_cd_src;
	iconv_t m_cd_id3v1;
	iconv_t m_cd_id3v2;
	TagLib::ID3v1::Tag *m_id3v1_tag;
	TagLib::ID3v2::Tag *m_id3v2_tag;
	bool m_preserve;

public:
	Converter (
		const std::string &src_enc,
		const std::string &id3v1_enc,
		const std::string &id3v2_enc,
		TagLib::ID3v1::Tag *id3v1_tag,
		TagLib::ID3v2::Tag *id3v2_tag,
		bool preserve
	) {
		m_id3v1 = false;
		m_id3v2 = false;
		m_src_utf8 = false;
		m_id3v2_utf8 = false;
		m_cd_src = (iconv_t)-1;
		m_cd_id3v1 = (iconv_t)-1;
		m_cd_id3v2 = (iconv_t)-1;
		std::string _src_enc = src_enc;
		std::string _id3v2_enc = id3v2_enc;

		m_id3v1_tag = id3v1_tag;
		m_id3v2_tag = id3v2_tag;
		m_preserve = preserve;

		if (_src_enc == "unicode") {
			m_src_utf8 = true;
			_src_enc = "UTF-8";
		}
		if ((m_cd_src = iconv_open ("UTF-8", _src_enc.c_str ())) == (iconv_t)-1) {
			throw msg::wrong_senc;
		}
		
		if(id3v1_enc == "unicode") {
			throw msg::v1unicode;
		}
		
		if(id3v1_enc != "none") {
			if ((m_cd_id3v1 = iconv_open (id3v1_enc.c_str (), "UTF-8")) == (iconv_t)-1) {
				throw msg::wrong_1enc;
			}
			m_id3v1 = true;	
		}
		if(_id3v2_enc != "none") {
			if (_id3v2_enc == "unicode") {
				_id3v2_enc = "UTF-8";
				m_id3v2_utf8 = true;
			}

			if ((m_cd_id3v2 = iconv_open (_id3v2_enc.c_str (), "UTF-8")) == (iconv_t)-1) {
				throw msg::wrong_2enc;
			}

			m_id3v2 = true;
		}
	}


	~Converter () {
		if (m_cd_src != (iconv_t)-1) {
			iconv_close (m_cd_src);
		}
		if (m_cd_id3v1 != (iconv_t)-1) {
			iconv_close (m_cd_id3v1);
		}
		if (m_cd_id3v2 != (iconv_t)-1) {
			iconv_close (m_cd_id3v2);
		}
	}

	int
	Tags() {
		return (
			(m_id3v1 ? TagLib::MPEG::File::ID3v1 : 0) |
			(m_id3v2 ? TagLib::MPEG::File::ID3v2 : 0)
		);
	}

	void
	Convert (
		const TagLib::String &value,
		void (TagLib::Tag::*field)(const TagLib::String &)
	) {
		std::string str;
		if (!m_src_utf8 && m_preserve) {
			if (heuristicIsUnicode (value)) {
				str = value.to8Bit (true);
			}
			else {
				str = ConvertString (m_cd_src, value.to8Bit (false));
			}
		}
		else {
			str = ConvertString (m_cd_src, value.to8Bit (m_src_utf8));
		}

		if (m_id3v1) {
			(m_id3v1_tag->*field) (TagLib::String (ConvertString (m_cd_id3v1, str)));
		}

		if (m_id3v2) {
			(m_id3v2_tag->*field) (
				TagLib::String (
					ConvertString (m_cd_id3v2, str),
					m_id3v2_utf8 ? TagLib::String::UTF8 : TagLib::String::Latin1
				)
			);
		}
	}

protected:

	bool
	heuristicIsUnicode (TagLib::String string) {
		unsigned u0080 = 0;
		for(TagLib::uint i = 0; i < string.size(); i++) {
			if(string[i] > 255) {
				return true;
			}
			if(string[i] > 127) {
				u0080++;
			}
		}
		if(u0080 * 2 <= string.size()) {
			return true;
		}
		else {
			return false;
		}
	}

	std::string
	ConvertString (
		iconv_t cd,
		std::string src
	) {
		const char *from;
		size_t from_size;
		char to_buffer[1024];
		char *to;
		size_t to_size;

		std::string dst;

		from = &*src.begin ();
		from_size = src.size ();
		while (from_size > 0) {
			to = to_buffer;
			to_size = sizeof (to_buffer);	 
			if (
				iconv (
					cd,
#if !defined(_LIBICONV_VERSION) || _LIBICONV_VERSION < 0x010B
					(char **)
#endif
					&from,
					&from_size,
					&to,
					&to_size
				) == (size_t)-1 &&
				errno != E2BIG
			) {
				throw msg::enc_error;
			}

			dst.append (to_buffer, to);
		}

		to = to_buffer;
		to_size = sizeof (to_buffer);
		if (iconv (cd, NULL, NULL, &to, &to_size) == (size_t)-1) {
			throw msg::enc_error;
		}

		dst.append (to_buffer, to);

		return dst;
	}
};

int main (int argc, char *argv[]) {
	try {
		static struct option long_options[] = {
			{ "source-encoding", required_argument, NULL, 's' },
			{ "id3v1-encoding", required_argument, NULL, '1' },
			{ "id3v2-encoding", required_argument, NULL, '2' },
			{ "preserve-unicode", no_argument, NULL, 'p' },
			{ "version", no_argument, NULL, 'v' },
			{ "help", no_argument, NULL, 'h' },
			{ NULL, 0, NULL, 0 }
		};
		int long_options_ret;
		std::string source_encoding;
		std::string id3v1_encoding = "none";
		std::string id3v2_encoding = "none";
		bool preserve_unicode = false;
		bool usage_ok = true;
		
		if(argc == 1) {
			printf(msg::usage);
			exit(1);
		}

		while (
			(long_options_ret = getopt_long (argc, argv, "s:1:2:pvh", long_options, NULL)) != -1
		) {
			switch (long_options_ret) {
				case 's':
					source_encoding = optarg;
					tolower(source_encoding);
				break;
				case '1':
					id3v1_encoding = optarg;
					tolower(id3v1_encoding);
				break;
				case '2':
					id3v2_encoding = optarg;
					tolower(id3v1_encoding);
				break;
				case 'p':
					preserve_unicode = true;
				break;
				case 'v':
					printf("%s %s\n", PACKAGE, PACKAGE_VERSION);
					printf(msg::copyright);
					exit (1);
				break;
				case 'h':
					printf(msg::usage);
					exit(1);
				default:
					usage_ok = false;
				break;
			}
		}

		if (usage_ok && source_encoding.empty ()) {
			printf (msg::nosenc);
			usage_ok = false;
		}
		
		if(optind == argc) {
			printf(msg::nofiles);
			usage_ok = false;
		}

		if (!usage_ok) {
			printf(msg::seehelp);
			exit (1);
		}

		TagLib::ID3v2::FrameFactory::instance()->setDefaultTextEncoding (TagLib::String::UTF8);

		for (int i=optind;i<argc;i++) {
			TagLib::MPEG::File mp3file(argv[i]);

			if (!mp3file.isOpen ()) {
				throw msg::nofile(argv[i]);
			}
			
			TagLib::Tag *tag = mp3file.tag();
			
			if(tag->isEmpty()) {
				std::cout << msg::emptyfile(argv[i]) << std::endl;
			}
			else {
				Converter converter (
					source_encoding,
					id3v1_encoding,
					id3v2_encoding,
					mp3file.ID3v1Tag (true),
					mp3file.ID3v2Tag (true),
					preserve_unicode
				);
	
				converter.Convert (tag->title (), &TagLib::Tag::setTitle);
				converter.Convert (tag->artist (), &TagLib::Tag::setArtist);
				converter.Convert (tag->album (), &TagLib::Tag::setAlbum);
				converter.Convert (tag->comment (), &TagLib::Tag::setComment);
				converter.Convert (tag->genre (), &TagLib::Tag::setGenre);
				
				mp3file.strip(~converter.Tags());		
				mp3file.save (converter.Tags ());
			}
		}

		exit (0);
	}
	catch (const std::string &e) {
		printf (msg::error(e).c_str());
		exit (1);
	}
	catch (const char *e) {
		printf (msg::error(e).c_str());
		exit (1);
	}

	return 1;
}
