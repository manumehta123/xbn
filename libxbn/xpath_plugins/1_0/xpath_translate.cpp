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
#include "xpath_plugins/xbn_xpath_plugins_1_0.h"
#include "xbn_helper.h"
#include "xbstring.h"
#include "xbn_document.h"

xpathplugin_translate::xpathplugin_translate()
{
	min_parameter = 1;
	max_parameter = 1;
	name          = "translate";
}
bool            xpathplugin_translate::testUnit()
{
	return testPass("translate('Hallo1900','abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')", 1, xbnode::xbn_temp, "HALLO1900")
			&testPass("translate('Halloz','abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXY')", 1, xbnode::xbn_temp, "HALLO");
}
bool            xpathplugin_translate::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
		return false;

	xbn_state arg1(state);
	if( !pxpath->process( arg1, *(state.pCurrent_token) ) )
	{
		pxpath->raiseError( this->name + "() could not process arg1", &state,__FILE__,__LINE__ );
		return false;
	}
	xbn_state arg2(state);
	if( !pxpath->process( arg2, *(state.pCurrent_token) ) )
	{
		pxpath->raiseError( this->name + "() could not process arg2", &state,__FILE__,__LINE__ );
		return false;
	}
	xbn_state arg3(state);
	if( !pxpath->process( arg3, *(state.pCurrent_token) ) )
	{
		pxpath->raiseError( this->name + "() could not process arg3", &state,__FILE__,__LINE__ );
		return false;
	}


	if( arg1.ResultNodeList.size()!=arg2.ResultNodeList.size()||
		arg1.ResultNodeList.size()!=arg3.ResultNodeList.size())
	{
		pxpath->raiseError( this->name + "() argsize does not match arg1 arg2 arg3", &state,__FILE__,__LINE__ );
		return false;
	}

	for( xbnode_list::iterator pc_arg1=arg1.ResultNodeList.begin(),pe_arg1=arg1.ResultNodeList.end(),
								pc_arg2=arg2.ResultNodeList.begin(),
								pc_arg3=arg3.ResultNodeList.begin();
			pc_arg1!=pe_arg1;
			++pc_arg1, ++pc_arg2, ++pc_arg3 )
	{
		std::string wert1 = (*pc_arg1)->getText();
		std::string wert2 = (*pc_arg2)->getText();
		std::string wert3 = (*pc_arg3)->getText();

		for(size_t p=0; p< wert1.length();++p )
		{
			size_t q = wert2.find( wert1[p] );
			if( q!=std::string::npos )
			{
				if( q<wert3.length() )
				{
					wert1[p] = wert3[q];
				}
				else
				{
					// Das zeichen entfernen
					wert1.replace(p,1,"");
					--p;
				}
			}
		}

		state.ResultNodeList.push_back(
				state.pStack->createTempNode(
						wert1
					)
				);
	}
	return true;
}

