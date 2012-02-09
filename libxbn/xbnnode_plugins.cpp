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
#include "xbnnode_plugins.h"
#include "xbnode.h"

//----------------------------------------------------------------------------------------------------
//			xbnode_binary
//----------------------------------------------------------------------------------------------------
xbnode_binary::xbnode_binary( uint_xbn id )
{
	this->m_ID = id;
}

xbnode_binary::~xbnode_binary()
{
	if( m_ptr_xbnode && m_ptr_xbnode->m_ptrBinary==this )
	{
		m_ptr_xbnode->m_ptrBinary = NULL;
		//m_ptr_xbnode = NULL;
	}

	if( m_ptr_plugin_base )
	{
		m_ptr_plugin_base->rsm_removeBinary( this );
		//m_ptr_plugin_base = NULL;
	}
}

uint_xbn xbnode_binary::getID()
{
	return this->m_ID;
}

xbnnode_plugin_base* xbnode_binary::getPluginBase()
{
	return this->getPluginBase();
}

sptr<xbnode> xbnode_binary::getNode()
{
	return this->getNode();
}

//----------------------------------------------------------------------------------------------------
//			xbnnode_plugin_base
//----------------------------------------------------------------------------------------------------
xbnnode_plugin_base::xbnnode_plugin_base()
{

}
xbnnode_plugin_base::~xbnnode_plugin_base()
{

}

void						xbnnode_plugin_base::rsm_insertBinary( xbnode_binary*ptr_binary )
{
	m_ressources[ptr_binary->getID()]=ptr_binary;
}

void						xbnnode_plugin_base::rsm_removeBinary( xbnode_binary*ptr_binary )
{
	m_ressources[ptr_binary->getID()]=NULL;
}

xbnode_binary*				xbnnode_plugin_base::rsm_getBinary( uint_xbn ID )
{
	return m_ressources[ID];
}

//----------------------------------------------------------------------------------------------------
//			xbnnode_plugin_manager
//----------------------------------------------------------------------------------------------------
xbnnode_plugin_manager::xbnnode_plugin_manager()
{

}

xbnnode_plugin_manager::~xbnnode_plugin_manager()
{

}

void						xbnnode_plugin_manager::addPlugin( xbnnode_plugin_base *ptr_plugin )
{
	std::string name = ptr_plugin->getFullname();
	m_plugins[ name ] = ptr_plugin;
}

void						xbnnode_plugin_manager::removePlugin( xbnnode_plugin_base *ptr_plugin )
{
	std::string name = ptr_plugin->getFullname();
	m_plugins[ name ]= NULL;
}

xbnnode_plugin_base*		xbnnode_plugin_manager::getPlugin( std::string name )
{
	return m_plugins[ name ];
}
