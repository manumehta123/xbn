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
#ifndef XBN_XSLT_H
#define XBN_XSLT_H
#include <string>
#include "xbn_document.h"
#include "xbn_state.h"

class xbn_xslt_plugin_base;
typedef std::map<std::string,xbn_xslt_plugin_base*>	xslt_plugin_map;

class xbnode;
class xbn_xslt
{
private:
	static			xslt_plugin_map			s_plugin_map;


	xbn_document	m_xslt;
public:
					xbn_xslt( std::string xslt_filename );
	virtual			~xbn_xslt();

	bool			m_bDebugMode;

	sptr<xbn_document>	transform( xbn_document *ptr_doc_source );


	bool			process( xbn_state &state );
	bool			process_template( xbn_state &state );
	sptr<xbnode>	getTemplateMatch( std::string match, std::string mode );
	sptr<xbnode>	getTemplateName( std::string name, std::string mode );

private:
	int				m_errorcount;
public:
	//------------------------------------------------------------------------------------------------------------------
	//		Fehlerbehandlung
	//------------------------------------------------------------------------------------------------------------------
	int			getErrorCount();
	int			peekErrorCount();
	void		raiseError( std::string message, xbn_state *state=NULL, const char *file=__FILE__,int line=__LINE__ );

	//------------------------------------------------------------------------------------------------------------------
	//			testUnit
	//------------------------------------------------------------------------------------------------------------------
	static  bool					testUnit();

	//------------------------------------------------------------------------------------------------------------------
	//			Plugin Manager
	//------------------------------------------------------------------------------------------------------------------
	static	void					initXSLT();
	static	xbn_xslt_plugin_base*	getPlugin( std::string name );
	static	void					addPlugin( xbn_xslt_plugin_base* ptr_plugin );
};

#endif // XBN_XSLT_H
