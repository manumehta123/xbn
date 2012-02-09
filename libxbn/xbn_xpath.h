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
#ifndef XBN_XPATH_H
#define XBN_XPATH_H

#include <string>
#include <list>
#include <vector>
#include <map>
#include "xbnode.h"
#include "xbn_state.h"
#include "xbn_document.h"

#define _Proc_Sign "?"
class xbn_xpath_plugin_base;
typedef std::map<std::string,xbn_xpath_plugin_base*>	xpath_plugin_map;
typedef std::vector<std::string>						token_queue;

class xbn_xpath
{
private:
	//------------------------------------------------------------------------------------------------------------------
	//		Statics
	//------------------------------------------------------------------------------------------------------------------
	static		std::string					s_whitespaces;
	static		std::vector<std::string>	s_tokenizer;
	static		xpath_plugin_map			s_plugin_map;

	//------------------------------------------------------------------------------------------------------------------
	//		konstruktor / Destruktor
	//------------------------------------------------------------------------------------------------------------------
				xbn_xpath( std::string xpath_pattern );
	virtual		~xbn_xpath();

	std::string	m_base_pattern;
	uint_xbn	m_errorcount;
	token_queue	m_token_queue;
	int			m_last_percent;
	bool		m_progress_printed;

	// compile pattern
	bool		compile_pattern( token_queue &result, std::string xpath_pattern );
	bool		function_param_split( std::vector<std::string> &param_list, std::string pattern );

	// selection

public:
	uint_xbn		select_nodes( sptr<xbnode> pbase_node, xbnode_list &nodes,xbn_stack *ptr_stack=NULL, uint_xbn max_result = -1 );
	sptr<xbnode>	select_node( sptr<xbnode> pbase_node, xbn_stack *ptr_stack=NULL );

	//------------------------------------------------------------------------------------------------------------------
	//		Verarbeitungsroutienen
	//------------------------------------------------------------------------------------------------------------------
	bool		process( xbn_state &state, uint_xbn &current_token );
	bool		peekFunctionList( uint_xbn &current_token );
	std::string peekToken( uint_xbn pos );

private:
	bool		process_function(  xbn_state &state, std::string funktion );

public:
	//------------------------------------------------------------------------------------------------------------------
	//		Fehlerbehandlung
	//------------------------------------------------------------------------------------------------------------------
	void		dumpTokenList( int mark_pos );
	int			getErrorCount();
	int			peekErrorCount();
	void		raiseError( std::string message, xbn_state *state=NULL, const char *file=__FILE__,int line=__LINE__ );
public:

	//------------------------------------------------------------------------------------------------------------------
	//			testUnit
	//------------------------------------------------------------------------------------------------------------------
	static  bool					testUnit();

	//------------------------------------------------------------------------------------------------------------------
	//			Plugin Manager
	//------------------------------------------------------------------------------------------------------------------
	static	void					initXPath();
	static	xbn_xpath_plugin_base*	getPlugin( std::string name );
	static	void					addPlugin( xbn_xpath_plugin_base* ptr_plugin );

	//------------------------------------------------------------------------------------------------------------------
	//			xpath abfrage
	//------------------------------------------------------------------------------------------------------------------
	static	uint_xbn		selectNodes( sptr<xbnode> pbase_node, xbnode_list &nodes, std::string xpath_pattern, xbn_stack *ptr_stack=NULL, uint_xbn max_result=-1 );
	static	sptr<xbnode>	selectNode( sptr<xbnode> pbase_node, std::string xpath_pattern, xbn_stack *ptr_stack=NULL );

	static	std::string		selectText( sptr<xbnode> pbase_node, std::string xpath_pattern, std::string sdefault="", xbn_stack *ptr_stack=NULL );
	static	float			selectNumber( sptr<xbnode> pbase_node, std::string xpath_pattern, float fdefault=0, xbn_stack *ptr_stack=NULL );
};

#endif // XBN_XPATH_H
