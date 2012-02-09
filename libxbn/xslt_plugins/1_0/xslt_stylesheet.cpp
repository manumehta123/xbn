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

xsltplugin_xsl_stylesheet::xsltplugin_xsl_stylesheet( )
{
	name = "xsl:stylesheet";
	min_parameter=1;
	max_parameter=4;
	/*
The <xsl:stylesheet> and <xsl:transform> elements are completely synonymous
elements. Both are used to define the root element of the style sheet.



version	version	Required. Specifies the XSLT version of the style sheet
extension-element-prefixes	list	Optional. A white space separated list of namespace prefixes used for extension elements
This attribute is not supported by Netscape 6

exclude-result-prefixes	list	Optional. A white space separated list of namespace prefixes that should not be sent to the output
id	name	Optional. A unique id for the style sheet
This attribute is not supported by Netscape 6
	  */
	addParameter("version",	false,	"version");
	addParameter("extension-element-prefixes",	true,	"list");
	addParameter("exclude-result-prefixes",	true,	"list");
	addParameter("id",	true,	"name");
}

bool xsltplugin_xsl_stylesheet::testUnit()
{
	return false;
}

bool xsltplugin_xsl_stylesheet::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	p_xbn_xslt->raiseError( name+" not implemented yet", &state, __FILE__, __LINE__ );
	return false;
}


//----------------------------------------------------------------------------------------------------------------------

xsltplugin_xsl_transform::xsltplugin_xsl_transform( )
{
	name = "xsl:transform";
	min_parameter=1;
	max_parameter=4;
	/*
version	version	Required. Specifies the XSLT version of the style sheet
extension-element-prefixes	list	Optional. A white space separated list of namespace prefixes used for extension elements
This attribute is not supported by Netscape 6

exclude-result-prefixes	list	Optional. A white space separated list of namespace prefixes that should not be sent to the output
id	name	Optional. A unique id for the style sheet
This attribute is not supported by Netscape 6
	  */
	addParameter("version",	false,	"version");
	addParameter("extension-element-prefixes",	true,	"list");
	addParameter("exclude-result-prefixes",	true,	"list");
	addParameter("id",	true,	"name");
}

bool xsltplugin_xsl_transform::testUnit()
{
	return false;
}

bool xsltplugin_xsl_transform::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	p_xbn_xslt->raiseError( name+" not implemented yet", &state, __FILE__, __LINE__ );
	return false;
}


