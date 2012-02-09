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
int main( int argc, char**argv )
{
	clog << "xpath version 0.2." << _XBN_VERSION << endl;
	clog << "build "<< __DATE__ << "." << __TIME__ << endl ;

	if( argc==1 )
	{
		clog << "xpath [file.xml] xpath" << endl;
		return 0;
	}

	sptr_class::init();
	{
		xbn_document xdoc;
		std::string pattern;
		if( argc==2 )
		{
			xdoc.loadTestDocument();
			pattern = argv[1];
		} else
		if( argc==3 )
		{
			xdoc.loadFile( argv[1] );
			pattern = argv[2];
		}

		clog << "x-path " << pattern << endl;
		xbnode_list result;
		if( xdoc.selectNodes( result, pattern  ) )
		{
			for( xbnode_list::iterator pc=result.begin(), pe=result.end(); pc!=pe; ++pc )
			{
				switch( (*pc)->getType() )
				{
				case xbnode::xbn_root:
					cout << "!ROOT" << endl;
					break;
				case xbnode::xbn_doctype:
					cout << "!DOCTYPE " << endl;
					break;
				case xbnode::xbn_node:
					cout << "!NODE: "<< (*pc)->getFullname() << endl;
					break;
				case xbnode::xbn_temp:
					cout << "!TEMP " << (*pc)->getValue() << endl;
					break;
				case xbnode::xbn_text:
					cout <<  "!TEXT " << (*pc)->getValue() << endl;
					break;
				case xbnode::xbn_attribute:
					cout << (*pc)->getFullname() << "=" << (*pc)->getValue() << endl;
					break;
				case xbnode::xbn_comment:
					cout << "!COMMENT " << (*pc)->getValue() << endl;
					break;
				case xbnode::xbn_cdata:
					cout << "[CDATA[ " << (*pc)->getValue() << endl;
					break;
				case xbnode::xbn_instruction:
					cout << "!INSTRUCTION " << (*pc)->getValue() << endl;
					break;
				default:
					cout << "!UNDEF" << endl;
					break;
				}
			}
			clog << "count " << result.size() << endl;
		}
		else
		{
			cout << "no result" << endl;
		}
	}
	sptr_class::cleanup();
	return(1);
}
