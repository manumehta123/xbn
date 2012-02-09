/*
	libxbn is a small and tiny xml binary node
	Copyright (C) 2010  Thomas Kraus (thomentor@gmx.de)

	This library is free software; you can redistribute it and/or modify it
	under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation; either version 2.1 of the License, or
	(at your option) any later version.

	This library is distributed in the hope that it will be useful, but
	WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
	or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
	 License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with this library; if not, write to the Free Software Foundation,
	Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110, USA
*/
#ifndef XBSTRING_H
#define XBSTRING_H

#include <string>
#include "sptr.h"


std::string std_string_ltrim( std::string str );
std::string std_string_rtrim( std::string str );
std::string std_string_trim( std::string str );
//void std_string_replace(std::string& value, std::string const& search,std::string const& replace);
void std_string_replace(std::string& value,  std::string  search, std::string  replace);
std::string Xml2Text( std::string &data );
std::string Text2Xml( std::string &data );

#endif // XBSTRING_H
