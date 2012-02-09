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
#include "xslt_plugins/xbn_xslt_plugins_1_0.h"
#include "xbn_xpath.h"


xsltplugin_xsl_copy::xsltplugin_xsl_copy( )
{
	name = "xsl:copy";
	min_parameter=0;
	max_parameter=1;

	/*
The <xsl:copy> element creates a copy of the current node.

Note: Namespace nodes of the current node are automatically copied as well, but
 child nodes and attributes of the current node are not automatically copied!

	  use-attribute-sets	name-list	Optional. A white space separated list of attribute-sets to apply to the output node, if the node is an element
	  */
	addParameter("use-attribute-sets",	true,	"name-list");
}

bool xsltplugin_xsl_copy::testUnit()
{
	return true;
}

bool xsltplugin_xsl_copy::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	if( !p_xbn_xslt ) return false;
	state.pTemplateNode->cloneNode( state.pCurrentNode, 0 );
	return true;
}

//----------------------------------------------------------------------------------------------------------------------

xsltplugin_xsl_copy_of::xsltplugin_xsl_copy_of( )
{
	name = "xsl:copy-of";
	min_parameter=1;
	max_parameter=1;
	/*
The <xsl:copy-of> element creates a copy of the current node.

Note: Namespace nodes, child nodes, and attributes of the current node are automatically copied as well!

Tip: This element can be used to insert multiple copies of the same node into different places in the output.

	  select	expression	Required. Specifies what to be copied
	  */
	addParameter("select",	false,	"expression");
}

bool xsltplugin_xsl_copy_of::testUnit()
{
	return true;
}

bool xsltplugin_xsl_copy_of::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	if( !p_xbn_xslt ) return false;
	std::string param_select =		state.pTemplateNode->getAttributeText( "select", "*" );

	// Betroffene nodes
	xbnode_list node_col;
	xbn_xpath::selectNodes( state.pSourceNode, node_col, param_select, state.pStack );

	for(xbnode_list::iterator pc=node_col.begin(), pe=node_col.end(); pc!=pe; ++pc )
	{
		(*pc)->cloneNode( state.pCurrentNode, xbnode::xbn_attribute|xbnode::xbn_node|xbnode::xbn_text|xbnode::xbn_cdata );
	}
	return true;
}
