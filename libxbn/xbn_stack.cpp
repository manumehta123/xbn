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

#include "xbn_stack.h"
#include "xbnode.h"
#include "xbn_helper.h"

xbn_stack::xbn_stack()
{
	insertVariable("!bottom", sptr<xbnode>::Empty );
	pushRange();
	m_ptr_base_stack = NULL;
}

xbn_stack::xbn_stack( xbn_stack *ptr_base_stack )
{
	insertVariable("!bottom", sptr<xbnode>::Empty );
	pushRange();
	m_ptr_base_stack = ptr_base_stack;
}

xbn_stack::~xbn_stack()
{
	while( popRange()>=1 )
	{
		// ups - fehler?
	}

	// ToDo: cleanup() :es duerfte nur noch die !bottom variable mit dem NULL Zeiger uebrig sein!
}

void			xbn_stack::pushRange()
{
	m_rangestack.push( m_stack.size() );
}

uint_xbn			xbn_stack::popRange()
{
	if( m_rangestack.size() )
	{
		uint_xbn clean_up_till = m_rangestack.top();
		m_rangestack.pop();

		while( m_stack.size()>clean_up_till )
		{
			m_stack.pop_back();
		}

		return clean_up_till;
	}
	return 0;
}

sptr<xbnode>			xbn_stack::createTempNode( std::string wert )
{
	sptr<xbnode> pnode = xbnode::createNode( NULL, xbnode::xbn_temp );

	pnode->setFullname( "temp:ptr"+zahlToString((long)pnode) );
	pnode->setText( wert );

	insertVariable( pnode->getFullname(), pnode );
	return pnode;
}

uint_xbn			xbn_stack::insertVariable( std::string name, sptr<xbnode> ptr_node_to_copy  )
{
	keyxbn_pair pair;
	pair.first = name;
	if( ptr_node_to_copy )
	{
		pair.second = ptr_node_to_copy->cloneNode();
	}
	else
	{
		pair.second = sptr<xbnode>::Empty;
	}
	m_stack.push_back( pair );

	return m_stack.size();
}

sptr<xbnode>			xbn_stack::getVariable( std::string name )
{
	for( keyxbnstack::reverse_iterator pc = m_stack.rbegin(), pe=m_stack.rend(); pc!=pe;++pc  )
	{
		if( (*pc).first == name )
		{
			return (*pc).second;
		}
	}
	if( m_ptr_base_stack )
	{
		return m_ptr_base_stack->getVariable( name );
	}
	return sptr<xbnode>::Empty;
}
