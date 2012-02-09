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
#ifndef XBDATA_H
#define XBDATA_H

#include <iostream>
#include <string>
#include <list>
#include "sptr.h"

class xbnode;
class xbnnode_plugin_manager;

class xbdata : public sptr_class
{
	friend class xbstring;
private:
	bool					 m_in_buildprocess;
	std::string				 m_data;
	sptr<xbnode>			 m_ptr_xbnode_root;
	xbnnode_plugin_manager	*m_ptr_plugin_manager;

public:
					xbdata();
					xbdata( std::string data );
					xbdata( std::istream &input_stream, uint_xbn capacity=0 );
	virtual			~xbdata();

	void			setPluginManager(xbnnode_plugin_manager	*);

	bool			read( std::istream &input_stream, uint_xbn capacity=0 );
	bool			read( std::string data );
	bool			write( std::ostream &output_stream );

	sptr<xbnode>	getRootNode();

protected:
	sptr<xbnode>	create_xbnode( sptr<xbnode> ptr_node, std::istream &input_stream, uint_xbn capacity=0 );
	bool			flush_xbnode( sptr<xbnode> ptr_node, std::ostream &output_stream );

	void			raiseError( std::string message, const char *file, int line  );
};


#endif // XBDATA_H
