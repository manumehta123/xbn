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


xsltplugin_xsl_template::xsltplugin_xsl_template()
{
	name = "xsl:template";
	min_parameter=0;
	max_parameter=4;
	/*

The <xsl:template> element contains rules to apply when a specified node is matched.

The match attribute is used to associate the template with an XML element. The match
attribute can also be used to define a template for a whole branch of the XML document
(i.e. match="/" defines the whole document).

Note: <xsl:template> is a top-level element.

name	name	Optional.	Specifies a name for the template.
							Note: If this attribute is omitted there must be a match attribute
match	pattern	Optional.	The match pattern for the template.
							Note: If this attribute is omitted there must be a name attribute
mode	mode	Optional.	Specifies a mode for this template
priority	number	Optional. A number which indicates the numeric priority of the template
	*/
	addParameter("name",	true,	"name");
	addParameter("match",	true,	"pattern");
	addParameter("mode",	true,	"mode");
	addParameter("priority",true,	"number");
}

bool xsltplugin_xsl_template::testUnit()
{
	return true;
}

bool xsltplugin_xsl_template::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	std::string param_name =		state.pTemplateNode->getAttributeText( "name" );
	std::string param_match =		state.pTemplateNode->getAttributeText( "match" );
	std::string param_mode =		state.pTemplateNode->getAttributeText( "mode" );
	std::string param_priority =	state.pTemplateNode->getAttributeText( "priority" );

	// Childnodes Parsen
	bool ret=true;
	xbnode_list col_child_nodes;
	state.pTemplateNode->getChildNodes( col_child_nodes, false, xbnode::xbn_node|xbnode::xbn_text|xbnode::xbn_cdata );

	if( !col_child_nodes.empty() )
	{
		state.pStack->pushRange();

		for(xbnode_list::iterator pc=col_child_nodes.begin(), pe=col_child_nodes.end(); pc!=pe && ret; ++pc )
		{
			xbn_state child_state(state);
			child_state.pTemplateNode = *pc;
			ret &= p_xbn_xslt->process( child_state );
		}

		state.pStack->popRange();
	}
	return ret;
}

