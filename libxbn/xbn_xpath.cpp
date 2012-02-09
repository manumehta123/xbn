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
#include <iostream>
#include "xpath_plugins/xbn_xpath_plugins.h"
#include "xpath_plugins/xbn_xpath_plugins_1_0.h"
#include "xbn_xpath.h"
#include "xbstring.h"

std::vector<std::string>	xbn_xpath::s_tokenizer;
xpath_plugin_map			xbn_xpath::s_plugin_map;
std::string					xbn_xpath::s_whitespaces;

xbn_xpath::xbn_xpath( std::string xpath_pattern )
{
	if( s_tokenizer.empty() )
		initXPath();

	if( xpath_pattern.length()>1 && xpath_pattern.substr( xpath_pattern.length()-1,1)=="/" )
	{
		xpath_pattern+=".";
	}

	// workarround fuer // bug
	//std_string_replace( xpath_pattern, "///", "/descendant-or-self::" );
	//std_string_replace( xpath_pattern, "//", "descendant-or-self::" );

	m_progress_printed = false;
	m_errorcount = 0;
	m_base_pattern = xpath_pattern;
	compile_pattern( m_token_queue, xpath_pattern );
	m_token_queue.push_back("#EOL");

	if( m_errorcount )
	{
		dumpTokenList(-1);
	}
}

xbn_xpath::~xbn_xpath()
{

}

void xbn_xpath::initXPath()
{
	if( !s_tokenizer.empty() )
		return;

	std::clog << "init_xpath" << std::endl;
	s_whitespaces = " \r\n\t";

	//------------------------------------------------
	//  Tokenizer intialisieren
	//------------------------------------------------
	s_tokenizer.push_back( "|" );


	// Knoten operatoren
	s_tokenizer.push_back( "//" );
	s_tokenizer.push_back( "/" );
	s_tokenizer.push_back( ".." );
	s_tokenizer.push_back( "." );

	// Axis
	s_tokenizer.push_back( "::" );

	// Conditional
	s_tokenizer.push_back( "[" );
	s_tokenizer.push_back( "]" );
	s_tokenizer.push_back( " and " );
	s_tokenizer.push_back( " or " );

	// Vergleichs operatoren
	s_tokenizer.push_back( "!=" );
	s_tokenizer.push_back( ">=" );
	s_tokenizer.push_back( "<=" );
	s_tokenizer.push_back( "=" );
	s_tokenizer.push_back( ">" );
	s_tokenizer.push_back( "<" );
	s_tokenizer.push_back( " in " ); // !Spezialfall!

	// Mathematische operatoren
	s_tokenizer.push_back( "+" );
	s_tokenizer.push_back( "- " );
	//s_tokenizer.push_back( " -" );
	s_tokenizer.push_back( " * " );
	s_tokenizer.push_back( " div " );
	s_tokenizer.push_back( " mod " );
	s_tokenizer.push_back( "(" );
	s_tokenizer.push_back( ")" );

	//------------------------------------------------
	//  xbn:Plugins intialisieren
	//------------------------------------------------
	addPlugin( new xpathplugin_xbn_all() );
	addPlugin( new xpathplugin_xbn_axis() );
	addPlugin( new xpathplugin_xbn_condition() );
	addPlugin( new xpathplugin_xbn_pipe() );
	addPlugin( new xpathplugin_xbn_and() );
	addPlugin( new xpathplugin_xbn_current() );
	addPlugin( new xpathplugin_xbn_div() );
	addPlugin( new xpathplugin_xbn_equal() );
	addPlugin( new xpathplugin_xbn_equal_or_greater() );
	addPlugin( new xpathplugin_xbn_equal_or_less() );
	addPlugin( new xpathplugin_xbn_greater() );
	addPlugin( new xpathplugin_xbn_less() );
	addPlugin( new xpathplugin_xbn_minus() );
	addPlugin( new xpathplugin_xbn_mod() );
	addPlugin( new xpathplugin_xbn_mul() );
	addPlugin( new xpathplugin_xbn_not_equal() );
	addPlugin( new xpathplugin_xbn_or() );
	addPlugin( new xpathplugin_xbn_parent() );
	addPlugin( new xpathplugin_xbn_plus() );
	addPlugin( new xpathplugin_xbn_select() );

	//------------------------------------------------
	//  XPath 1.0 Plugins intialisieren
	//------------------------------------------------
	addPlugin( new xpathplugin_boolean() );
	addPlugin( new xpathplugin_ceiling() );
	addPlugin( new xpathplugin_comment() );
	addPlugin( new xpathplugin_concat() );
	addPlugin( new xpathplugin_contains() );
	addPlugin( new xpathplugin_count() );
	addPlugin( new xpathplugin_current() );
	addPlugin( new xpathplugin_document() );
	addPlugin( new xpathplugin_element_available() );
	addPlugin( new xpathplugin_false() );
	addPlugin( new xpathplugin_floor() );
	addPlugin( new xpathplugin_format_number() );
	addPlugin( new xpathplugin_function_available() );
	addPlugin( new xpathplugin_generate_id() );
	addPlugin( new xpathplugin_id() );
	addPlugin( new xpathplugin_last() );
	addPlugin( new xpathplugin_local_name() );
	addPlugin( new xpathplugin_name() );
	addPlugin( new xpathplugin_normalize_space() );
	addPlugin( new xpathplugin_not() );
	addPlugin( new xpathplugin_node() );
	addPlugin( new xpathplugin_number() );
	addPlugin( new xpathplugin_position() );
	addPlugin( new xpathplugin_round() );
	addPlugin( new xpathplugin_starts_with() );
	addPlugin( new xpathplugin_string() );
	addPlugin( new xpathplugin_string_length() );
	addPlugin( new xpathplugin_substring() );
	addPlugin( new xpathplugin_substring_after() );
	addPlugin( new xpathplugin_substring_before() );
	addPlugin( new xpathplugin_sum() );
	addPlugin( new xpathplugin_text() );
	addPlugin( new xpathplugin_translate() );
	addPlugin( new xpathplugin_true() );
}

bool	xbn_xpath::testUnit()
{
	uint_xbn succeed=0;
	uint_xbn problems=0;

	std::cout << "startup xbn_xpath::testUnit()" << std::endl;
	for( xpath_plugin_map::iterator pc = s_plugin_map.begin(),pe=s_plugin_map.end(); pc!=pe;++pc )
	{
		std::cout << "Invoke " << pc->first << "->testUnit()" << std::endl;
		if( pc->second->testUnit() )
			++succeed;
		else
			++problems;
	}
	std::cout << "xbn_xpath::testUnit() done" << std::endl;
	std::cout << "--------------------------------------------------"<<std::endl;
	std::cout << "> successfuly " << succeed << std::endl;
	std::cout << "> problems " << problems << std::endl;
	std::cout << "> totaly run " << succeed+problems << std::endl;
	std::cout << "--------------------------------------------------"<<std::endl;
	return problems==0;
}

void	xbn_xpath::addPlugin( xbn_xpath_plugin_base* ptr_plugin )
{
	//std::clog << "add_plugin " << ptr_plugin->name << std::endl;
	if( s_plugin_map[ ptr_plugin->name ] )
	{
		std::clog << "replace_plugin " << ptr_plugin->name << std::endl;
		delete (s_plugin_map[ ptr_plugin->name ]);
	}
	s_plugin_map[ ptr_plugin->name ] = ptr_plugin;
}

xbn_xpath_plugin_base*		xbn_xpath::getPlugin( std::string name )
{
	return s_plugin_map[ name ];
}

// compile pattern
bool	xbn_xpath::compile_pattern( token_queue &result, std::string xpath_pattern )
{
	for( std::vector<std::string>::iterator it_tokens = s_tokenizer.begin(); it_tokens!=s_tokenizer.end(); ++it_tokens )
	{
		bool inQuotes= false;
		bool inApos  = false;
		int  inKlammern = 0;
		int  inKondition= 0;

		for(uint_xbn p=0;p<xpath_pattern.length();++p)
		{
			// StateMachine
			bool inText = inApos|inQuotes;
			bool outKondition = inKondition==0;
			bool outKlammern  = inKlammern==0;
			bool inMinusSign  = p==0 && xpath_pattern[0]=='-';
			bool inDotNumeric = p>0 && xpath_pattern[p]=='.' && xpath_pattern[p-1]>='0' && xpath_pattern[p-1]<='9';

			switch( xpath_pattern[p] )
			{
			case '(':
				if(!inText) ++inKlammern;
				break;
			case ')':
				if(!inText) if( !(--inKlammern) ) outKlammern = true;
				break;
			case '[':
				if(!inText) ++inKondition;
				break;
			case ']':
				if(!inText) if( !(--inKondition) ) outKondition = true;
				break;
			case '\'':
				if(!inQuotes) inApos = !inApos;
				break;
			case '"':
				if(!inApos) inQuotes = !inQuotes;
				break;
			}

			// Whitespace detect
			if( s_whitespaces.find( xpath_pattern[p] )!=std::string::npos )
			{
				//continue;
			}

			// Textstring
			if( inText || inApos || inQuotes )
			{
				continue;
			}

			// Klammerung
			if( !outKlammern || !outKondition )
			{
				continue;
			}

			// vorzeichen und Zahlpunkt
			if( inMinusSign || inDotNumeric )
			{
				continue;
			}

			/*
			if( p>0 && xpath_pattern[p]=='*' && *it_tokens=="*"  )
			{
				if( xpath_pattern[p-1] == '@' ) continue;
				if( xpath_pattern[p-1] == '[' ) continue;
				if( xpath_pattern[p-1] == ':' ) continue;
				if( xpath_pattern[p-1] == '/' ) continue;
			}*/

			// Token pruefen
			if( xpath_pattern.length()>=p+it_tokens->length() &&
				xpath_pattern.substr(p,it_tokens->length()) == *it_tokens )
			{
				// ToDo: auf white space/Token einschluss achten...

				std::string prefix  = std_string_trim( xpath_pattern.substr(0,p) );
				std::string infix   = std_string_trim(*it_tokens);
				std::string postfix = std_string_trim( xpath_pattern.substr(p+it_tokens->length()) );

				if( infix=="]" || infix==")" )
				{
					if( !compile_pattern( result, prefix ) ) break;
					result.push_back( _Proc_Sign+infix );
				}
				else
				{
					result.push_back( _Proc_Sign+infix );
					if( !compile_pattern( result, prefix ) ) break;

					if( infix!="(" )
					{
						if( !compile_pattern( result, postfix ) ) break;
					}
					else
					{
						if( postfix!="" )
						{
							std::vector<std::string> parameter_liste;
							if( !function_param_split( parameter_liste, postfix ) ) break;

							for( std::vector<std::string>::iterator pc = parameter_liste.begin(); pc!=parameter_liste.end(); ++pc )
							{
								// Funktion
								result.push_back( _Proc_Sign"," );
								if( !compile_pattern( result, *pc ) ) break;
							}
						}
					}
				}
				p= xpath_pattern.length();
				return (m_errorcount==0);
			}
		}

		// State Machine pruefen
		if( inQuotes )      raiseError( "CompilePattern missing closing Quote in "+xpath_pattern,NULL,__FILE__,__LINE__);
		if( inApos )        raiseError( "CompilePattern missing closing Apos in "+xpath_pattern,NULL,__FILE__,__LINE__);
		if( inKlammern>0 )  raiseError( "CompilePattern missing closing token ) in "+xpath_pattern,NULL,__FILE__,__LINE__);
		if( inKlammern<-1 ) raiseError( "CompilePattern to many closing token ) in "+xpath_pattern,NULL,__FILE__,__LINE__);
		if( inKondition>0 ) raiseError( "CompilePattern missing closing token ] in "+xpath_pattern,NULL,__FILE__,__LINE__);
		if( inKondition<-1 )raiseError( "CompilePattern to many closing token ] in "+xpath_pattern,NULL,__FILE__,__LINE__);
		if( m_errorcount>0 ) break;
	}

	// Pattern als token setzen
	result.push_back( std_string_trim(xpath_pattern) );
	return (m_errorcount==0);
}

bool xbn_xpath::function_param_split( std::vector<std::string> &param_list, std::string pattern )
{
	bool inQuotes= false;
	bool inApos  = false;
	int  inKlammern = 0;
	int  inKondition= 0;
	int  param_start= 0;

	for(uint_xbn p=0;p<pattern.length();++p)
	{
		// StateMachine
		bool inText = inApos|inQuotes;
		bool outKondition = inKondition==0;
		bool outKlammern  = inKlammern==0;
		switch( pattern[p] )
		{
		case '(':
			if(!inText) ++inKlammern;
			break;
		case ')':
			if(!inText) if( !(--inKlammern) ) outKlammern = true;
			break;
		case '[':
			if(!inText) ++inKondition;
			break;
		case ']':
			if(!inText) if( !(--inKondition) ) outKondition = true;
			break;
		case '\'':
			if(!inQuotes) inApos = !inApos;
			break;
		case '"':
			if(!inApos) inQuotes = !inQuotes;
			break;
		}

		if( !inText && outKlammern && outKondition && pattern[p]==',' )
		{
			std::string param = pattern.substr( param_start, p-param_start );
			param_list.push_back( std_string_trim(param) );
			param_start = p+1;
		}
	}
	std::string rest =  std_string_trim( pattern.substr( param_start ) );

	if( rest.length()>0 && rest[rest.length()-1]==')')
	{
		if( rest.length()>1 )
		{
			param_list.push_back( rest.substr(0,rest.length()-1) );
		}
		else
		{
			// Keine Parameter!
		}
	}
	else
	{
		raiseError("function_param_split: missing cloding token )",NULL,__FILE__,__LINE__);
		return false;
	}

	return true;
}


//------------------------------------------------------------------------------------------------------------
//  Fehler Protokolierung
//------------------------------------------------------------------------------------------------------------
// Tokenliste ausgeben
void	xbn_xpath::dumpTokenList( int mark_pos )
{
	std::cerr << std::endl;
	std::cerr << "errdump:" << std::endl;
	std::cerr << "\txpath " << m_base_pattern << std::endl;
	std::cerr << "\ttoken ";

	int pos=0;
	for( token_queue::iterator pc = m_token_queue.begin(); pc!=m_token_queue.end(); ++pc,++pos )
	{
		if( pos==mark_pos ) std::cerr << "--> ";
		std::cerr << *pc << " ";
	}
	std::cerr << std::endl;
	std::cerr << std::endl;
}

// Fehler Anzahl auslesen (loescht den code anschliessend)
int  xbn_xpath::getErrorCount()
{
	int ret = m_errorcount;
	m_errorcount = 0;
	return ret;
}

// Fehler anzahl abfragen
int  xbn_xpath::peekErrorCount()
{
	return m_errorcount;
}

void		xbn_xpath::raiseError( std::string message, xbn_state *states,const char *file, int line)
{
	++m_errorcount;
	std::cerr << std::endl << file << ":" << std::dec << line <<"#"<< message << std::endl;
	std::cerr << "["<< m_errorcount << "] state ptr" << std::hex <<  states << std::endl;
	if( states ) dumpTokenList( *(states->pCurrent_token) );
}

// select_nodes
uint_xbn		xbn_xpath::select_nodes( sptr<xbnode> pbase_node, xbnode_list &nodes, xbn_stack *ptr_stack, uint_xbn max_result )
{
	m_last_percent = 0;
	xbn_state state( ptr_stack );
	uint_xbn    current_token=0;
	state.MaxResultSize			= max_result;
	state.pCurrentNode			= pbase_node;
	state.current_node_position = 0;
	state.last_node_position	= 1;
	state.pCurrent_token		= &current_token;

	if( process( state, current_token ) )
	{
		if( max_result>1 )
		{
			nodes.splice( nodes.end(), state.ResultNodeList, state.ResultNodeList.begin(), state.ResultNodeList.end() );
		}
		else
		{
			if( !state.ResultNodeList.empty() )
				nodes.push_back(  state.ResultNodeList.front() );
		}
	}
	else
	{
		raiseError( "xbn_xpath::select_nodes::process failure", &state,__FILE__,__LINE__ );
	}

	if( m_progress_printed )
	{
		std::clog << "\r                             \r";
		m_progress_printed = false;
	}

	return nodes.size();
}

sptr<xbnode>	xbn_xpath::select_node( sptr<xbnode> pbase_node,xbn_stack *ptr_stack )
{
	xbnode_list nodes;
	if( select_nodes( pbase_node,nodes,ptr_stack, 1) )
		return nodes.back();
	return sptr<xbnode>::Empty;
}

// select_nodes wrapper
uint_xbn	xbn_xpath::selectNodes( sptr<xbnode> pbase_node, xbnode_list &nodes, std::string xpath_pattern,xbn_stack *ptr_stack, uint_xbn max_result )
{
	xbn_xpath xpth( xpath_pattern );
	return xpth.select_nodes( pbase_node, nodes, ptr_stack, max_result );
}

sptr<xbnode>	xbn_xpath::selectNode( sptr<xbnode> pbase_node, std::string xpath_pattern,xbn_stack *ptr_stack )
{
	xbn_xpath xpth( xpath_pattern );
	return xpth.select_node( pbase_node, ptr_stack );
}

std::string		xbn_xpath::selectText( sptr<xbnode> pbase_node, std::string xpath_pattern, std::string sdefault, xbn_stack *ptr_stack )
{
	sptr<xbnode> node = selectNode( pbase_node, xpath_pattern, ptr_stack );
	if( node && node->isText() )
		return node->getText();
	return sdefault;
}

float			xbn_xpath::selectNumber( sptr<xbnode> pbase_node, std::string xpath_pattern, float fdefault, xbn_stack *ptr_stack )
{
	sptr<xbnode> node = selectNode( pbase_node, xpath_pattern, ptr_stack );
	if( node && node->isNumeric() )
		return node->getNumeric();
	return fdefault;
}

bool		xbn_xpath::peekFunctionList( uint_xbn &current_token )
{
	std::string current_cmd = m_token_queue[ current_token ];
	if( current_cmd=="#EOL" )
	{
		raiseError( "peekFunctionList() #EOL", NULL,__FILE__,__LINE__ );
		return false;
	}

	return (current_cmd==_Proc_Sign",");
}

//------------------------------------------------------------------------------------------------------------
//  Generischer verarbeitungsschritt
//------------------------------------------------------------------------------------------------------------
//
bool xbn_xpath::process( xbn_state &state, uint_xbn &current_token )
{
	std::string current_cmd = m_token_queue[ current_token ];
	bool ret_value=false;

	//std::cout << "process " << current_cmd << std::endl;
	if( peekErrorCount()>0 )
	{
		return false;
	}
	if( current_cmd=="#EOL" )
	{
		raiseError( "process() #EOL", &state,__FILE__,__LINE__ );
		return false;
	}
	if( !state.pCurrentNode )
	{
		raiseError( "process() empty node at "+current_cmd, &state,__FILE__,__LINE__ );
		return false;
	}
	++current_token;

	//---------------------------------------------------------------------------------------------------
	//              RootNode
	//---------------------------------------------------------------------------------------------------
	if( current_cmd=="" )
	{
		//"process !ROOT";
		state.ResultNodeList.push_back( state.pCurrentNode->getRoot() );
		ret_value = true;
	}else
		//---------------------------------------------------------------------------------------------------
		//			Direkte ergebnisse
		//---------------------------------------------------------------------------------------------------
	if( current_cmd[0]=='@' )
	{
		current_cmd = current_cmd.substr(1);
		bool bAll= (current_cmd == "*");
		xbnode_list list;
		state.pCurrentNode->getAttributes( list );

		if( bAll )
		{
			state.addNodeList( list );
		}
		else
		{
			for(xbnode_list::iterator pc=list.begin(),pe=list.end(); pc!=pe;++pc )
			{
				if( (*pc)->getFullname()==current_cmd || (*pc)->getName()==current_cmd )
				{
					state.ResultNodeList.push_back( *pc );
				}
			}
		}
		ret_value = true;
	}else
	if( current_cmd[0]=='$' )
	{
		sptr<xbnode> pnode =  state.pStack->getVariable( current_cmd.substr(1) );
		if( pnode )
		{
			state.ResultNodeList.push_back( pnode );
			ret_value = true;
		}
		else
		{
			raiseError( "missing variable "+current_cmd, &state,__FILE__,__LINE__ );
			ret_value = false;
		}
	}else
	if( current_cmd[0]=='\'' || current_cmd[0]=='\"' )
	{
		state.ResultNodeList.push_back(
					state.pStack->createTempNode( current_cmd.substr(1,current_cmd.length()-2) )
				);
		ret_value = true;
	}else
		if( current_cmd.find_first_not_of("-0123456789.")==std::string::npos )
	{
		state.ResultNodeList.push_back(
					state.pStack->createTempNode( current_cmd )
				);
		ret_value = true;
	}else
		//---------------------------------------------------------------------------------------------------
		//  Kondition funktion
		//---------------------------------------------------------------------------------------------------
	if( current_cmd==_Proc_Sign"]" )
	{
		// Conditional Stop
		raiseError( "Process() stop-condition failure",  &state,__FILE__,__LINE__);
		ret_value = false;
	}else
		//---------------------------------------------------------------------------------------------------
		//  Nodesets
		//---------------------------------------------------------------------------------------------------
	if( current_cmd==_Proc_Sign"//" ||
		current_cmd==_Proc_Sign"/" ||
		current_cmd==_Proc_Sign"." ||
		current_cmd==_Proc_Sign".." ||
		current_cmd==_Proc_Sign"::" ||
		current_cmd==_Proc_Sign"[" ||
		current_cmd==_Proc_Sign"|" )
	{
		std::string funktion = "xbn:"+current_cmd.substr(1);
		ret_value = process_function( state, funktion );
	}else

		//---------------------------------------------------------------------------------------------------
		//     Interne Funktionen
		//---------------------------------------------------------------------------------------------------
	if( current_cmd==_Proc_Sign"and"||
		current_cmd==_Proc_Sign"or"||
		current_cmd==_Proc_Sign"="||
		current_cmd==_Proc_Sign"!="||
		current_cmd==_Proc_Sign">="||
		current_cmd==_Proc_Sign"<="||
		current_cmd==_Proc_Sign">"||
		current_cmd==_Proc_Sign"<"||
		current_cmd==_Proc_Sign"in"||
		current_cmd==_Proc_Sign"+"||
		current_cmd==_Proc_Sign"-"||
		current_cmd==_Proc_Sign"*"||
		current_cmd==_Proc_Sign"div"||
		current_cmd==_Proc_Sign"mod" )
	{
		std::string funktion = "xbn:"+current_cmd.substr(1);
		ret_value = process_function( state, funktion );
	}else
		//---------------------------------------------------------------------------------------------------
		//          Standard    funktionen oder schachtelung
		//---------------------------------------------------------------------------------------------------
	if( current_cmd==_Proc_Sign"(" )
	{
		// Funktion Start
		std::string funktion = m_token_queue[ current_token++ ];

		if( funktion!="" )
		{
			ret_value = process_function( state, funktion );
		}
		else
		{
			// Mathetmatsche schachtlung (eigentlich egal)
			ret_value = process( state, current_token );
		}
	}else
	if( current_cmd==_Proc_Sign")" )
	{
		// Funktion Stop - do nothing
		ret_value = process( state, current_token );
	}else
	if( current_cmd==_Proc_Sign"," )
	{
		// Parameter
		ret_value = process( state, current_token );
	}else
	{
		//---------------------------------------------------------------------------------------------------
		//  Select ChildNode Funktion
		//---------------------------------------------------------------------------------------------------
		bool bAll = (current_cmd=="*");
		xbnode_list list;
		state.pCurrentNode->getChildNodes( list );

		if( bAll )
		{
			state.addNodeList( list );
		}
		else
		{
			for(xbnode_list::iterator pc=list.begin(),pe=list.end(); pc!=pe;++pc )
			{
				if( (*pc)->getName()==current_cmd || (*pc)->getFullname()==current_cmd )
				{
					state.ResultNodeList.push_back( *pc );
					//if( state.ResultNodeList.size()>state.MaxResultSize ) break;
				}
			}
		}
		ret_value = true;
	}

	if( ret_value )
	{
		int next_percent = state.estimateProgressPercent();
		if( next_percent>m_last_percent )
		{
			std::clog << "\rxbn_xpath::processing... " << next_percent << "%";
					//<< state.current_node_position << "/" << state.last_node_position;
			std::clog.flush();
			m_last_percent = next_percent;
			m_progress_printed = true;
		}
	}
	return ret_value;
}

bool xbn_xpath::process_function(  xbn_state &state, std::string funktion )
{
	xbn_xpath_plugin_base* plugin_ptr= s_plugin_map[funktion];

	if( plugin_ptr!=NULL )
	{
		//std::clog << "process_function " << funktion << std::endl;
		return (*plugin_ptr)( state, this );
	}

	raiseError( "process_function() "+funktion+" unknown function!",&state,__FILE__,__LINE__);
	return false;
}

std::string xbn_xpath::peekToken( uint_xbn pos )
{
	return pos< m_token_queue.empty() ?  "#EOL" : m_token_queue[ pos ];
}
