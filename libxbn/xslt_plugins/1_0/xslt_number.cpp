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


xsltplugin_xsl_number::xsltplugin_xsl_number( )
{
	name = "xsl:number";
	min_parameter=0;
	max_parameter=9;
	/*
		The <xsl:number> element is used to determine the integer position of the
		current node in the source. It is also used to format a number.

count	expression	Optional. An XPath expression that specifies what nodes are to be counted
level	single
multiple
any	Optional. Controls how the sequence number is assigned
Can be one of the following:

single (default)
multiple
any (not supported by Netscape 6)
from	expression	Optional. An XPath expression that specifies where the counting will start
value	expression	Optional. Specifies a user-provided number that is used in place of a sequence generated number
format	formatstring	Optional. Defines the output format for the number. Can be one of the following:
format="1" results in 1 2 3 . .
format="01" results in 01 02 03 (not supported by Netscape 6)
format="a" results in a b c . . (not supported by Netscape 6)
format="A" results in A B C. . (not supported by Netscape 6)
format="i" results in i ii iii iv . . (not supported by Netscape 6)
format="I" results in I II III IV . . (not supported by Netscape 6)
lang	languagecode	Optional. Specifies the language alphabet to be used for the numbering (Not supported by Netscape 6)
letter-value	alphabetic
traditional	Optional. Specifies whether the numbering in the selected language is alphabetic or traditional. The default is alphabetic
grouping-separator	character	Optional. Specifies what character should be used to separate groups of digits. The default is the comma
grouping-size	number	Optional. Specifies how many digits are in the groups that are being separated by the character specified in the grouping-separator attribute. The default is 3
	  */
	addParameter("count",	true,	"expression");
	addParameter("level",	true,	"single|multiple|any");
	addParameter("from",	true,	"expression");
	addParameter("value",	true,	"expression");
	addParameter("format",	true,	"formatstring");
	addParameter("lang",	true,	"languagecode");
	addParameter("letter-value",	true,	"alphabetic|traditional");
	addParameter("grouping-separator",	true,	"character");
	addParameter("grouping-size",	true,	"number");
}

bool xsltplugin_xsl_number::testUnit()
{
	return false;
}

bool xsltplugin_xsl_number::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	p_xbn_xslt->raiseError( name+" not implemented yet", &state, __FILE__, __LINE__ );
	return false;
}


//----------------------------------------------------------------------------------------------------------------------

xsltplugin_xsl_decimal_format::xsltplugin_xsl_decimal_format( )
{
	name = "xsl:decimal-format";
	min_parameter=0;
	max_parameter=11;
	/*
The <xsl:decimal-format> element defines the characters and symbols to be used when
converting numbers into strings, with the format-number() function.

All countries do not use the same characters for separating the decimal part from
the integer part, and for grouping digits. With the <xsl:decimal-format> element
you can change special characters to other symbols.

This element is a top level element.

The format-number() function can refer to the <xsl:decimal-format> element by name.

name	name	Optional. Specifies a name for this format
decimal-separator	char	Optional. Specifies the decimal point character. Default is "."
grouping-separator	char	Optional. Specifies the thousands separator character. Default is ","
infinity	string	Optional. Specifies the string used to represent infinity. Default is "Infinity"
minus-sign	char	Optional. Specifies the character to represent negative numbers. Default is "-"
NaN	string	Optional. Specifies the string used when the value is not a number". Default is "NaN"
percent	char	Optional. Specifies the percentage sign character. Default is "%"
per-mille	char	Optional. Specifies the per thousand sign character. Default is "?"
zero-digit	char	Optional. Specifies the digit zero character. Default is "0"
digit	char	Optional. Specifies the character used to indicate a place where a digit is required. Default is #
pattern-separator	char	Optional. Specifies the character used to separate positive and negative subpatterns in a format pattern. Default is ";"
	  */
	addParameter("name",	true,	"name");
	addParameter("decimal-separator",	true,	"char");
	addParameter("grouping-separator",	true,	"char");
	addParameter("infinity",	true,	"string");
	addParameter("minus-sign",	true,	"char");
	addParameter("NaN	string",	true,	"string");
	addParameter("percent",	true,	"char");
	addParameter("per-mille",	true,	"char");
	addParameter("zero-digit",	true,	"char");
	addParameter("digit",	true,	"char");
	addParameter("pattern-separator",	true,	"char");
}

bool xsltplugin_xsl_decimal_format::testUnit()
{
	return false;
}

bool xsltplugin_xsl_decimal_format::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	p_xbn_xslt->raiseError( name+" not implemented yet", &state, __FILE__, __LINE__ );
	return false;
}

