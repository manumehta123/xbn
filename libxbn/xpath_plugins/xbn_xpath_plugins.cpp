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
#include "xbn_xpath_plugins.h"
#include "xbn_helper.h"
#include "xbn_document.h"

xbn_xpath_plugin_base::xbn_xpath_plugin_base()
{
	min_parameter	= 0;
	max_parameter	= 0;
	name			= "";
}


xbn_xpath_plugin_base::~xbn_xpath_plugin_base()
{

}

bool	xbn_xpath_plugin_base::testPass(
									 std::string pattern,
									 uint_xbn result_count,
									 uint_xbn type,
									 std::string result
									 )
{
	xbn_document xdoc;
	xdoc.loadTestDocument();

	xbnode_list result_list;
	xdoc.selectNodes( result_list, pattern );

	if( result_list.size()!=result_count )
	{
		std::cout << "[!!] " << name <<"_test(" << pattern << ") resultcount_mismatch get "<<result_list.size()<<", need " << result_count << std::endl;
		return false;
	}

	bool ret=true;
	for( xbnode_list::iterator pc=result_list.begin(),pe=result_list.end(); pc!=pe; ++pc )
	{
		if( !( (*pc)->getType()&type ) )
		{
			std::cout << "[!!] " << name <<"_test(" << pattern << ") type mismatch "
					<< "get " << xbnode::getTypeName( (*pc)->getType() )
					<< " need " << xbnode::getTypeName( (xbnode::NodeType)type ) << std::endl;
			ret= false;
		} else
		if( result!="" && (*pc)->getText()!=result )
		{
			std::cout << "[!!] " << name <<"_test(" << pattern << ") value mismatch "
					<< "get " << (*pc)->getText()
					<< " need " << result << std::endl;
			ret = false;
		} else
		{
			// ok!
		}
	}
	if( ret ) std::cout << "[ok] " << name <<"_test(" << pattern << ")"<<std::endl;
	return ret;
}
