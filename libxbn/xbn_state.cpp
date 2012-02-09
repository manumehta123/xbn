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
#include "xbn_state.h"

xbn_state::xbn_state()
{
	MaxResultSize	= -1;
	current_node_position = 0;
	last_node_position    = 0;
	pStack			= new xbn_stack();
	pParentState	= NULL;
	pCurrentNode	= sptr<xbnode>::Empty;
	pSourceNode		= sptr<xbnode>::Empty;
	pTemplateNode	= sptr<xbnode>::Empty;
	pCurrent_token  = NULL;
	CurrentToken    = "";

	// Result
	ResultNodeList.clear();
}

xbn_state::xbn_state( xbn_stack *ptr_stack )
{
	MaxResultSize	= -1;
	current_node_position = 0;
	last_node_position    = 0;
	pStack			= new xbn_stack( ptr_stack );
	pParentState	= NULL;
	pCurrentNode	= sptr<xbnode>::Empty;
	pSourceNode		= sptr<xbnode>::Empty;
	pTemplateNode	= sptr<xbnode>::Empty;
	pCurrent_token  = NULL;
	CurrentToken    = "";

	// Result
	ResultNodeList.clear();
}

xbn_state::xbn_state( const xbn_state &T )
{
	MaxResultSize	= T.MaxResultSize;
	current_node_position		= T.current_node_position;
	last_node_position			= T.last_node_position;
	CurrentToken	= T.CurrentToken;
	pCurrent_token  = T.pCurrent_token;
	pParentState	= (xbn_state*)&T;
	pStack			= T.pStack;
	pCurrentNode	= T.pCurrentNode;
	pSourceNode		= T.pSourceNode;
	pTemplateNode	= T.pTemplateNode;

	// Result
	ResultNodeList.clear();
}

xbn_state::~xbn_state()
{
	if( !pParentState && pStack )
	{
		delete pStack;
		pStack = NULL;
	}
}

void	xbn_state::addNodeList( xbnode_list &liste )
{
	ResultNodeList.splice( ResultNodeList.end(), liste );
	//ResultNodeList.insert( ResultNodeList.end(), liste.begin(), liste.end() );
}

float		xbn_state::estimateProgressPercent()
{
	xbn_state *ptr = this;
	float percent_over_all = 0;
	for( ; ptr; ptr=ptr->pParentState )
	{
		if( ptr->current_node_position>0 && ptr->last_node_position>0 )
		{
			float percent = (ptr->current_node_position*100.0) / ptr->last_node_position;
			percent_over_all = percent + (percent_over_all/ptr->last_node_position);
		}
	}
	return percent_over_all;
}

