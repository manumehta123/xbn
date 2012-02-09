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


xsltplugin_xsl_variable::xsltplugin_xsl_variable(  )
{
	name = "xsl:variable";
	min_parameter=1;
	max_parameter=2;
	/*
The <xsl:variable> element is used to declare a local or global variable.

Note: The variable is global if it's declared as a top-level element, and local if it's declared within a template.

Note: Once you have set a variable's value, you cannot change or modify that value!

Tip: You can add a value to a variable by the content of the <xsl:variable> element OR by the select attribute!

name	name	Required. Specifies the name of the variable
select	expression	Optional. Defines the value of the variable
	  */
	addParameter("name",	false,	"name");
	addParameter("select",	true,	"expression");
}

bool xsltplugin_xsl_variable::testUnit()
{
	return true;
}

bool xsltplugin_xsl_variable::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	if( !p_xbn_xslt ) return false;
	std::string param_name =		state.pTemplateNode->getAttributeText( "name" );
	std::string param_select =		state.pTemplateNode->getAttributeText( "select" );

	if( param_select!="" )
	{
		state.pStack->insertVariable( param_name, xbn_xpath::selectNode( state.pSourceNode, param_select, state.pStack ) );
	}
	else
	{
		state.pStack->insertVariable( param_name, state.pTemplateNode );
	}
	return false;
}

