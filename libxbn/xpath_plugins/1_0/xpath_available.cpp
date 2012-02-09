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
#include "xbn_xslt.h"
#include "xbn_helper.h"
#include "xbstring.h"
#include "xbn_document.h"

xpathplugin_element_available::xpathplugin_element_available()
{
	min_parameter = 1;
	max_parameter = 1;
	name          = "element-available";
}
bool           xpathplugin_element_available:: testUnit()
{
	return testPass( "element-available('xsl:for-each')", 1, xbnode::xbn_temp, "true" );
}
bool            xpathplugin_element_available::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
		return false;

	xbn_state arg1(state);
	if( !pxpath->process( arg1, *(state.pCurrent_token) ) || arg1.ResultNodeList.empty() )
	{
		pxpath->raiseError( this->name + "() could not process arg1", &state,__FILE__,__LINE__ );
		return false;
	}
	std::string function = arg1.ResultNodeList.front()->getText();
	xbn_xslt_plugin_base* ptr_plugin = xbn_xslt::getPlugin( function );

	state.ResultNodeList.push_back(  state.pStack->createTempNode( ptr_plugin?"true":"false" ) );
	return true;
}

//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
xpathplugin_function_available::xpathplugin_function_available()
{
	min_parameter = 1;
	max_parameter = 1;
	name          = "function-available";
}
bool            xpathplugin_function_available::testUnit()
{
	return testPass( "function-available('function-available')", 1, xbnode::xbn_temp, "true" );
}
bool            xpathplugin_function_available::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
		return false;

	xbn_state arg1(state);
	if( !pxpath->process( arg1, *(state.pCurrent_token) ) )
	{
		pxpath->raiseError( this->name + "() could not process arg1", &state,__FILE__,__LINE__ );
		return false;
	}

	if( arg1.ResultNodeList.empty() )
	{
		pxpath->raiseError( this->name + "() could not process list arg1", &state,__FILE__,__LINE__ );
		return false;
	}
	std::string function = arg1.ResultNodeList.front()->getText();

	xbn_xpath_plugin_base* ptr_plugin = xbn_xpath::getPlugin( function );
	state.ResultNodeList.push_back(  state.pStack->createTempNode( ptr_plugin?"true":"false" ) );
	return true;
}

