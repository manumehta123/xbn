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


xsltplugin_xsl_param::xsltplugin_xsl_param( )
{
	name = "xsl:param";
	min_parameter=1;
	max_parameter=2;
	/*
The <xsl:param> element is used to declare a local or global parameter.

Note: The parameter is global if it's declared as a top-level element, and local if it's declared within a template.

name	name	Required. Specifies the name of the parameter
select	expression	Optional. Specifies an XPath expression that specifies a default value for the parameter
	  */
	addParameter("name",	false,	"name");
	addParameter("select",	true,	"expression");
}

bool xsltplugin_xsl_param::testUnit()
{
	return true;
}

bool xsltplugin_xsl_param::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	std::string param_name =		state.pTemplateNode->getAttributeText( "name" );
	std::string param_select =		state.pTemplateNode->getAttributeText( "select" );

	if( state.pStack->getVariable( param_name ) )
		return true;

	sptr<xbnode> selection;
	if( param_select!="" )
	{
		xbn_xpath::selectNode( state.pSourceNode, param_select, state.pStack );
	}
	else
	{
		selection = state.pTemplateNode;
	}

	state.pStack->insertVariable( param_name, selection );
	return true;
}


//----------------------------------------------------------------------------------------------------------------------

xsltplugin_xsl_with_param::xsltplugin_xsl_with_param( )
{
	name = "xsl:with-param";
	min_parameter=1;
	max_parameter=2;
	/*
The <xsl:with-param> element defines the value of a parameter to be passed into a template.

Note: The value of the name attribute of <xsl:with-param> must match a name in an <xsl:param>
element (the <xsl:with-param> element is ignored if there is no match).

Note: The <xsl:with-param> element is allowed within <xsl:apply-templates> and <xsl:call-template>.

Tip: You can add a value to the parameter by the content of the <xsl:with-param> element OR by the select attribute!

name	name	Required. Specifies the name of the parameter
select	expression	Optional. An XPath expression that defines the value of the paramete
	  */
	addParameter("name",	false,	"name");
	addParameter("select",	true,	"expression");
}

bool xsltplugin_xsl_with_param::testUnit()
{
	return true;
}

bool xsltplugin_xsl_with_param::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	std::string param_name =		state.pTemplateNode->getAttributeText( "name" );
	std::string param_select =		state.pTemplateNode->getAttributeText( "select" );

	sptr<xbnode> selection;
	if( param_select!="" )
	{
		xbn_xpath::selectNode( state.pSourceNode, param_select, state.pStack );
	}
	else
	{
		selection = state.pTemplateNode;
	}

	state.pStack->insertVariable( param_name, selection );
	return true;
}
