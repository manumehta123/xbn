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

xpathplugin_xbn_select::xpathplugin_xbn_select()
{
	min_parameter = 0;
	max_parameter = 2;
	name          = "xbn:/";
}
bool            xpathplugin_xbn_select::testUnit()
{
	return	testPass( "/",1, xbnode::xbn_root, "" )
		&	testPass( "/test",1, xbnode::xbn_node, "" );
}
bool            xpathplugin_xbn_select::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	// Hole linke Seite
	xbn_state arg1(state);
	if( !pxpath->process( arg1, *(state.pCurrent_token) ) )
	{
		return true;
	}

	// Und verknuepfe diese mit allen ergebnissen der rechten seite
	uint_xbn pos=0, col_size = arg1.ResultNodeList.size();
	for( xbnode_list::iterator pc=arg1.ResultNodeList.begin(),pe=arg1.ResultNodeList.end(); pc!=pe;++pc,++pos )
	{
		xbn_state arg2(state);
		uint_xbn current_token = *(state.pCurrent_token);
		arg2.pCurrent_token  = &current_token;

		arg2.pCurrentNode          = *pc;
		arg2.current_node_position = pos;
		arg2.last_node_position    = col_size-1;
		if( pxpath->process( arg2, *(arg2.pCurrent_token) ) )
		{
			// Ergebnis auflisten
			state.addNodeList( arg2.ResultNodeList );
			//if( state.ResultNodeList.size()>state.MaxResultSize ) break;
		}
	}
	return true;
}

//----------------------------------------------------------------------------------------------------------------------

xpathplugin_xbn_current::xpathplugin_xbn_current()
{
	min_parameter = 0;
	max_parameter = 2;
	name          = "xbn:.";
}
bool            xpathplugin_xbn_current::testUnit()
{
	return	testPass( ".",1, xbnode::xbn_root, "" )
		|	testPass( "/test/.",1, xbnode::xbn_node, "" );
}
bool            xpathplugin_xbn_current::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( state.pCurrentNode )
	{
		state.ResultNodeList.push_back( state.pCurrentNode );
		return true;
	}
	pxpath->raiseError( name+"() missing current node", &state, __FILE__,__LINE__ );
	return false;
}

//----------------------------------------------------------------------------------------------------------------------


xpathplugin_xbn_parent::xpathplugin_xbn_parent()
{
	min_parameter = 0;
	max_parameter = 2;
	name          = "xbn:..";
}
bool            xpathplugin_xbn_parent::testUnit()
{
	return testPass( "/test/..",1, xbnode::xbn_root, "" );
}
bool            xpathplugin_xbn_parent::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( state.pCurrentNode && state.pCurrentNode->getParent() )
	{
		state.ResultNodeList.push_back( state.pCurrentNode->getParent() );
		return true;
	}
	pxpath->raiseError( name+"() missing parentnode!",&state,__FILE__,__LINE__);
	return false;
}

//----------------------------------------------------------------------------------------------------------------------

xpathplugin_xbn_all::xpathplugin_xbn_all()
{
	min_parameter = 0;
	max_parameter = 2;
	name          = "xbn://";
}
bool            xpathplugin_xbn_all::testUnit()
{
	return	testPass( "//",14, xbnode::xbn_root|xbnode::xbn_node, "" )
		&	testPass( "/.//",13, xbnode::xbn_node, "" )
		&	testPass( "/test//",12, xbnode::xbn_node, "" );
}
bool            xpathplugin_xbn_all::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	//std::cout << "#debug :: "<< pxpath->peekToken( *(state.pCurrent_token) ) << "|" << pxpath->peekToken( *(state.pCurrent_token)+1 ) << std::endl;

	if( state.pCurrentNode )
	{
		xbnode_list all_nodes_col;
		all_nodes_col.push_back( state.pCurrentNode );
		state.pCurrentNode->getChildNodes( all_nodes_col, true, xbnode::xbn_node );

		std::string peek_token =  pxpath->peekToken( *(state.pCurrent_token)+1 );
		if( peek_token!="" && peek_token!="?." )
		{
			uint_xbn pos=0, col_size = all_nodes_col.size();
			for( xbnode_list::iterator pc=all_nodes_col.begin(),pe=all_nodes_col.end(); pc!=pe;++pc,++pos )
			{
				xbn_state arg(state);
				uint_xbn current_token = *(state.pCurrent_token) +1 ;
				arg.pCurrent_token  = &current_token;

				arg.pCurrentNode          = *pc;
				arg.current_node_position = pos;
				arg.last_node_position    = col_size-1;
				if( pxpath->process( arg, *(arg.pCurrent_token) ) )
				{
					state.addNodeList( arg.ResultNodeList );
				}
			}
		}
		else
		{
			state.addNodeList( all_nodes_col );
		}
		return true;
	}
	return false;
}

//----------------------------------------------------------------------------------------------------------------------

xpathplugin_xbn_axis::xpathplugin_xbn_axis()
{
	min_parameter = 1;
	max_parameter = 2;
	name          = "xbn:::";
}
bool            xpathplugin_xbn_axis::testUnit()
{
	return	testPass( "child::",1, xbnode::xbn_node, "" )
			&	testPass( "/test/parent::",1, xbnode::xbn_root|xbnode::xbn_node, "" )
		&	testPass( "/test/self::",1, xbnode::xbn_node, "" )
		&	testPass( "/test/ancestor::",1, xbnode::xbn_root|xbnode::xbn_node, "" )
		&	testPass( "/test/ancestor-or-self::",2, xbnode::xbn_root|xbnode::xbn_node, "" )
		&	testPass( "/test/descendant::",12, xbnode::xbn_root|xbnode::xbn_node, "" )
		&	testPass( "/test/descendant-or-self::",13, xbnode::xbn_root|xbnode::xbn_node, "" )
		&	testPass( "/test/following::",0, xbnode::xbn_node, "" )
		&	testPass( "/test/following-sibling::",1, xbnode::xbn_node, "" )
		&	testPass( "/test/preceding::",0, xbnode::xbn_node, "" )
		&	testPass( "/test/preceding-sibling::",1, xbnode::xbn_node, "" )
		&	testPass( "/test/attribute::",0, xbnode::xbn_attribute, "" );
}
bool            xpathplugin_xbn_axis::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
		return false;

	std::string axis_name = pxpath->peekToken( (*(state.pCurrent_token)) );
	xbnode_list all_nodes_col;
	if( axis_name=="" || axis_name=="child" )
	{
		state.pCurrentNode->getChildNodes( all_nodes_col, false, xbnode::xbn_node );
	}else
	if( axis_name=="parent" )
	{
		all_nodes_col.push_back( state.pCurrentNode->getParent() );
	}else
	if( axis_name=="self" )
	{
		all_nodes_col.push_back( state.pCurrentNode );
	}else
	if( axis_name=="ancestor" )
	{
		state.pCurrentNode->getParentNodes( all_nodes_col );
	}else
	if( axis_name=="ancestor-or-self" )
	{
		all_nodes_col.push_back( state.pCurrentNode );
		state.pCurrentNode->getParentNodes( all_nodes_col );
	}else
	if( axis_name=="descendant" )
	{
		state.pCurrentNode->getChildNodes( all_nodes_col, true, xbnode::xbn_node );
	}else
	if( axis_name=="descendant-or-self" )
	{
		all_nodes_col.push_back( state.pCurrentNode );
		state.pCurrentNode->getChildNodes( all_nodes_col, true, xbnode::xbn_node );
	}else
	if( axis_name=="following" )
	{
		state.pCurrentNode->getFollowingNodes( all_nodes_col, xbnode::xbn_node );
	}else
	if( axis_name=="following-sibling" )
	{
		all_nodes_col.push_back( state.pCurrentNode );
		state.pCurrentNode->getFollowingNodes( all_nodes_col, xbnode::xbn_node );
	}else
	if( axis_name=="preceding" )
	{
		state.pCurrentNode->getPrecedingNodes( all_nodes_col, xbnode::xbn_node );
	}else
	if( axis_name=="preceding-sibling" )
	{
		all_nodes_col.push_back( state.pCurrentNode );
		state.pCurrentNode->getPrecedingNodes( all_nodes_col, xbnode::xbn_node );
	}else
	if( axis_name=="attribute" )
	{
		state.pCurrentNode->getChildNodes( all_nodes_col, false, xbnode::xbn_attribute );
	}else
	if( axis_name=="namespace" )
	{
		pxpath->raiseError( "namespace axis not supported yet!", &state, __FILE__,__LINE__ );
		return false;
	}else
	{
		pxpath->raiseError( "unknown axis "+axis_name, &state, __FILE__,__LINE__ );
		return false;
	}
	std::string peek_token =  pxpath->peekToken( *(state.pCurrent_token)+1 );

	if( peek_token!="" && peek_token!="?." )
	{
		uint_xbn pos=0, col_size = all_nodes_col.size();
		for( xbnode_list::iterator pc=all_nodes_col.begin(),pe=all_nodes_col.end(); pc!=pe;++pc,++pos )
		{
			xbn_state arg(state);
			uint_xbn current_token = *(state.pCurrent_token) + 1;
			arg.pCurrent_token  = &current_token;

			arg.pCurrentNode          = *pc;
			arg.current_node_position = pos;
			arg.last_node_position    = col_size-1;
			if( pxpath->process( arg, *(arg.pCurrent_token) ) )
			{
				state.addNodeList( arg.ResultNodeList );
			}
		}
	}
	else
	{
		state.addNodeList( all_nodes_col );
	}
	return true;
}
