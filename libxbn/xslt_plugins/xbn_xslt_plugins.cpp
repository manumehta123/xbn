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
#include "xbn_xslt_plugins.h"


xbn_xslt_plugin_base::xbn_xslt_plugin_base()
{
	name = "";
	min_parameter = 0;
	max_parameter = 0;
	parameter.clear();
}

xbn_xslt_plugin_base::~xbn_xslt_plugin_base()
{

}

void	xbn_xslt_plugin_base::addParameter( std::string name, bool optional, std::string type )
{
	parameter[ name ] = std::pair<bool,std::string>(optional,type);
}

bool	xbn_xslt_plugin_base::checkParameter( xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	if( parameter.empty() )
		return true;

	bool ret=true;
	for(parammap::iterator pc=parameter.begin(), pe=parameter.end(); pc!=pe; ++pc)
	{
		std::string param_name		= pc->first;
		bool		param_optional	= pc->second.first;
		std::string param_type		= pc->second.second;

		sptr<xbnode> attribute_node = state.pTemplateNode->getAttribute( param_name );
		if( attribute_node )
		{
			// Datentyp ok?
			if( param_type=="" )
			{
				// alles ok
			}else
			if( param_type=="number" )
			{
				if( !attribute_node->isNumeric() )
				{
					p_xbn_xslt->raiseError( name+"() attribute "+param_name+" is not numeric", &state, __FILE__, __LINE__ );
					ret=false;
				}
			}else
			if( param_type=="boolean" )
			{
				if( !attribute_node->isBool() )
				{
					p_xbn_xslt->raiseError( name+"() attribute "+param_name+" is not boolean", &state, __FILE__, __LINE__ );
					ret=false;
				}
			}else
			if( param_type=="pattern" )
			{
				if( !attribute_node->isPattern() )
				{
					p_xbn_xslt->raiseError( name+"() attribute "+param_name+" is not pattern", &state, __FILE__, __LINE__ );
					ret=false;
				}
			}else
			if( param_type=="name" )
			{
				if( !attribute_node->isText() )
				{
					p_xbn_xslt->raiseError( name+"() attribute "+param_name+" is not name", &state, __FILE__, __LINE__ );
					ret=false;
				}
			}
		}
		else
		{
			if( !param_optional )
			{
				p_xbn_xslt->raiseError( name+"() missing attribute "+param_name, &state, __FILE__, __LINE__ );
				ret=false;
			}
		}
	}
	return ret;
}
