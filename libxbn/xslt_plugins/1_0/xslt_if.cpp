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


xsltplugin_xsl_if::xsltplugin_xsl_if( )
{
	name = "xsl:if";
	min_parameter=1;
	max_parameter=1;
	/*
The <xsl:if> element contains a template that will be applied only if a specified condition is true.

Tip: Use <xsl:choose> in conjunction with <xsl:when> and <xsl:otherwise> to express multiple conditional tests!

	  test	expression	Required. Specifies the condition to be tested
	  */
	addParameter("test",	false,	"expression");
}

bool xsltplugin_xsl_if::testUnit()
{
	return true;
}

bool xsltplugin_xsl_if::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	std::string param_test =		state.pTemplateNode->getAttributeText( "test" );

	sptr<xbnode> result_node = xbn_xpath::selectNode( state.pSourceNode, param_test, state.pStack );

	if( result_node && result_node->isBool() )
	{
		if( result_node->getBool() )
		{
			return p_xbn_xslt->process_template( state );
		}
		return true;
	}
	p_xbn_xslt->raiseError( name+"() result is not an boolean", &state, __FILE__, __LINE__ );
	return false;
}

