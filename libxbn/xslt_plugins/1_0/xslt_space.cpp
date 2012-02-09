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


xsltplugin_xsl_preserve_space::xsltplugin_xsl_preserve_space( )
{
	name = "xsl:preserve-space";
	min_parameter=0;
	max_parameter=1;
	/*
The <xsl:preserve-space> element is used to define the elements for which white space should be preserved.

The <xsl:strip-space> element is used to define the elements for which white space should be removed.

Note: Preserving white space is the default setting, so using the <xsl:preserve-space> element is only necessary if  the <xsl:strip-space> element is used.

Note: The <xsl:preserve-space> element and the <xsl:strip-space> element are top-level elements

elements	list-of-element-names
Required. A white space separated list of element names for which white space should be preserved/removed.

Note: The list can also contain "*" and "prefix:*" so that all elements or all elements from a particular namespace can be joined
	  */
	addParameter("elements",	false,	"list-of-element-names");
}

bool xsltplugin_xsl_preserve_space::testUnit()
{
	return false;
}

bool xsltplugin_xsl_preserve_space::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	p_xbn_xslt->raiseError( name+" not implemented yet", &state, __FILE__, __LINE__ );
	return false;
}


//----------------------------------------------------------------------------------------------------------------------

xsltplugin_xsl_strip_space::xsltplugin_xsl_strip_space( )
{
	name = "xsl:strip-space";
	min_parameter=1;
	max_parameter=1;
	/*
The <xsl:preserve-space> element is used to define the elements for which white space should be preserved.

The <xsl:strip-space> element is used to define the elements for which white space should be removed.

Note: Preserving white space is the default setting, so using the <xsl:preserve-space> element is only necessary if  the <xsl:strip-space> element is used.

Note: The <xsl:preserve-space> element and the <xsl:strip-space> element are top-level elements.

elements	list-of-element-names
Required. A white space separated list of element names for which white space should be preserved/removed.

Note: The list can also contain "*" and "prefix:*" so that all elements or all elements from a particular namespace can be joined
	  */
	addParameter("elements",	false,	"list-of-element-names");
}

bool xsltplugin_xsl_strip_space::testUnit()
{
	return false;
}

bool xsltplugin_xsl_strip_space::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	p_xbn_xslt->raiseError( name+" not implemented yet", &state, __FILE__, __LINE__ );
	return false;
}

