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
#ifndef XBN_DOCUMENT_H
#define XBN_DOCUMENT_H

#include <string>
#include <iostream>
#include <map>
#include "xbnode.h"
#include "sptr.h"

class xbn_document;
typedef std::map<std::string,sptr<xbn_document> > ptrdocmap;

class xbdata;
class xbn_document : public sptr_class
{
private:
	sptr<xbdata> m_ptr_xbdata;
public:
				xbn_document();
	virtual		~xbn_document();

	//------------------------------------------------------------------------------------------------------------------
	//		IO
	//------------------------------------------------------------------------------------------------------------------
	bool		loadFile( std::string filename );
	bool		loadPlainXML( std::string &plain_xml );
	bool		loadStream( std::istream &input_stream );

	bool		loadTestDocument();

	bool		saveFile( std::string filename );
	bool		savePlainXML( std::string &plain_xml );
	bool		saveStream( std::ostream &output_stream );

	//------------------------------------------------------------------------------------------------------------------
	//		xpath
	//------------------------------------------------------------------------------------------------------------------
	sptr<xbnode> getRootNode();
	uint_xbn	 selectNodes( xbnode_list &node_list_result, std::string xpath_pattern );
	sptr<xbnode> selectNode( std::string xpath_pattern );

	//------------------------------------------------------------------------------------------------------------------
	//		xsd
	//------------------------------------------------------------------------------------------------------------------
	bool		checkXSD();

	//------------------------------------------------------------------------------------------------------------------
	//		Cache
	//------------------------------------------------------------------------------------------------------------------
	static		sptr<xbn_document>	getDocument( std::string filename );
	static		bool				removeDocument( std::string filename );
private:
	static		ptrdocmap			s_ptrdocmap;
};

#endif // XBN_DOCUMENT_H
