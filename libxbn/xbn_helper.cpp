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
#include <iostream>
#include <sstream>
#include "xbn_helper.h"


std::string zahlToString(double d, unsigned int weite,
						 unsigned int format,                    // 0: fix, 1: scientific, sonst: automatisch
						 unsigned int anzahlNachkommastellen )
{ // nur Format 0/1
   std::ostringstream wandler;

   if( (int)d==d )
	   anzahlNachkommastellen=0;

   if(format == 0)
   {
	  wandler.setf(std::ios::fixed, std::ios::floatfield);
	  if(anzahlNachkommastellen > 0)
	  {
		 wandler.setf(std::ios::showpoint);
	  }
   }
   else
   {
	  if(format == 1)
	   {
		 wandler.setf(std::ios::scientific, std::ios::floatfield);
	  }
   }
   if(format == 0 || format == 1)
   {
	  wandler.precision(anzahlNachkommastellen);
   }
   if(weite > 0)
   {
	  wandler.width(weite);
   }
   wandler << d;
   return wandler.str();
}

std::string zahlToString(long i, unsigned int weite)
{
   return zahlToString(static_cast<double>(i), weite, 0, 0);
}
std::string zahlToString(int i, unsigned int weite)
{
   return zahlToString(static_cast<double>(i), weite, 0, 0);
}
std::string zahlToString(unsigned long i, unsigned int weite)
{
   return zahlToString(static_cast<double>(i), weite, 0, 0);
}
std::string zahlToString(unsigned int i, unsigned int weite)
{
   return zahlToString(static_cast<double>(i), weite, 0, 0);
}



double		stringToZahl( std::string str )
{
	if( str.empty() )
		return 0;
	std::istringstream ss( str );
	double wert=0;
	ss >> wert;
	return wert;
}

