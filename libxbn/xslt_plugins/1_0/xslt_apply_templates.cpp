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


xsltplugin_xsl_apply_templates::xsltplugin_xsl_apply_templates( )
{
	name = "xsl:apply-templates";
	min_parameter=0;
	max_parameter=2;
	/*
The <xsl:apply-templates> element applies a template to the current element or to the current element's child nodes.

If we add a select attribute to the <xsl:apply-templates> element it will process only the
child element that matches the value of the attribute. We can use the select attribute to
specify in which order the child nodes are to be processed.

select	expression	Optional. Specifies the nodes to be processed. An asterisk selects the entire node-set. If this attribute is omitted, all child nodes of the current node will be selected
mode	name		Optional. If there are multiple ways of processing defined for the same element, distinguishes among them

<!-- Content:(xsl:sort|xsl:with-param)* -->
*/
	addParameter("select",	true,	"expression");
	addParameter("mode",	true,	"name");
}

bool xsltplugin_xsl_apply_templates::testUnit()
{
	return true;
}

bool xsltplugin_xsl_apply_templates::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	std::string param_select =		state.pTemplateNode->getAttributeText( "select", "*" );
	std::string param_mode  =		state.pTemplateNode->getAttributeText( "mode" );

	state.pStack->pushRange();

	// WithParam Parameter
	xbnode_list col_param;
	xbn_xpath::selectNodes( state.pTemplateNode, col_param, "xsl:with-param" );

	for( xbnode_list::iterator pc=col_param.begin(), pe=col_param.end(); pc!=pe; ++pc )
	{
		if( (*pc)->getFullname()=="xsl:with-param" )
		{
			// ToDo: Parameter
			xbn_state sub_state( state );
			sub_state.pTemplateNode = (*pc);
			if( !p_xbn_xslt->process( sub_state ) )
				return false;
		}
		else
		{
			p_xbn_xslt->raiseError( name+"() only xsl:with-param allowed! "+(*pc)->getFullname() );
			return false;
		}
	}

	// Betroffene nodes
	xbnode_list node_col;
	xbn_xpath::selectNodes( state.pSourceNode, node_col, param_select, state.pStack );

	// Sort Parameter
	sptr<xbnode> param_xsl_sort = xbn_xpath::selectNode( state.pTemplateNode, "xsl:sort" );
	if( param_xsl_sort )
	{
		// sort aufrufen
		xsltplugin_xsl_sort::sort( param_xsl_sort, node_col, state, p_xbn_xslt );
	}

	bool ret = true;
	for(xbnode_list::iterator pc=node_col.begin(), pe=node_col.end(); pc!=pe && ret; ++pc )
	{
		xbn_state child_state(state);

		// Template bestimmen
		child_state.pSourceNode = *pc;
		child_state.pTemplateNode = p_xbn_xslt->getTemplateMatch( child_state.pSourceNode->getFullname(), param_mode );


		if( child_state.pTemplateNode )
		{
			ret &= p_xbn_xslt->process( child_state );
		}
	}
	state.pStack->popRange();
	return ret;
}
