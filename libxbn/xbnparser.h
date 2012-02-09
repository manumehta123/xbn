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
#ifndef XBNPARSER_H
#define XBNPARSER_H

#include "xbn.h"
#include <string>
#include <iostream>

class xbnparser
{
private:
	char		m_inQuoted;
	std::string m_lastToken;
	std::string m_prefix_whitespace;
	std::string m_currentToken;
	uint_xbn	m_currentToken_pos;

	uint_xbn	m_current_pos;
	uint_xbn	m_current_depth;

	char		m_next_char;

public:
			xbnparser();

	bool		processStream( std::istream &input_stream );

	std::string getDrop();
	std::string getToken();
	std::string getLastToken();
	char		getNextChar();

	std::string	readTill( std::istream &input_stream, std::string till_string );
	std::string readTillStop( std::istream &input_stream, char stop );
	bool		await( std::istream &input_stream, const char *await_string );

	uint_xbn	getTokenPos();
	void		raiseError( std::string message, const char *file = __FILE__, int line = __LINE__ );

	enum
	{
		xbnp_undefined =0,
		xbnp_error,
		xbnp_in_cdata,
		xbnp_in_comment,
		xbnp_in_text

	} Status;
};

#endif // XBNPARSER_H
