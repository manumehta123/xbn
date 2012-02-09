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
	clog << endl;
	clog << "xmlos version 0.2." << _XBN_VERSION << endl;
	clog << "build "<< __DATE__ << "." << __TIME__ << endl ;

	if( argc==1 )
	{
		clog << "xmlos [file.xml]" << endl;
		return 0;
	}

	sptr_class::init();
	{
		std::string document_file="";
		xbn_document xdoc;
		if( argc==1 )
		{
			document_file = "test";
			xdoc.loadTestDocument();
		} else
		if( argc==2 )
		{
			document_file = argv[1];
			xdoc.loadFile( document_file );
		}

		bool status=true;
		sptr<xbnode> current_node = xdoc.getRootNode();
		while( status )
		{
			std::string cmd;
			clog << document_file << ":" << current_node->getNodePath() << ">";
			std::getline( cin, cmd );


			if( cmd=="q" || cmd =="exit" || cmd=="quit" )
				break;

			if( cmd=="?" || cmd=="help" )
			{
				clog << "\txmlos help" << endl;
				clog << "\tq, quit, exit	terminate xmlos" << endl;
				clog << "\t?, help			show this help" << endl;
				clog << "\tcd xpath			change to first element of xpath" << endl;
				clog << "\t*				shows all Childnode" << endl;
				clog << "\t@*				shows all attributes" << endl;
				clog << "\txpath			shows the xpath result" << endl;
				clog << "\tstat				shows statistics" << endl;
			}

			if( cmd=="ls" ) cmd = "*";
			if( cmd.length()>3 && cmd.substr(0,3)=="ls " ) cmd = cmd.substr(3);

			if( cmd=="stat")
			{
				sptr_class::print_debug_state();
				continue;
			}

			if( cmd=="gc")
			{
				sptr_class::gc();
				continue;
			}

			if( cmd.length()>3 && cmd.substr(0,3)=="cd " )
			{
				std::string path = cmd.substr(3);

				sptr<xbnode> new_node = xbn_xpath::selectNode( current_node, path );
				if( new_node )
				{
					current_node = new_node;
				}
			}
			else
			{
				xbnode_list result;
				if( xbn_xpath::selectNodes( current_node, result, cmd  ) )
				{
					cout << "Type     Wert" << endl;
					cout << "--------------------------------------------" << endl;
					int pos=0;
					for( xbnode_list::iterator pc=result.begin(), pe=result.end(); pc!=pe && pos<25 ; ++pc,++pos )
					{
						switch( (*pc)->getType() )
						{
						case xbnode::xbn_root:
							cout << "!ROOT    " << endl;
							break;
						case xbnode::xbn_doctype:
							cout << "!DOCTYPE " << endl;
							break;
						case xbnode::xbn_node:
							cout << "!NODE:   "<< (*pc)->getFullname() << endl;
							break;
						case xbnode::xbn_temp:
							cout << "!TEMP    " << (*pc)->getValue() << endl;
							break;
						case xbnode::xbn_text:
							cout <<  "!TEXT   " << (*pc)->getValue() << endl;
							break;
						case xbnode::xbn_attribute:
							cout << (*pc)->getFullname() << " = " << (*pc)->getValue() << endl;
							break;
						case xbnode::xbn_comment:
							cout << "!COMMENT " << (*pc)->getValue() << endl;
							break;
						case xbnode::xbn_cdata:
							cout << "[CDATA[  " << (*pc)->getValue() << endl;
							break;
						case xbnode::xbn_instruction:
							cout << "!INSTR   " << (*pc)->getValue() << endl;
							break;
						default:
							cout << "!UNDEF   " << endl;
							break;
						}
					}
					if( pos==25 ) cout << "..." << std::endl;
					cout << "--------------------------------------------" << endl;
					clog << "count " << result.size() << endl;
				}
				else
				{
					cout << "no result" << endl;
				}
			}
		}
	}
	sptr_class::cleanup();
	return(1);
}
