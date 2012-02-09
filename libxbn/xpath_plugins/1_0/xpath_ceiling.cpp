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

xpathplugin_ceiling::xpathplugin_ceiling()
{
	min_parameter = 1;
	max_parameter = 1;
	name          = "ceiling";
}
bool            xpathplugin_ceiling::testUnit()
{
	return testPass( "ceiling(1)", 1, xbnode::xbn_temp, "1" )
			&testPass( "ceiling(1.1)", 1, xbnode::xbn_temp, "2" )
			&testPass( "ceiling(0.9)", 1, xbnode::xbn_temp, "1" );
}
bool            xpathplugin_ceiling::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
		return false;

	xbn_state arg1(state);
	if( !pxpath->process( arg1, *(state.pCurrent_token) ) )
	{
		pxpath->raiseError( this->name + " could not process arg1", &state,__FILE__,__LINE__ );
		return false;
	}
	for( xbnode_list::iterator pc_arg1=arg1.ResultNodeList.begin(),pe_arg1=arg1.ResultNodeList.end();
			pc_arg1!=pe_arg1;
			++pc_arg1 )
	{
		if( (*pc_arg1)->isNumeric() )
		{
			int c = (int)( (*pc_arg1)->getNumeric()+0.99999 );
			state.ResultNodeList.push_back(  state.pStack->createTempNode( zahlToString(c) ) );
		}
		else
		{
			pxpath->raiseError( this->name + "() arg1 is not numeric", &state,__FILE__,__LINE__ );
			return false;
		}
	}
	return true;
}

