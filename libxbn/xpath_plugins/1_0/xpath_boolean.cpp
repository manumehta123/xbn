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

xpathplugin_boolean::xpathplugin_boolean()
{
	min_parameter = 1;
	max_parameter = 1;
	name          = "bool";
}
bool            xpathplugin_boolean::testUnit()
{
	return testPass( "bool(1)", 1, xbnode::xbn_temp, "true" )
			&testPass( "bool(0)", 1, xbnode::xbn_temp, "false" )
			&testPass( "bool('Hallo')", 1, xbnode::xbn_temp, "true" )
			&testPass( "bool('')", 1, xbnode::xbn_temp, "false" );
}
bool            xpathplugin_boolean::operator() (xbn_state &state, xbn_xpath *pxpath )
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
		if( (*pc_arg1)->getBool() )
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
xpathplugin_true::xpathplugin_true()
{
	min_parameter = 0;
	max_parameter = 0;
	name          = "true";
}
bool            xpathplugin_true::testUnit()
{
	return testPass( "true()", 1, xbnode::xbn_temp, "true" );
}
bool            xpathplugin_true::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
	{
		pxpath->raiseError( name+"() missing current node", &state, __FILE__,__LINE__ );
		return false;
	}

	state.ResultNodeList.push_back(  state.pStack->createTempNode( "true" ) );
	return true;
}

//----------------------------------------------------------------------------------------------------------------------
xpathplugin_false::xpathplugin_false()
{
	min_parameter = 1;
	max_parameter = 1;
	name          = "false";
}
bool            xpathplugin_false::testUnit()
{
	return testPass( "false()", 1, xbnode::xbn_temp, "false" );
}
bool            xpathplugin_false::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
	{
		pxpath->raiseError( name+"() missing current node", &state, __FILE__,__LINE__ );
		return false;
	}

	state.ResultNodeList.push_back(  state.pStack->createTempNode( "false" ) );
	return true;
}

//----------------------------------------------------------------------------------------------------------------------
xpathplugin_not::xpathplugin_not()
{
	min_parameter = 1;
	max_parameter = 1;
	name          = "not";
}
bool            xpathplugin_not::testUnit()
{
	return testPass( "not(true())", 1, xbnode::xbn_temp, "false" )
			&testPass( "not(false())", 1, xbnode::xbn_temp, "true" )
			&testPass( "not('Hallo')", 1, xbnode::xbn_temp, "false" )
			&testPass( "not('')", 1, xbnode::xbn_temp, "true" );
}
bool            xpathplugin_not::operator() (xbn_state &state, xbn_xpath *pxpath )
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
		if( (*pc_arg1)->getBool() )
			state.ResultNodeList.push_back(  state.pStack->createTempNode( "false" ) );
		else
			state.ResultNodeList.push_back(  state.pStack->createTempNode( "true" ) );
	}

	return true;
}
