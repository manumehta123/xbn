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
#include <fstream>
#include <sstream>
#include "xbn.h"
#include "xbnode.h"
#include "xbdata.h"
#include "xbn_document.h"
#include "xbn_xpath.h"

xbn_document::xbn_document()
{
	//std::cout << (long)this << "::xbn_document()"<<std::endl;
	m_ptr_xbdata = new xbdata();
}

xbn_document::~xbn_document()
{
	//std::cout << (long)this << "::~xbn_document()"<<std::endl;
	m_ptr_xbdata = sptr<xbdata>::Empty;
}

bool		xbn_document::loadTestDocument()
{
	std::string xml = "<?xml encode='UTF-8'?>"\
								"<!-- Hallo -->"\
								"<test>"\
								" <a test='Hallo&amp;' text='Tach'/>"\
								" <!-- und noch ein Comment-->"\
								" <b>Hallo B!! lf&#10;lf</b>"\
								" <c name='subnode c'>"\
								"	 <c2 wert='12'/>"\
								"	 <c3 id='666-8' wert='8'/>"\
								"	 <c3 id='666-9' wert='9'/>"\
								"	 <c3 id='666-11' wert='1'/>"\
								"</c>"\
								" <d>"\
								"	 <![CDATA[Hallo, das ist ein cdata block 10>9 und 9<10 -- mal gucken... ]]>"\
								" </d>"\
								" <d wert='99'>"\
								"	 <name>hund</name>"\
								" </d>"\
								" <uc1:test2 wert='uc1'>"\
								"	 <d wert='44'/>"\
								" </uc1:test2>"\
								"</test>";
	return loadPlainXML( xml );
}

//------------------------------------------------------------------------------------------------------------------
//		IO
//------------------------------------------------------------------------------------------------------------------
bool		xbn_document::loadFile( std::string filename )
{
	std::ifstream fs( filename.c_str(), std::ios::binary );

	fs.seekg( 0, std::ios::end );
	uint_xbn length = fs.tellg();
	fs.seekg( 0, std::ios::beg );

	bool ret = m_ptr_xbdata->read( fs, length );
	fs.close();
	return ret;
}

bool		xbn_document::loadPlainXML( std::string &plain_xml )
{
	return m_ptr_xbdata->read( plain_xml );
}

bool		xbn_document::loadStream( std::istream &input_stream )
{
	return m_ptr_xbdata->read( input_stream );
}

bool		xbn_document::saveFile( std::string filename )
{
	std::ofstream fs( filename.c_str() );
	bool ret = m_ptr_xbdata->write( fs );
	fs.close();
	return ret;
}

bool		xbn_document::savePlainXML( std::string &plain_xml )
{
	std::stringstream ss;
	bool ret = m_ptr_xbdata->write( ss );
	ss.str(plain_xml);
	return ret;
}

bool		xbn_document::saveStream( std::ostream &output_stream )
{
	return m_ptr_xbdata->write( output_stream );
}

//------------------------------------------------------------------------------------------------------------------
//		xpath
//------------------------------------------------------------------------------------------------------------------
sptr<xbnode> xbn_document::getRootNode()
{
	return m_ptr_xbdata ? m_ptr_xbdata->getRootNode() : sptr<xbnode>::Empty;
}

uint_xbn		xbn_document::selectNodes( xbnode_list &node_list_result, std::string xpath_pattern )
{
	sptr<xbnode> ptr_root = m_ptr_xbdata->getRootNode();
	if( ptr_root )
	{
		return xbn_xpath::selectNodes( ptr_root, node_list_result, xpath_pattern );
	}
	return 0;
}

sptr<xbnode> xbn_document::selectNode( std::string xpath_pattern )
{
	sptr<xbnode> ptr_root = m_ptr_xbdata->getRootNode();
	if( ptr_root )
	{
		xbnode_list node_list_result;
		return xbn_xpath::selectNodes( ptr_root, node_list_result, xpath_pattern,NULL,1 )>0? node_list_result.front():sptr<xbnode>::Empty;
	}
	return 0;
}

//------------------------------------------------------------------------------------------------------------------
//		xsd
//------------------------------------------------------------------------------------------------------------------
bool		xbn_document::checkXSD()
{
	return false;
}


//------------------------------------------------------------------------------------------------------------------
//		Cache
//------------------------------------------------------------------------------------------------------------------
ptrdocmap		xbn_document::s_ptrdocmap;

sptr<xbn_document>	xbn_document::getDocument( std::string filename )
{
	sptr<xbn_document> ptr_doc = s_ptrdocmap[ filename ];

	if( !ptr_doc )
	{
		ptr_doc = new xbn_document();

		if( ptr_doc->loadFile( filename ) )
		{
			s_ptrdocmap[ filename ] = ptr_doc;
		}
		else
		{
			ptr_doc = sptr<xbn_document>::Empty;
		}
	}
	return ptr_doc;
}

bool			xbn_document::removeDocument( std::string filename )
{
	if( s_ptrdocmap[ filename ] )
	{
		s_ptrdocmap[ filename ] = sptr<xbn_document>::Empty;
		return true;
	}
	return false;
}
