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
#ifndef XBN_XSLT_PLUGINS_H
#define XBN_XSLT_PLUGINS_H
#include <string>
#include <map>
#include "xbn_state.h"
#include "xbn_xslt.h"

typedef std::map< std::string, std::pair<bool,std::string> > parammap;

class xbn_xslt_plugin_base
{
public:
	uint_xbn	min_parameter;
	uint_xbn	max_parameter;
	std::string name;
	parammap	parameter;

				xbn_xslt_plugin_base();
	virtual		~xbn_xslt_plugin_base();

	void		addParameter( std::string name, bool optional, std::string type );
	bool		checkParameter( xbn_state &state, xbn_xslt *p_xbn_xslt );

	virtual bool testUnit()=0;
	//-------------------------------------------------------------------
	// Eigentliche Plugin Funktion
	//-------------------------------------------------------------------
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt ) = 0;
};

#endif // XBN_XSLT_PLUGINS_H
