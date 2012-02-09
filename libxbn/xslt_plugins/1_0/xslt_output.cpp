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


xsltplugin_xsl_output::xsltplugin_xsl_output( )
{
	name = "xsl:output";
	min_parameter=0;
	max_parameter=10;
	/*

The <xsl:output> element defines the format of the output document.

Note: <xsl:output> is a top-level element, and must appear as a child node of <xsl:stylesheet> or <xsl:transform>.

method	xml
html
text
name	Optional. Defines the output format. The default is XML (but if the first child of the root node is <html> and there are no preceding text nodes, then the default is HTML)
Netscape 6 only supports "html" and "xml"

version	string	Optional. Sets the W3C version number for the output format (only used with method="html" or method="xml")
encoding	string	Optional. Sets the value of the encoding attribute in the output
omit-xml-declaration	yes
no	Optional. "yes" specifies that the XML declaration (<?xml...?>) should be omitted in the output. "no" specifies that the XML declaration should be included in the output. The default is "no"
standalone	yes
no	Optional. "yes" specifies that a standalone declaration should occur in the output. "no" specifies that a standalone declaration should not occur in the output. The default is "no"
This attribute is not supported by Netscape 6

doctype-public	string	Optional. Sets the value of the PUBLIC attribute of the DOCTYPE declaration in the output
doctype-system	string	Optional. Sets the value of the SYSTEM attribute of the DOCTYPE declaration in the output
cdata-section-elements	namelist	Optional. A white-space separated list of elements whose text contents should be written as CDATA sections
indent	yes
no	Optional. "yes" indicates that the output should be indented according to its hierarchic structure. "no" indicates that the output should not be indented according to its hierarchic structure.
This attribute is not supported by Netscape 6

media-type	string	Optional. Defines the MIME type of the output. The default is "text/xml"
This attribute is not supported by Netscape 6
	  */
	addParameter("method",	true,	"xml|html|text|name");
	addParameter("version",	true,	"string");
	addParameter("encoding",	true,	"string");
	addParameter("omit-xml-declaration",	true,	"yes|no");
	addParameter("standalone",	true,	"yes|no");
	addParameter("doctype-public",	true,	"string");
	addParameter("doctype-system",	true,	"string");
	addParameter("cdata-section-elements",	true,	"namelist");
	addParameter("indent",	true,	"yes|no");
	addParameter("media-type",	true,	"string");
}

bool xsltplugin_xsl_output::testUnit()
{
	return false;
}

bool xsltplugin_xsl_output::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	p_xbn_xslt->raiseError( name+" not implemented yet", &state, __FILE__, __LINE__ );
	return false;
}
