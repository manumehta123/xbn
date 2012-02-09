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
#ifndef XBNNODE_PLUGINS_H
#define XBNNODE_PLUGINS_H
#include <string>
#include <map>
#include "sptr.h"

class xbnode;
class xbnode_binary;
class xbnnode_plugin_base;
typedef std::map< uint_xbn, xbnode_binary*> binarymap;
typedef std::map< std::string, xbnnode_plugin_base*> pluginmap;

// Baseclass fuer binary Objekte
class xbnode_binary
{
protected:
	xbnnode_plugin_base*	m_ptr_plugin_base;
	uint_xbn				m_ID;
	sptr<xbnode>			m_ptr_xbnode;
public:
							xbnode_binary( uint_xbn id );
	virtual					~xbnode_binary();

	uint_xbn				getID();
	xbnnode_plugin_base*	getPluginBase();
	sptr<xbnode>			getNode();

	virtual	void			OnLoad() = 0;
	virtual	void			OnUnload() = 0;
	virtual	uint_xbn		updateBinary() = 0;
	virtual uint_xbn		updateNode() = 0;
};

// Binary Object Factory Baseclass
class xbnnode_plugin_base
{
protected:
	binarymap					m_ressources;
public:
								xbnnode_plugin_base();
	virtual						~xbnnode_plugin_base();

	void						rsm_insertBinary( xbnode_binary*ptr_binary );
	void						rsm_removeBinary( xbnode_binary*ptr_binary );
	xbnode_binary*				rsm_getBinary( uint_xbn ID );

	virtual std::string			getNamespace() = 0;
	virtual std::string			getName() = 0;
	virtual std::string			getFullname() = 0;
	virtual std::string			getDescription() = 0;
	virtual xbnode_binary*		createBinary( xbnode *ptr_init_node ) = 0;
};

// Plugin manager fuer Object Factories
class xbnnode_plugin_manager
{
protected:
	pluginmap					m_plugins;
public:
								xbnnode_plugin_manager();
	virtual						~xbnnode_plugin_manager();

	void						addPlugin( xbnnode_plugin_base *ptr_plugin );
	void						removePlugin( xbnnode_plugin_base *ptr_plugin );

	xbnnode_plugin_base*		getPlugin( std::string name );
};

#endif // XBNNODE_PLUGINS_H
