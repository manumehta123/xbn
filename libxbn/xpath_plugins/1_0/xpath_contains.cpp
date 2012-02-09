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

xpathplugin_contains::xpathplugin_contains()
{
	min_parameter = 2;
	max_parameter = 2;
	name          = "contains";
}
bool            xpathplugin_contains::testUnit()
{
	return testPass( "contains('Hallo','ll')", 1, xbnode::xbn_temp, "true" )
			&testPass( "contains('Hallo','odda')", 1, xbnode::xbn_temp, "false" );
}
bool            xpathplugin_contains::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
		return false;

	xbn_state arg1(state);
	if( !pxpath->process( arg1, *(state.pCurrent_token) ) )
		return false;

	xbn_state arg2(state);
	if( !pxpath->process( arg2, *(state.pCurrent_token) ) )
		return false;

	if( arg1.ResultNodeList.size()!=arg2.ResultNodeList.size() )
	{
		pxpath->raiseError( name+"() resultsizes arg1,arg2 does not match",&state, __FILE__, __LINE__ );
		return false;
	}

	for( xbnode_list::iterator pc_arg1=arg1.ResultNodeList.begin(),pe_arg1=arg1.ResultNodeList.end(),
							   pc_arg2=arg2.ResultNodeList.begin();
			pc_arg1!=pe_arg1;
			++pc_arg1,++pc_arg2 )
	{
		std::string text1 = (*pc_arg1)->getText();
		std::string text2 = (*pc_arg2)->getText();

		state.ResultNodeList.push_back(
				state.pStack->createTempNode(
					text1.find(text2)!=std::string::npos ? "true" : "false"
					)
				);
	}
	return true;
}
