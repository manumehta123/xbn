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
#ifndef SPTR_H
#define SPTR_H
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <list>
#include <new>
#include <cstdlib>
#include "xbn.h"

class sptr_base;

/// GeSmartpointerte Basisklasse
class sptr_class
{
protected:
	int_xbn					m_ref;
	std::set<sptr_base*>	m_refmap;
	bool					m_mark_sweep_flag;

public:
							sptr_class();
	virtual					~sptr_class();

	int_xbn					ref();
	int_xbn					incref( sptr_base* ptr_from );
	int_xbn					decref( sptr_base* ptr_from );
	uint_xbn				invalidate( );

public:
	static	void			init();
	static	uint_xbn		gc();
	static  uint_xbn		cleanup();
	static	void			print_debug_state();
	static	uint_xbn		getCurrentObjectCount();
	static	uint64_t		stack_bottom_adr;
protected:
	static	void			addObject( sptr_class* obj );
	static	void			removeObject( sptr_class* obj );
	static	std::set< sptr_class* > s_collection;
};

///	Basis klasse zu sprt<T> - stellt invalidate bereit
class sptr_base
{
public:
					sptr_base()
	{}
	virtual			~sptr_base()
	{}
	virtual bool	invalidate() = 0;

	bool isStack()
	{
		int p=0;
		uint64_t adr_stack_top		= (uint64_t)&p;
		uint64_t adr_stack_bottom	= sptr_class::stack_bottom_adr;
		uint64_t adr_ptr			= (uint64_t)this;

		if( adr_stack_top<adr_stack_bottom )
			return adr_stack_top< adr_ptr && adr_ptr<adr_stack_bottom;
		else
			return adr_stack_top> adr_ptr && adr_ptr>adr_stack_bottom;
	}
};

///	SmartPointer Template usage: sptr<T>  wobei T von sptr_base abgeleitet sein sollte
template<class T> class sptr : public sptr_base
{
private:
	// Zeiger Speicher
	T*		m_ptr;
	int_xbn m_ref;

	// Zeiger Setzen
	void setPtr( const T* ptr )
	{
		if( ptr!=m_ptr )
		{
			removePtr();
			m_ptr = (T*)ptr;
			if(m_ptr) m_ref = m_ptr->incref( this );
		}
	}
	// Zeiger entfernen
	bool removePtr()
	{
		bool ret=false;
		if( m_ptr )
		{
			T* backup_ptr = m_ptr;
			m_ptr = NULL;

			if( !backup_ptr->decref( this ) )
			{
				delete backup_ptr;
				ret=true;
			}
		}

		return ret;
	}
	// Check BaseType
	bool	checkBase()
	{
		return dynamic_cast<sptr_class*>( this )?true:false;
	}

public:
	// Static Empty (muesste eigentlich auch const sein... )
	const static sptr<T> Empty;

	// Leerer Konstruktur := Empty
	sptr()
	{
		m_ptr = NULL;
		m_ref = 0;
	}
	// Copy constructor
	sptr( const sptr<T> &value )
	{
		m_ptr = NULL;
		m_ref = 0;
		setPtr( value.m_ptr );
	}
	// T const zeiger Konstruktor
	sptr( const T* ptr )
	{
		m_ptr = NULL;
		m_ref = 0;
		setPtr( ptr );
	}
	// Destruktor
	virtual ~sptr()
	{
		removePtr();
	}
	// -> Dereferenzierung als zugriff auf T*
	T* operator->()
	{
		return m_ptr;
	}
	// Assignment Operator
	const sptr<T>& operator=(const sptr<T>& right)
	{
		setPtr( right.m_ptr );
		return *this;
	}
	// Vergleich mit const sptr<T>
	int	operator==(const sptr<T>& right)
	{
		return this->m_ptr==right.m_ptr;
	}
	// Vergleich mit const T*
	int	operator==(const T* right)
	{
		return this->m_ptr==right;
	}
	// Vergleich mit T*
	int	operator==(T* right)
	{
		return this->m_ptr==right;
	}
	// pruefe ob ein Zeiger hinterlegt wurde
	operator bool()
	{
		return this->m_ptr?true:false;
	}
	// Cast auf T*
	operator T*()
	{
		return this->m_ptr;
	}

	void *operator			new(size_t size)
	{
		void *p;
		std::cout << "In overloaded new.\n";
		p =  malloc(size);
		if(!p)
		{
			std::bad_alloc ba;
			throw ba;
		}
		return p;
	}

	void operator			delete(void *p)
	{
		std::cout << "In overloaded delete.\n";
		free(p);
	}

	void *operator			new[](size_t size)
	{
		void *p;
		std::cout << "Using overload new[].\n";
		p =  malloc(size);
		if( !p )
		{
			std::bad_alloc ba;
			throw ba;
		}
		return p;
	}

	void operator			delete[](void *p)
	{
		std::cout << "Freeing array using overloaded delete[]\n";
		free(p);
	}

	std::string id()
	{
		std::ostringstream oss;
		oss << "id_"<< std::hex << (long)this->m_ptr;
		return oss.str();
	}

	bool invalidate()
	{
		return removePtr();
	}
};

template<class T> const sptr<T> sptr<T>::Empty;


#endif // SPTR_H
