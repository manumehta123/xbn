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

xpathplugin_last::xpathplugin_last()
{
	min_parameter = 1;
	max_parameter = 1;
	name          = "last";
}
bool            xpathplugin_last::testUnit()
{
	return testPass( "/last()", 1, xbnode::xbn_temp, "1" );
}
bool           xpathplugin_last:: operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
	{
		pxpath->raiseError( name+"() missing current node", &state, __FILE__,__LINE__ );
		return false;
	}
	state.ResultNodeList.push_back(  state.pStack->createTempNode( zahlToString( state.last_node_position+1) ) );
	return true;
}

//----------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
xpathplugin_position::xpathplugin_position()
{
	min_parameter = 0;
	max_parameter = 0;
	name          = "position";
}
bool            xpathplugin_position::testUnit()
{
	return testPass( "/position()", 1, xbnode::xbn_temp, "1" );
}
bool            xpathplugin_position::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
	{
		pxpath->raiseError( name+"() missing current node", &state, __FILE__,__LINE__ );
		return false;
	}

	state.ResultNodeList.push_back(  state.pStack->createTempNode( zahlToString( state.current_node_position+1 ) ) );
	return true;
}


