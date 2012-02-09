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

xpathplugin_xbn_condition::xpathplugin_xbn_condition()
{
	min_parameter = 0;
	max_parameter = -1;
	name          = "xbn:[";
}
bool            xpathplugin_xbn_condition::testUnit()
{
	return testPass( "/test/c/c3[@wert='8']",1, xbnode::xbn_node, "" )
		&  testPass( "//c3[@wert='8']",1, xbnode::xbn_node, "" );
}
bool            xpathplugin_xbn_condition::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	xbn_state arg1( state );
	if( !pxpath->process( arg1, *(state.pCurrent_token) ) )
	{
		pxpath->raiseError( name+"() process_condition missing nodeset", &state, __FILE__, __LINE__ );
		return false;
	}
	uint_xbn pos=0, maxtoken=*(state.pCurrent_token), col_size = arg1.ResultNodeList.size();
	for( xbnode_list::iterator pc_arg1=arg1.ResultNodeList.begin(),pe_arg1=arg1.ResultNodeList.end();
			pc_arg1!=pe_arg1;
			++pc_arg1  )
	{
		xbn_state cond_state( arg1 );
		uint_xbn cond_token= *(arg1.pCurrent_token);
		cond_state.MaxResultSize= -1;
		cond_state.pCurrentNode = *pc_arg1;
		cond_state.pCurrent_token = &cond_token;
		cond_state.current_node_position = pos++;
		cond_state.last_node_position    = col_size-1;

		// berechne den nachfolgenden ausdruch
		if( !pxpath->process( cond_state, *(cond_state.pCurrent_token) ) )
		{
			pxpath->raiseError( name+"() process_condition missing condition", &state, __FILE__, __LINE__ );
			return false;
		}
		if( *(cond_state.pCurrent_token)>maxtoken ) maxtoken = *(cond_state.pCurrent_token);

		for( xbnode_list::iterator pc_cond_state=cond_state.ResultNodeList.begin(),
								   pe_cond_state=cond_state.ResultNodeList.end();
				pc_cond_state!=pe_cond_state;
				++pc_cond_state )
		{

			if(  (*pc_cond_state)->isBool() )
			{
				if( (*pc_cond_state)->getBool()  )
					state.ResultNodeList.push_back( *pc_arg1 );
			}else
			if(  (*pc_cond_state)->isNumeric() )
			{
				if( (*pc_cond_state)->getNumeric()==cond_state.current_node_position+1  )
					state.ResultNodeList.push_back( *pc_arg1 );
			}
			else
			{
				pxpath->raiseError( name+"() process_condition not boolean or numeric", &state, __FILE__, __LINE__ );
				return false;
			}
		}
	}

	// condition vorspulen
	int schachtelung=0;
	while( pxpath->peekToken( maxtoken )!=_Proc_Sign"]" && pxpath->peekToken( maxtoken )!="#EOL" && !schachtelung )
	{
		if( pxpath->peekToken( maxtoken )==_Proc_Sign"[" ) ++schachtelung;
		else if( pxpath->peekToken( maxtoken )==_Proc_Sign"]" ) --schachtelung;

		++maxtoken;
	}

	if( pxpath->peekToken( maxtoken )!=_Proc_Sign"]" )
	{
		pxpath->raiseError( name+"() process_condition missing closing condition token ]", &state, __FILE__, __LINE__ );
		return false;
	}
	*(state.pCurrent_token) =maxtoken+1;

	return true;
}
