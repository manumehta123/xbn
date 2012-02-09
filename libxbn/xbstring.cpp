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
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "xbstring.h"
#include "xbdata.h"


std::string std_string_trim( std::string str )
{
	return std_string_rtrim( std_string_ltrim(str) );
}

std::string std_string_rtrim( std::string str )
{
	if( str.empty() )
		return str;

	// trim trailing spaces
	size_t endpos = str.find_last_not_of(" \t\r\n");
	if( std::string::npos != endpos )
	{
		str = str.substr( 0, endpos+1 );
	}
	else
	{
		size_t pos = str.find_first_of(" \t\r\n");
		if( std::string::npos != pos )
		{
			// Sonderfall , der ganze String besteht nur aus whitespace!
			str="";
		}
	}
	return str;
}

std::string std_string_ltrim( std::string str )
{
	if( str.empty() )
		return str;

	// trim leading spaces
	size_t startpos = str.find_first_not_of(" \t\r\n");
	if( std::string::npos != startpos )
	{
		str = str.substr( startpos );
	}
	else
	{
		size_t pos = str.find_first_of(" \t\r\n");
		if( std::string::npos != pos )
		{
			// Sonderfall , der ganze String besteht nur aus whitespace!
			str="";
		}
	}
	return str;
}

/*
void std_string_replace(std::string& value, std::string const& search,std::string const& replace)
{
	size_t  next;

	for(next = value.find(search);
		next != std::string::npos;
		next = value.find(search,next)

	   )
	{
		value.replace(next,search.length(),replace);
		next += replace.length();
	}
}*/

void std_string_replace(std::string& value, std::string search,std::string replace)
{
	size_t  next;

	for(next = value.find(search);
		next != std::string::npos;
		next = value.find(search,next)

	   )
	{
		value.replace(next,search.length(),replace);
		next += replace.length();
	}
}

std::string det_Automat( std::istream &stream, const char *stop_signs,const char *white_space,const char *ignore_chars="", bool bIgnoreKlammerung=true );

//	liest zeichen ein bis eines der Stoppzeichen auftreten
//  diese werden nicht mit eingelesen!  Klammerungen "' werden
//  übersprungen!
std::string det_Automat( std::istream &stream, const char *stop_signs,const char *white_space,const char *ignore_chars,bool bIgnoreKlammerung )
{
	char comment_flag= 0;
	bool bWhiteSpace = true;
	int eckig_depth = bIgnoreKlammerung ? -1:0;
	std::string ret ="";


	while( !stream.eof() && stream.peek()>=0 )
	{
		bool new_whitespace = false;

		if( !comment_flag && eckig_depth<=0 )
		{
			char peek = stream.peek();
			const char *ss  = stop_signs;
			while( *ss && *ss!=peek ) ++ss;
			if( *ss )
				break;

			// Whitespaces können nur in einem nicht comment_ block auftreten
			const char *ws = white_space;
			while( *ws && *ws!=peek ) ++ws;
			if( *ws )
				new_whitespace = true;
		}
		char wert = (char)stream.get();

		switch( wert )
		{
			case '[':
				if( !comment_flag && eckig_depth>=0 ) ++eckig_depth;
				break;
			case ']':
				if( !comment_flag && eckig_depth>=0 ) --eckig_depth;
				break;
		}

		switch( wert )
		{
			case '"':
			case '\'':
				// Comments
				if( !comment_flag )
					comment_flag = wert;
				else
				if( comment_flag == wert )
					comment_flag = 0;

				bWhiteSpace = false;
				ret+=wert;
				break;
			default:
				if( !bWhiteSpace || !new_whitespace )
				{
					bWhiteSpace = new_whitespace;

					char *ic;for(ic = (char*)ignore_chars;*ic&&*ic!=wert;++ic);

					if( comment_flag || *ic!=wert )
						ret+=wert;
				}
				break;
		}
	}
	return ret;
}

//	Wandelt einen Xml Kodierten String in einen normalen Textstring um
//
std::string Xml2Text( std::string &data )
{
	std::string ret = "";
	std::istringstream iss(data,std::istringstream::in);

	while( !iss.eof() && iss.peek()>=0 )
	{
		ret += det_Automat( iss , "&", "" );

		if( iss.peek()=='&' )
		{
			std::string ampy =  det_Automat( iss , ";", "" );
			if( iss.peek()==';' )
			{
				ampy+=(char)iss.get();
				if( ampy == "&amp;" )
				{
					ret+='&';
				} else
				if( ampy == "&apos;" )
				{
					ret+='\'';
				} else
				if( ampy == "&quot;" )
				{
					ret+='"';
				} else
				if( ampy == "&gt;" )
				{
					ret+='>';
				} else
				if( ampy == "&lt;" )
				{
					ret+='<';
				} else
				if( ampy.find("&#")==0 && ampy[ ampy.length()-1 ]==';' )
				{
					int code = atoi( ampy.substr(2,ampy.length()-3).c_str() );
					ret+=(char)code;
				} else
				{
					std::cout << "Xml2Text() unrecognized ampy " << ampy.c_str() << std::endl;
				}
			}
			else
			{
				std::cout << "Xml2Text() unexpected closing-token found '"<< iss.peek() <<"' but ';' required @" << ampy <<"<--" <<std::endl;
				break;
			}
		}
	}

	//printf("Xml2Text %s -> %s \n",data.c_str(),ret.c_str() );
	return ret;
}

//	Wandelt einen Normalen Textstring in einen Xml Kodierten String um
//
std::string Text2Xml( std::string &data )
{
	std::string ret = "";
	std::istringstream iss(data,std::istringstream::in);

	while( !iss.eof() && iss.peek()>=0 )
	{
		char array[]={'&','<','>','\"','\'','\r','\n',228,246,252,196,214,220,223,0 }; // "&<>\"'äöüÄÖÜß"

		ret+= det_Automat( iss , array, "" );
		if( !iss.eof() )
		{
			switch( iss.get() )
			{
				case '&': ret+="&amp;";		break;
				case '<': ret+="&lt;";		break;
				case '>': ret+="&gt;";		break;
				case '\'':ret+="&apos;";	break;
				case '"': ret+="&quot;";	break;

				case '\r': ret+="&#10;";	break;
				case '\n': ret+="&#13;";	break;
				case 228: ret+="&#228;";	break;//ä   228 132
				case 246: ret+="&#246;";	break;//ö   246 148
				case 252: ret+="&#252;";	break;//ü   252 129
				case 196: ret+="&#196;";	break;//Ä   196 142
				case 214: ret+="&#214;";	break;//Ö   214 153
				case 220: ret+="&#220;";	break;//Ü   220 154
				case 223: ret+="&#223;";	break;//ß   223
				default:
					std::cout << "Text2Xml() unrecognized state" << std::endl;
				break;
			}
		}
	}
	return ret;
}

