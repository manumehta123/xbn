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


xsltplugin_xsl_namespace_alias::xsltplugin_xsl_namespace_alias( )
{
	name = "xsl:namespace-alias";
	min_parameter=2;
	max_parameter=2;

	/*
The <xsl:namespace-alias> element is used to replace a namespace in the style sheet to a different namespace in the output.

Note: <xsl:namespace-alias> is a top-level element, and must be a child node of <xsl:stylesheet> or <xsl:transform>.

stylesheet-prefix	prefix
#default	Required. Specifies the namespace you wish to change
result-prefix	prefix
#default	Requ
	  */
	addParameter("stylesheet-prefix",	false,	"prefix");
	addParameter("result-prefix",	false,	"prefix");
}

bool xsltplugin_xsl_namespace_alias::testUnit()
{
	return false;
}

bool xsltplugin_xsl_namespace_alias::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	p_xbn_xslt->raiseError( name+" not implemented yet", &state, __FILE__, __LINE__ );
	return false;
}

