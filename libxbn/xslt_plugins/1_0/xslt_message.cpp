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


xsltplugin_xsl_message::xsltplugin_xsl_message( )
{
	name = "xsl:message";
	min_parameter=0;
	max_parameter=1;
	/*
The <xsl:message> element writes a message to the output. This element is primarily used to report errors.

This element can contain almost any other XSL element (<xsl:text>, <xsl:value-of>, etc.).

The terminate attribute gives you the choice to either quit or continue the processing when an error occurs.

terminate	yes
no	Optional. "yes" terminates the processing after the message is written to the output. "no" continues the processing after the message is written to the output. Default is "no".
	  */
	addParameter("terminate",	true,	"yes|no");
}

bool xsltplugin_xsl_message::testUnit()
{
	return true;
}

bool xsltplugin_xsl_message::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	std::string param_terminate = state.pTemplateNode->getAttributeText( "terminate","no" );
	p_xbn_xslt->raiseError( state.pTemplateNode->getText(), &state, __FILE__, __LINE__ );
	return param_terminate=="no";
}

