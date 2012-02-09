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
#ifndef XBN_STACK_H
#define XBN_STACK_H

#include <string>
#include <stack>
#include <deque>
#include "sptr.h"

class xbnode;
typedef std::pair<std::string, sptr<xbnode> > keyxbn_pair;
typedef std::deque< keyxbn_pair > keyxbnstack;

class xbn_stack
{
private:
	keyxbnstack			m_stack;
	std::stack<uint_xbn>	m_rangestack;

	xbn_stack			*m_ptr_base_stack;
public:
					xbn_stack();
					xbn_stack( xbn_stack *ptr_base_stack );
	virtual			~xbn_stack();

	void			pushRange();
	uint_xbn		popRange();


	sptr<xbnode>	createTempNode( std::string wert="" );
	uint_xbn		insertVariable( std::string name, sptr<xbnode> ptr_node_to_copy  );
	sptr<xbnode>	getVariable( std::string name );
};

#endif // XBN_STACK_H
