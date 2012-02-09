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
#include "libxbn/xbn.h"
#include "libxbn/xbn_document.h"
#include "libxbn/xbn_xpath.h"
#include "libxbn/xbn_xslt.h"

#include <string>
#include <istream>
#include <fstream>

#include "libxbn/xbn_helper.h"

using namespace std;

/// xpath
///

/// testxbn
///
int main( int argc, char**argv )
{
	clog << "xslt version 0.2." << _XBN_VERSION << endl;
	clog << "build "<< __DATE__ << "." << __TIME__ << endl ;

	if( argc==1 )
	{
		cout << "xsltp file.xslt input.xml" << endl;
		return 0;
	}

	sptr_class::init();
	{
		xbn_document xdoc;
		if( argc==3 )
		{
			clog << "xslt.transform() " << argv[1] << "^"<<argv[2]<<endl;
			xbn_xslt xslt( argv[1] );
			xdoc.loadFile( argv[2] );

			sptr<xbn_document> ptr_result =  xslt.transform( &xdoc );
			if( ptr_result )
			{
				ptr_result->saveStream( std::cout );
			}
		}
	}
	sptr_class::cleanup();
	return(1);
}
