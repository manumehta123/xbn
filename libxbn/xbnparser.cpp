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
#include "xbnparser.h"

xbnparser::xbnparser()
{
	this->m_inQuoted = 0;
	this->m_currentToken = "";
	this->m_lastToken = "";
	this->m_currentToken_pos = 0;
	this->m_current_pos = 0;
	this->m_current_depth = 0;
	this->Status = xbnparser::xbnp_undefined;
}

bool		xbnparser::processStream( std::istream &input_stream )
{
	std::string  whitespaces=" \r\n\t";
	std::string  nextchar_terminate="<>/=?!'\"";

	// Whitespaces ueberspulen
	m_prefix_whitespace="";
	while( !input_stream.eof() &&
		   whitespaces.find( input_stream.peek() )!=std::string::npos )
	{
		 m_prefix_whitespace += input_stream.get();
	}

	m_lastToken = m_currentToken;
	m_currentToken.clear();

	this->m_currentToken_pos = input_stream.tellg();
	char quoted=0;
	while( !input_stream.eof() )
	{
		char current_char = input_stream.get();
		m_next_char       = input_stream.peek();
		m_currentToken+=current_char;

		// Quotierung steuern
		if( current_char=='\"' || current_char=='\'' )
		{
			if( !quoted )
			{
				quoted = current_char;
				continue;
			}
			else
			if( quoted==current_char )
			{
				quoted = 0;
				break;
			}
		}
		if( quoted )
			continue;


		if(  whitespaces.find( m_next_char )!=std::string::npos )
			break;

		if( m_currentToken.length()==1 &&
			nextchar_terminate.find( current_char )!=std::string::npos )
		{
			if( (current_char=='<' && m_next_char=='/') ||
				(current_char=='/' && m_next_char=='>') ||
				(current_char=='<' && m_next_char=='!') ||
				(current_char=='!' && m_next_char=='>') ||
				(current_char=='<' && m_next_char=='?') ||
				(current_char=='?' && m_next_char=='>') )
			{
				m_currentToken+= input_stream.get();
				m_next_char    = input_stream.peek();
				break;
			}
			break;
		}
		else
		{
			if( nextchar_terminate.find( m_next_char )!=std::string::npos  )
				break;
			if( m_currentToken=="--" )
				break;
		}
	}

	// Sonderfall <!--
	if( m_currentToken=="<!" )
	{
		if( m_next_char=='-' )
		{
			if( !await( input_stream, "--") )
			{
				raiseError( "comment is not wellformed - missing <!--", __FILE__, __LINE__ );
			}
		}else
		if( m_next_char=='[' )
		{
			if( !await( input_stream, "[CDATA[" ) )
			{
				raiseError( "cdata is not wellformed - missing <![CDATA[", __FILE__, __LINE__ );
			}
		}

	}

	return  this->m_currentToken.size();
}

std::string	xbnparser::readTill( std::istream &input_stream, std::string till_string )
{
	std::string ret;
	while( !input_stream.eof() )
	{
		ret += input_stream.get();
		if( ret.length()>=till_string.length() &&
			ret.substr( ret.length()-till_string.length() )==till_string )
			break;
	}
	m_next_char = input_stream.peek();
	return ret;
}

std::string xbnparser::readTillStop( std::istream &input_stream, char stop )
{
	std::string ret;
	while( !input_stream.eof() && input_stream.peek()!=stop )
	{
		ret+=input_stream.get();
	}
	return ret;
}

bool		xbnparser::await( std::istream &input_stream, const char *await_string )
{
	for(int p=0; !input_stream.eof() && await_string[p] ;++p )
	{
		if( input_stream.get()!=await_string[p] )
			return false;
		m_currentToken+=await_string[p];
	}
	m_next_char = input_stream.peek();
	return true;
}

std::string xbnparser::getDrop()
{
	return m_prefix_whitespace;
}

std::string xbnparser::getToken()
{
	return m_currentToken;
}

std::string xbnparser::getLastToken()
{
	return m_lastToken;
}

char xbnparser::getNextChar()
{
	return m_next_char;
}

uint_xbn		xbnparser::getTokenPos()
{
	return m_currentToken_pos;
}


void		xbnparser::raiseError( std::string message, const char *file, int line )
{
	std::cout << "xbnparser::raiseError" << std::endl;
	std::cout << "["<< line << "]"<<file <<" " << message << std::endl;
	std::cout << "last token " << m_lastToken << std::endl;
	std::cout << "current token " << m_currentToken << "@" << m_currentToken_pos << std::endl;
}
