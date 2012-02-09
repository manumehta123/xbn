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
#include "xpath_plugins/xbn_xpath_plugins_1_0.h"
#include "xbn_helper.h"
#include "xbstring.h"
#include "xbn_document.h"

xpathplugin_document::xpathplugin_document()
{
	min_parameter = 1;
	max_parameter = 1;
	name          = "document";
}
bool            xpathplugin_document::testUnit()
{
	return testPass( "document('test2.xml')/test", 1, xbnode::xbn_node, "" );;
}
bool            xpathplugin_document::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
		return false;

	xbn_state arg1(state);
	if( !pxpath->process( arg1, *(state.pCurrent_token) ) )
	{
		pxpath->raiseError( this->name + "() could not process arg1", &state,__FILE__,__LINE__ );
		return false;
	}

	for( xbnode_list::iterator pc_arg1=arg1.ResultNodeList.begin(),pe_arg1=arg1.ResultNodeList.end();
			pc_arg1!=pe_arg1;
			++pc_arg1 )
	{
		std::string wert1 = (*pc_arg1)->getText();

		// Dokument Laden und bereitstellen
		// evtl. noch ein Dokumenten Cache bereitstellen?
		xbn_document ptr_doc;
		if( !ptr_doc.loadFile(wert1) )
		{
			pxpath->raiseError(name+"() could not load "+wert1, &state, __FILE__,__LINE__ );
			return false;
		}

		state.ResultNodeList.push_back(
					ptr_doc.getRootNode()
				);
	}
	return true;
}

