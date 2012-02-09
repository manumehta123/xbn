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



xsltplugin_xsl_value_of::xsltplugin_xsl_value_of( )
{
	name = "xsl:value-of";
	min_parameter=1;
	max_parameter=2;
	/*
The <xsl:value-of> element element extracts the value of a selected node.

The <xsl:value-of> element can be used to select the value of an XML element and add it to the output.

select	expression	Required. An XPath expression that specifies which node/attribute to extract the value from. It works like navigating a file system where a forward slash (/) selects subdirectories.
disable-output-escaping	yes
no	Optional. "yes" indicates that special characters (like "<") should be output as is. "no" indicates that special characters (like "<") should be output as "&lt;". Default is "no"
	  */
	addParameter("select",	false,	"expression");
	addParameter("disable-output-escaping",	true,	"yes|no");
}

bool xsltplugin_xsl_value_of::testUnit()
{
	return false;
}

bool xsltplugin_xsl_value_of::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	if( !p_xbn_xslt ) return false;
	std::string param_select =		state.pTemplateNode->getAttributeText( "select" );
	std::string param_disable_output_escaping  =		state.pTemplateNode->getAttributeText( "disable-output-escaping","no" );

	// Betroffene nodes
	xbnode_list node_col;
	xbn_xpath::selectNodes( state.pSourceNode, node_col, param_select, state.pStack );

	bool ret = true;
	for(xbnode_list::iterator pc=node_col.begin(), pe=node_col.end(); pc!=pe && ret; ++pc )
	{
		std::string wert = (*pc)->getText();
		if( !wert.empty() )
		{
			state.pCurrentNode->appendText( wert );
		}
	}
	return ret;
}

