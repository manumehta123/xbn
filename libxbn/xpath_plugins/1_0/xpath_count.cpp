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

xpathplugin_count::xpathplugin_count()
{
	min_parameter = 1;
	max_parameter = 1;
	name          = "count";
}
bool            xpathplugin_count::testUnit()
{
	return testPass( "count(/)", 1, xbnode::xbn_temp, "1" )
			&testPass( "count(/test/c/c3)", 1, xbnode::xbn_temp, "3" )
			&testPass( "count(1|2|3|4)", 1, xbnode::xbn_temp, "4" );
}
bool            xpathplugin_count::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
		return false;

	xbn_state arg1(state);
	if( !pxpath->process( arg1, *(state.pCurrent_token) ) )
	{
		pxpath->raiseError( this->name + "() could not process arg1", &state,__FILE__,__LINE__ );
		return false;
	}
	state.ResultNodeList.push_back(  state.pStack->createTempNode( zahlToString( arg1.ResultNodeList.size() ) ) );
	return true;
}
