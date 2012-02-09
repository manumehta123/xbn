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


xsltplugin_xsl_call_template::xsltplugin_xsl_call_template( )
{
	name = "xsl:call-template";
	min_parameter=1;
	max_parameter=1;

	/*
	  The <xsl:call-template> element calls a named template.

	  name	templatename	Required. Specifies the name of the template to be called
	  */
	addParameter("name",	false,	"name");
}

bool xsltplugin_xsl_call_template::testUnit()
{

	return true;
}

bool xsltplugin_xsl_call_template::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	std::string param_name =		state.pTemplateNode->getAttributeText( "name" );

	state.pStack->pushRange();

	xbnode_list col_param;
	state.pTemplateNode->getChildNodes( col_param, false, xbnode::xbn_node );

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

	// Template aufrufen
	sptr<xbnode> tmp = p_xbn_xslt->getTemplateName( param_name, "" );
	if( tmp )
	{
		xbn_state sub_state( state );
		sub_state.pTemplateNode = tmp;
		bool ret= p_xbn_xslt->process_template( sub_state );
		state.pStack->popRange();
		return ret;
	}
	state.pStack->popRange();
	return false;
}

