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
#include <algorithm>

xsltplugin_xsl_sort::xsltplugin_xsl_sort( )
{
	name = "xsl:sort";
	min_parameter=0;
	max_parameter=5;
	/*
The <xsl:sort> element is used to sort the output.

Note: <xsl:sort> is always within <xsl:for-each> or <xsl:apply-templates>.

select	XPath-expression	Optional. Specifies which node/node-set to sort on
lang	language-code	Optional. Specifies which language is to be used by the sort
data-type	text
number
qname	Optional. Specifies the data-type of the data to be sorted. Default is "text"
order	ascending
descending	Optional. Specifies the sort order. Default is "ascending"
case-order	upper-first
lower-first	Optional. Specifies whether upper- or lowercase letters are to be ordered first
	  */
	addParameter("select",	true,	"expression");
	addParameter("lang",	true,	"language-code");
	addParameter("data-type",	true,	"text|number|qname");
	addParameter("order",	true,	"ascending|descending");
	addParameter("case-order",	true,	"upper-first|lower-first");
}

bool xsltplugin_xsl_sort::testUnit()
{
	return false;
}

bool xsltplugin_xsl_sort::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	p_xbn_xslt->raiseError( name+" not implemented yet", &state, __FILE__, __LINE__ );
	return false;
}

//------------------------------------------------------------------------------------------------------------
// Number
//------------------------------------------------------------------------------------------------------------
struct __sort__number_ascending
{
	std::string*   pSelect;
	xbn_state*     pState;

	bool operator() (sptr<xbnode> &v1, sptr<xbnode> &v2)
	{
		float v1_value = xbn_xpath::selectNumber( v1, *pSelect, 0, pState->pStack );
		float v2_value = xbn_xpath::selectNumber( v2, *pSelect, 0, pState->pStack );
		return v1_value<v2_value;
	}
};

struct __sort__number_descending
{
	std::string*     pSelect;
	xbn_state*       pState;

	bool operator() (sptr<xbnode> &v1, sptr<xbnode> &v2)
	{
		float v1_value = xbn_xpath::selectNumber( v1, *pSelect, 0, pState->pStack );
		float v2_value = xbn_xpath::selectNumber( v2, *pSelect, 0, pState->pStack );
		return v1_value>v2_value;
	}
};

//------------------------------------------------------------------------------------------------------------
// String
//------------------------------------------------------------------------------------------------------------
struct __sort__string_ascending
{
	std::string*     pSelect;
	xbn_state*       pState;

	bool operator() (sptr<xbnode> &v1, sptr<xbnode> &v2)
	{
		std::string v1_value = xbn_xpath::selectText( v1, *pSelect, "", pState->pStack );
		std::string v2_value = xbn_xpath::selectText( v2, *pSelect, "", pState->pStack );
		return v1_value<v2_value;
	}
};

struct __sort__string_descending
{
	std::string*     pSelect;
	xbn_state*       pState;

	bool operator() (sptr<xbnode> &v1, sptr<xbnode> &v2)
	{
		std::string v1_value = xbn_xpath::selectText( v1, *pSelect, "", pState->pStack );
		std::string v2_value = xbn_xpath::selectText( v2, *pSelect, "", pState->pStack );
		return v1_value>v2_value;
	}
};

bool xsltplugin_xsl_sort::sort( sptr<xbnode> sort_node, xbnode_list &col_liste, xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	std::string param_select	= sort_node->getAttributeText( "select" );
	std::string param_lang		= sort_node->getAttributeText( "lang" );
	std::string param_data_type = sort_node->getAttributeText( "data-type" );
	std::string param_order		= sort_node->getAttributeText( "order" );
	std::string param_case_order= sort_node->getAttributeText( "case-order" );

	uint_xbn mode=1;
	if( param_order=="ascending" )
	{
		mode=1;
	} else
	if( param_order=="descending" )
	{
		mode=2;
	}
	else
	{
		p_xbn_xslt->raiseError( "xsltplugin_xsl_sort::sort() not supported order mode [" + param_order + "]", &state, __FILE__, __LINE__ );
		return false;
	}

	if( param_data_type=="number" )
	{
		if( mode==1 )
		{
			__sort__number_ascending obj = { &param_select, &state };
			col_liste.sort( obj );
		}
		else
		{
			__sort__number_descending obj = { &param_select, &state };
			col_liste.sort( obj );
		}
	}
	else
	{
		if( mode==1 )
		{
			__sort__string_ascending obj = { &param_select, &state };
			col_liste.sort( obj );
		}
		else
		{
			__sort__string_descending obj = { &param_select, &state };
			col_liste.sort( obj );
		}
	}

	return true;
}
