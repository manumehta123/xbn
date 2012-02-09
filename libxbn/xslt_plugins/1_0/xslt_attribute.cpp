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



xsltplugin_xsl_attribute::xsltplugin_xsl_attribute( )
{
	name = "xsl:attribute";
	min_parameter=1;
	max_parameter=2;
	/*
The <xsl:attribute> element is used to add attributes to elements.

Note: The <xsl:attribute> element replaces existing attributes with equivalent  names.

name	attributename	Required. Specifies the name of the attribute
namespace	URI	Optional. Defines the namespace URI for the attribute
	 */
	addParameter("name",	false,	"attributename");
	addParameter("namespace",	true,	"URI");
}

bool xsltplugin_xsl_attribute::testUnit()
{
	return true;
}

bool xsltplugin_xsl_attribute::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	std::string param_name =		state.pTemplateNode->getAttributeText( "name" );
	std::string param_namespace  =	state.pTemplateNode->getAttributeText( "namespace" );

	std::string wert = state.pTemplateNode->getText();
	state.pCurrentNode->setAttributeText( param_name, wert );

	return p_xbn_xslt->process_template( state );
}

//----------------------------------------------------------------------------------------------------------------------

xsltplugin_xsl_attribute_set::xsltplugin_xsl_attribute_set( )
{
	name = "xsl:attribute-set";
	min_parameter=1;
	max_parameter=2;
	/*
The <xsl:attribute-set> element creates a named set of attributes. The attribute-set
can be applied as whole to the output document.

Note: Must be child of <xsl:stylesheet> or <xsl:transform>.

name	name	Required. Specifies the name of the attribute-set
use-attribute-sets	name-list	Optional. A white space separated list of other attribute-sets to use in the attribute-set
	  */
	addParameter("name",	false,	"name");
	addParameter("use-attribute-sets",	true,	"name-list");
}

bool xsltplugin_xsl_attribute_set::testUnit()
{
	return false;
}

bool xsltplugin_xsl_attribute_set::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	p_xbn_xslt->raiseError( name+" not implemented yet", &state, __FILE__, __LINE__ );
	return false;
}

