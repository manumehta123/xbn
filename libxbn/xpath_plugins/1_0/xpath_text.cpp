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

xpathplugin_text::xpathplugin_text()
{
	min_parameter = 0;
	max_parameter = 0;
	name          = "text";
}
bool            xpathplugin_text::testUnit()
{
	return testPass( "/test/d/name/text()", 1, xbnode::xbn_text, "hund" );
}
bool            xpathplugin_text::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
	{
		pxpath->raiseError( name+"() missing current node", &state, __FILE__,__LINE__ );
		return false;
	}

	state.pCurrentNode->getChildNodes(  state.ResultNodeList, false, xbnode::xbn_text|xbnode::xbn_cdata );
	return true;
}

xpathplugin_comment::xpathplugin_comment()
{
	min_parameter = 0;
	max_parameter = 0;
	name          = "comment";
}
bool            xpathplugin_comment::testUnit()
{
	return testPass( "/test/comment()", 1, xbnode::xbn_comment, " und noch ein Comment" );
}
bool            xpathplugin_comment::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
	{
		pxpath->raiseError( name+"() missing current node", &state, __FILE__,__LINE__ );
		return false;
	}

	state.pCurrentNode->getChildNodes(  state.ResultNodeList, false, xbnode::xbn_comment );
	return true;
}


xpathplugin_node::xpathplugin_node()
{
	min_parameter = 0;
	max_parameter = 0;
	name          = "node";
}
bool            xpathplugin_node::testUnit()
{
	return testPass( "/test/node()", 7, xbnode::xbn_mask_all, "" );
}
bool            xpathplugin_node::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
	{
		pxpath->raiseError( name+"() missing current node", &state, __FILE__,__LINE__ );
		return false;
	}

	state.pCurrentNode->getChildNodes(  state.ResultNodeList, false, xbnode::xbn_mask_all );
	return true;
}
