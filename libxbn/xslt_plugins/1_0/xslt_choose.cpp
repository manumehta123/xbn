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

xsltplugin_xsl_choose::xsltplugin_xsl_choose( )
{
	name = "xsl:choose";
	min_parameter=0;
	max_parameter=0;
	/*
The <xsl:choose> element is used in conjunction with <xsl:when> and <xsl:otherwise> to express multiple conditional tests.

If no <xsl:when> is true, the content of <xsl:otherwise> is processed.

If no <xsl:when> is true, and no <xsl:otherwise> element is present, nothing is created.

Tip: For simple conditional testing, use the <xsl:if> element instead.
	  */
}

bool xsltplugin_xsl_choose::testUnit()
{
	return true;
}

bool xsltplugin_xsl_choose::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	// xsl:when und xsl:otherwise
	xbnode_list col_child_nodes;
	state.pTemplateNode->getChildNodes( col_child_nodes, xbnode::xbn_node );

	for(xbnode_list::iterator pc=col_child_nodes.begin(), pe=col_child_nodes.end(); pc!=pe ; ++pc )
	{
		xbn_state child_state(state);
		child_state.pTemplateNode = *pc;
		if( p_xbn_xslt->process( child_state ) )
		{
			break;
		}
	}
	return true;
}

//----------------------------------------------------------------------------------------------------------------------

xsltplugin_xsl_when::xsltplugin_xsl_when( )
{
	name = "xsl:when";
	min_parameter=1;
	max_parameter=1;
	/*
The <xsl:when> element is used to specify an action for the <xsl:choose> element.
The <xsl:when> element evaluates an expression, and if it returns true, an action is performed.

Note: The <xsl:when> element is used in conjunction with <xsl:choose> and <xsl:otherwise> to express multiple conditional tests.

test	boolean-expression	Required. Specifies a Boolean expression to be tested
*/
	addParameter("test",	false,	"boolean-expression");
}

bool xsltplugin_xsl_when::testUnit()
{
	return true;
}

bool xsltplugin_xsl_when::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	std::string param_test =		state.pTemplateNode->getAttributeText( "test" );

	sptr<xbnode> result_node = xbn_xpath::selectNode( state.pSourceNode, param_test, state.pStack );

	if( result_node && result_node->isBool() )
	{
		if( result_node->getBool() )
		{
			return p_xbn_xslt->process_template( state );
		}
		return false;
	}
	p_xbn_xslt->raiseError( name+"() result is not an boolean", &state, __FILE__, __LINE__ );
	return false;
}

//----------------------------------------------------------------------------------------------------------------------

xsltplugin_xsl_otherwise::xsltplugin_xsl_otherwise( )
{
	name = "xsl:otherwise";
	min_parameter=0;
	max_parameter=0;
	/*
The <xsl:otherwise> element specifies a default action for the <xsl:choose> element.
This action will take place when none of the <xsl:when> conditions apply.
	  */
}

bool xsltplugin_xsl_otherwise::testUnit()
{
	return false;
}

bool xsltplugin_xsl_otherwise::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	return p_xbn_xslt->process_template( state );
}
