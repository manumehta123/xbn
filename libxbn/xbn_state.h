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
#ifndef XBN_STATE_H
#define XBN_STATE_H

#include "xbnode.h"
#include "xbn_stack.h"
#include "sptr.h"

struct xbn_state
{
				xbn_state();
				xbn_state( xbn_stack * ptr_stack );
				xbn_state( const xbn_state &T );
	virtual		~xbn_state();

	uint_xbn	MaxResultSize;
	xbn_state*	pParentState;
	uint_xbn*	pCurrent_token;
	uint_xbn	current_node_position;
	uint_xbn	last_node_position;
	std::string CurrentToken;

	xbn_stack*		pStack;
	sptr<xbnode>	pCurrentNode;
	sptr<xbnode>	pSourceNode;
	sptr<xbnode>	pTemplateNode;

	// Result
	xbnode_list	ResultNodeList;

	void		addNodeList( xbnode_list &liste );
	float		estimateProgressPercent();
};

#endif // XBN_STATE_H
