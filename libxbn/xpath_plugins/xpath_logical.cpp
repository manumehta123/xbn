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
#include "xbn_xpath_plugins.h"
#include "xbn_helper.h"
#include "xbn_document.h"

xpathplugin_xbn_and::xpathplugin_xbn_and()
{
	min_parameter = 2;
	max_parameter = 2;
	name          = "xbn:and";
}
bool            xpathplugin_xbn_and::testUnit()
{
	return	testPass("true() and true()"	, 1, xbnode::xbn_temp, "true")
		&	testPass("true() and false()"	, 1, xbnode::xbn_temp, "false")
		&	testPass("false() and true()"	, 1, xbnode::xbn_temp, "false")
		&	testPass("false() and false()"	, 1, xbnode::xbn_temp, "false");
}
bool            xpathplugin_xbn_and::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
		return false;

	xbn_state arg1(state);
	if( !pxpath->process( arg1, *(state.pCurrent_token) ) )
		return false;

	xbn_state arg2(state);
	if( !pxpath->process( arg2, *(state.pCurrent_token) ) )
		return false;

	if( arg1.ResultNodeList.size()!=arg2.ResultNodeList.size() &&
		(arg1.ResultNodeList.size()>1&&
		 arg2.ResultNodeList.size()>1) )
	{
		pxpath->raiseError( name+"() resultsizes arg1,arg2 does not match",&state, __FILE__, __LINE__ );
		return false;
	}

	for( xbnode_list::iterator pc_arg1=arg1.ResultNodeList.begin(),pe_arg1=arg1.ResultNodeList.end(),
							   pc_arg2=arg2.ResultNodeList.begin(),pe_arg2=arg2.ResultNodeList.end();
			pc_arg1!=pe_arg1 && pc_arg2!=pe_arg2;
			++pc_arg1,++pc_arg2 )
	{
		if( pc_arg1==pe_arg1 ) pc_arg1=arg1.ResultNodeList.begin();
		if( pc_arg2==pe_arg2 ) pc_arg2=arg2.ResultNodeList.begin();

		if( (*pc_arg1)->getBool() && (*pc_arg2)->getBool() )
		{
			state.ResultNodeList.push_back(  state.pStack->createTempNode("true") );
		}
		else
		{
			state.ResultNodeList.push_back(  state.pStack->createTempNode("false") );
		}
	}
	return true;
}

//----------------------------------------------------------------------------------------------------------------------
xpathplugin_xbn_or::xpathplugin_xbn_or()
{
	min_parameter = 2;
	max_parameter = 2;
	name          = "xbn:or";
}
bool            xpathplugin_xbn_or::testUnit()
{
	return	testPass("true() or true()"		, 1, xbnode::xbn_temp, "true")
		|	testPass("true() or false()"	, 1, xbnode::xbn_temp, "true")
		|	testPass("false() or true()"	, 1, xbnode::xbn_temp, "true")
		|	testPass("false() or false()"	, 1, xbnode::xbn_temp, "false");
}
bool           xpathplugin_xbn_or:: operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
		return false;

	xbn_state arg1(state);
	if( !pxpath->process( arg1, *(state.pCurrent_token) ) )
		return false;

	xbn_state arg2(state);
	if( !pxpath->process( arg2, *(state.pCurrent_token) ) )
		return false;

	if( arg1.ResultNodeList.size()!=arg2.ResultNodeList.size() &&
		(arg1.ResultNodeList.size()>1&&
		 arg2.ResultNodeList.size()>1) )
	{
		pxpath->raiseError( name+"() resultsizes arg1,arg2 does not match",&state, __FILE__, __LINE__ );
		return false;
	}

	for( xbnode_list::iterator pc_arg1=arg1.ResultNodeList.begin(),pe_arg1=arg1.ResultNodeList.end(),
							   pc_arg2=arg2.ResultNodeList.begin(),pe_arg2=arg2.ResultNodeList.end();
			pc_arg1!=pe_arg1 && pc_arg2!=pe_arg2;
			++pc_arg1,++pc_arg2 )
	{
		if( pc_arg1==pe_arg1 ) pc_arg1=arg1.ResultNodeList.begin();
		if( pc_arg2==pe_arg2 ) pc_arg2=arg2.ResultNodeList.begin();

		if( (*pc_arg1)->getBool() || (*pc_arg2)->getBool() )
		{
			state.ResultNodeList.push_back( state.pStack->createTempNode("true") );
		}
		else
		{
			state.ResultNodeList.push_back( state.pStack->createTempNode("false") );
		}
	}
	return true;
}
