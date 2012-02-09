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


xsltplugin_xsl_for_each::xsltplugin_xsl_for_each( )
{
	name = "xsl:for-each";
	min_parameter=1;
	max_parameter=1;
	/*
	  The <xsl:for-each> element loops through each node in a specified node set.

	select	expression	Required. An XPath expression that specifies which node set to be processed.
	*/
	addParameter("select",	false,	"expression");
}

bool xsltplugin_xsl_for_each::testUnit()
{
	return true;
}

bool xsltplugin_xsl_for_each::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	std::string param_select =		state.pTemplateNode->getAttributeText( "select", "*" );

	// Sort Parameter auslesen
	sptr<xbnode> param_xsl_sort = xbn_xpath::selectNode( state.pTemplateNode, "xsl:sort" );

	// Betroffene nodes
	xbnode_list node_col;
	xbn_xpath::selectNodes( state.pSourceNode, node_col, param_select, state.pStack );

	if( param_xsl_sort )
	{
		// sort aufrufen
		xsltplugin_xsl_sort::sort( param_xsl_sort, node_col, state, p_xbn_xslt );
	}

	bool ret = true;
	for(xbnode_list::iterator pc=node_col.begin(), pe=node_col.end(); pc!=pe && ret; ++pc )
	{
		xbn_state child_state(state);

		// Template bestimmen
		child_state.pSourceNode = *pc;
		ret &= p_xbn_xslt->process_template( child_state );
	}
	return ret;
}
