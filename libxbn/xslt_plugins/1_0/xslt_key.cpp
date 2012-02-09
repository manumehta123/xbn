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


xsltplugin_xsl_key::xsltplugin_xsl_key( )
{
	name = "xsl:key";
	min_parameter=3;
	max_parameter=3;
	/*
The <xsl:key> element is a top-level element which declares a named key that can
be used in the style sheet with the key() function.

Note: A key does not have to be unique!

name	name	Required. Specifies the name of the key
match	pattern	Required. Defines the nodes to which the key will be applied
use	expression	Required. The value of the key for each of the nodes
	  */
	addParameter("name",	false,	"name");
	addParameter("match",	false,	"pattern");
	addParameter("use",	false,	"expression");
}

bool xsltplugin_xsl_key::testUnit()
{
	return false;
}

bool xsltplugin_xsl_key::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	p_xbn_xslt->raiseError( name+" not implemented yet", &state, __FILE__, __LINE__ );
	return false;
}

