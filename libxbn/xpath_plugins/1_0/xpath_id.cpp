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

xpathplugin_generate_id::xpathplugin_generate_id()
{
	min_parameter = 0;
	max_parameter = 0;
	name          = "generate-id";
}
bool            xpathplugin_generate_id::testUnit()
{
	return testPass( "/test/generate-id()", 1, xbnode::xbn_temp, "" );
}
bool            xpathplugin_generate_id::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
	{
		pxpath->raiseError( name+"() missing current node", &state, __FILE__,__LINE__ );
		return false;
	}

	state.ResultNodeList.push_back(  state.pStack->createTempNode( state.pCurrentNode.id() ) );
	return true;
}

//----------------------------------------------------------------------------------------------------------------------
xpathplugin_id::xpathplugin_id()
{
	min_parameter = 0;
	max_parameter = 0;
	name          = "id";
}
bool            xpathplugin_id::testUnit()
{
	return testPass( "/test/c/c3/id()", 3, xbnode::xbn_attribute, "" );
}
bool            xpathplugin_id::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
		return false;

	sptr<xbnode> id_attribute= state.pCurrentNode->getAttribute( "id" );
	if( id_attribute )
	{
		state.ResultNodeList.push_back( id_attribute );
	}
	else
	{
		pxpath->raiseError( name+"() missing attribute", &state, __FILE__, __LINE__ );
	}
	return true;
}

