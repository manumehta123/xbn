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
#ifndef XBN_HELPER_H
#define XBN_HELPER_H

#include <string>

std::string zahlToString(double d, unsigned int weite=0,
						 unsigned int format=0,                    // 0: fix, 1: scientific, sonst: automatisch
						 unsigned int anzahlNachkommastellen=4 );
std::string zahlToString(long i, unsigned int weite=0);
std::string zahlToString(int i, unsigned int weite=0);
std::string zahlToString(unsigned long i, unsigned int weite=0);
std::string zahlToString(unsigned int i, unsigned int weite=0);


double		stringToZahl( std::string str );
#endif // XBN_HELPER_H
