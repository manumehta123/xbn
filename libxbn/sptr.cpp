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
#include "sptr.h"
#include "xbnode.h"
#include "xbstring.h"



sptr_class::sptr_class()
{
	//std::clog << std::hex << this << "::sptr_base()" << std::endl;
	addObject( this );
	m_ref = 0;
}

sptr_class::~sptr_class()
{
	removeObject( this );
	if( m_ref>0 )
	{
		// noch nicht komplett sauber!
		std::cerr << std::hex << this << "::~sptr_class() m_ref=" << std::dec << m_ref << std::endl;
		invalidate( );
	}
	else
	{
		//std::clog << std::hex << this << "::~sptr_class()" << std::endl;
	}
}


uint_xbn	sptr_class::invalidate()
{
	uint_xbn ret=0;

	if( this->m_mark_sweep_flag )
	{
		std::cout << "sptr_class::invalidate marked object " << std::hex << this << std::dec << std::endl;
	}

	while( !m_refmap.empty() )
	{
		++ret;

		// Zeiger-referenz Invalidieren
		if( (*m_refmap.begin())->invalidate() )
		{
			break;
		}
	}
	return ret;
}

int_xbn		sptr_class::ref()
{
	return m_ref;
}

int_xbn		sptr_class::incref(sptr_base* ptr_from)
{
	//std::cout << std::hex << this << "::incref() = " << std::dec << m_ref << std::endl;
	m_refmap.insert( ptr_from );
	return m_ref++;
}

int_xbn		sptr_class::decref(sptr_base* ptr_from)
{
	if( m_ref<=0 )
	{
		std::cerr << std::hex << this << "::decref() = " << std::dec << m_ref << std::endl;
	}
	m_refmap.erase( ptr_from );
	return --m_ref;
}

void	sptr_class::init()
{
	int p=0;
	stack_bottom_adr = (uint64_t)&p;
	std::clog << "sptr_class::init()"<< std::endl;
}

uint_xbn	sptr_class::gc()
{
	std::clog << "sptr_class::gc()"<< std::endl;

	// ToDo: Garbage Collector
	// mark & sweep
	std::set< sptr_base* > root_ptrs;

	for( std::set< sptr_class* >::iterator pc =s_collection.begin(), pe = s_collection.end();pc!=pe;++pc )
	{
		// gibt es gerootete Pointer?
		sptr_class *ptr = *pc;
		ptr->m_mark_sweep_flag = false;

		for( std::set< sptr_base* >::iterator pc_rm =ptr->m_refmap.begin(), pe_rm = ptr->m_refmap.end();pc_rm!=pe_rm;++pc_rm )
		{
			sptr_base* ptr_base = *pc_rm;

			if( ptr_base->isStack() )
			{
				// rooted, makieren
				//root_ptrs.set( ptr_base );
				ptr->m_mark_sweep_flag = true;
				std::clog << "mark " << std::hex << ptr << std::dec << std::endl;
				break;
			}
		}
	}

	// Mark


	// Sweep

	return 0;
}

uint_xbn	sptr_class::cleanup()
{
	gc();

	std::clog << "sptr_class::cleanup()"<< std::endl;
	uint_xbn ret = 0;

	while( !s_collection.empty() )
	{
		sptr_class *ptr = *(s_collection.begin());// back();

		if( !ptr->invalidate() )
		{
			delete ptr;
		}
		++ret;
	}
	return ret;
}

void	sptr_class::print_debug_state()
{
	std::clog << "sptr_class::print_debug_state()"<< std::endl;
	std::clog << "--------------------------------------------------------"<< std::endl;
	std::clog << "sizeof(std::string) : " << sizeof(std::string) << std::endl;
	std::clog << "sizeof(sptr<xbnode>): " << sizeof(sptr<xbnode>) << std::endl;
	std::clog << "sizeof(xbnode_list) : " << sizeof(xbnode_list) << std::endl;
	std::clog << "sizeof(xbnode)      : " << sizeof(xbnode) << std::endl;
	std::clog << "total object count  : " << s_collection.size() << std::endl;
	std::clog << "--------------------------------------------------------"<< std::endl;
}

uint_xbn	sptr_class::getCurrentObjectCount()
{
	return s_collection.size();
}

void	sptr_class::addObject( sptr_class* obj )
{
	s_collection.insert( obj );
}

void	sptr_class::removeObject( sptr_class* obj )
{
	s_collection.erase( obj );
}

std::set< sptr_class* > sptr_class::s_collection;
uint64_t sptr_class::stack_bottom_adr=0;
