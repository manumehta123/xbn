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
#include "xbn_xslt.h"
#include "xslt_plugins/xbn_xslt_plugins_1_0.h"

xslt_plugin_map			xbn_xslt::s_plugin_map;


xbn_xslt::xbn_xslt( std::string xslt_filename )
{
	m_bDebugMode = false;
	m_errorcount = 0;
	if( s_plugin_map.empty() )
	{
		initXSLT();
	}

	// XSLT Dokument laden
	if( !m_xslt.loadFile( xslt_filename ) )
	{
		raiseError( "loadFile("+xslt_filename+") failed to load", NULL, __FILE__,__LINE__ );
		return;
	}

	// XSLT Dokument verifizieren
	xbnode_list col_stylesheet;
	m_xslt.selectNodes( col_stylesheet, "/xsl:stylesheet" );
	if( col_stylesheet.empty() )
	{
		raiseError( "xbn_xslt() document stylesheet not wellformed!", NULL, __FILE__, __LINE__ );
		return;
	}

	if( col_stylesheet.front()->getAttributeText("version","1.0")!="1.0" )
	{
		raiseError("xbn_xslt() not supported stylesheet version [" +col_stylesheet.front()->getAttributeText("version","1.0") +"]!", NULL,__FILE__,__LINE__);
	}

	if(  col_stylesheet.front()->getAttributeText("xmlns:xsl","http://www.w3.org/1999/XSL/Transform")!="http://www.w3.org/1999/XSL/Transform" )
	{
		raiseError("xbn_xslt() not supported stylesheet namespace [" +
				   col_stylesheet.front()->getAttributeText("xmlns:xsl","http://www.w3.org/1999/XSL/Transform")
				   +"]!", NULL, __FILE__, __LINE__);
	}
}

xbn_xslt::~xbn_xslt()
{

}

sptr<xbn_document>	xbn_xslt::transform( xbn_document *ptr_doc_source )
{
	sptr<xbn_document>	pDest = new xbn_document();
	xbn_state state;

	// Verarbeitungsstatus Initialisieren
	state.pSourceNode   = ptr_doc_source->getRootNode();
	state.pTemplateNode = m_xslt.selectNode("/xsl:stylesheet/xsl:template[@match='/']");
	state.pCurrentNode  = pDest->getRootNode();


	if( process( state ) )
	{

	}
	else
	{
		raiseError( "[!!] abort xbn_xslt::transform ", &state, __FILE__,__LINE__ );
		//delete pDest;
		//pDest = NULL;
	}

	return pDest;
}


bool			xbn_xslt::process( xbn_state &state )
{
	if( !state.pTemplateNode )
	{
		raiseError( "xbn_xslt::process() empty templatenode", &state, __FILE__, __LINE__ );
		return false;
	}
	if( m_bDebugMode ) std::clog << "xbn_xslt::process " <<  state.pTemplateNode->getFullname() << std::endl;

	xbn_xslt_plugin_base* plugin = getPlugin( state.pTemplateNode->getFullname() );
	if( plugin )
	{
		if( plugin->checkParameter( state, this) )
		{
			return (*plugin)( state, this );
		}
		raiseError( "xbn_xslt::process() plugin parameter processing failure!", &state, __FILE__, __LINE__ );
		return false;
	}
	bool ret=true;

	// Source Node+ Attribute Kopieren und in pCurrentNode einfuegen
	state.pCurrentNode = state.pTemplateNode->cloneNode( state.pCurrentNode, xbnode::xbn_attribute );

	// ToDo: Attribute und Texte gegen {tag} aufloesen
	//....

	// Child Elemente
	xbnode_list col_child_nodes;
	state.pTemplateNode->getChildNodes( col_child_nodes, false, xbnode::xbn_node|xbnode::xbn_cdata|xbnode::xbn_text );
	for(xbnode_list::iterator pc=col_child_nodes.begin(), pe=col_child_nodes.end(); pc!=pe && ret; ++pc )
	{
		xbn_state child_state(state);
		child_state.pTemplateNode = *pc;
		ret &= process( child_state );
	}

	return ret;
}

bool			xbn_xslt::process_template( xbn_state &state )
{
	if( !state.pTemplateNode )
	{
		raiseError( "xbn_xslt::process_template() empty templatenode", &state, __FILE__, __LINE__ );
		return false;
	}

	xbn_xslt_plugin_base* plugin = getPlugin( "xsl:template" );
	if( plugin )
	{
		return (*plugin)( state, this );
	}
	raiseError( "xbn_xslt::process_template()missing xsl:template plugin!", &state, __FILE__, __LINE__ );
	return false;
}

sptr<xbnode>			xbn_xslt::getTemplateMatch( std::string match, std::string mode )
{
	xbnode_list col_match;
	if( mode.length() )
		m_xslt.selectNodes( col_match, "/xsl:stylesheet/xsl:template[@match='"+ Text2Xml( match )+"' and @mode='"+ Text2Xml(mode) +"']");
	else
		m_xslt.selectNodes( col_match, "/xsl:stylesheet/xsl:template[@match='"+ Text2Xml( match )+"']");

	if( m_bDebugMode ) std::clog << "xbn_xslt::getTemplateMatch " << match << " ("<< col_match.size() << ")" << std::endl;
	return col_match.empty() ? sptr<xbnode>::Empty : col_match.front();
}

sptr<xbnode>			xbn_xslt::getTemplateName( std::string name, std::string mode )
{
	xbnode_list col_match;
	if( mode.length() )
		m_xslt.selectNodes( col_match, "/xsl:stylesheet/xsl:template[@name='"+ Text2Xml( name )+"' and @mode='"+ Text2Xml(mode) +"']");
	else
		m_xslt.selectNodes( col_match, "/xsl:stylesheet/xsl:template[@name='"+ Text2Xml( name )+"']");
	return col_match.empty() ? sptr<xbnode>::Empty : col_match.front();
}

//------------------------------------------------------------------------------------------------------------------
//		Fehlerbehandlung
//------------------------------------------------------------------------------------------------------------------
int			xbn_xslt::getErrorCount()
{
	int ret = m_errorcount;
	m_errorcount = 0;
	return ret;
}

int			xbn_xslt::peekErrorCount()
{
	return m_errorcount;
}

void		xbn_xslt::raiseError( std::string message, xbn_state *state, const char *file,int line )
{
	std::cerr << std::endl << file << ":" << line <<"#" << message << std::endl;
	std::cerr << "[" << ++m_errorcount << "] state ptr " << std::hex << state << std::endl;
}

//------------------------------------------------------------------------------------------------------------------
//			testUnit
//------------------------------------------------------------------------------------------------------------------
bool					xbn_xslt::testUnit()
{
	uint_xbn succeed=0;
	uint_xbn problems=0;

	std::cout << "startup xbn_xslt::testUnit()" << std::endl;
	for( xslt_plugin_map::iterator pc= s_plugin_map.begin(), pe= s_plugin_map.end(); pc!=pe; ++pc )
	{
		if( pc->second )
		{
			std::cout << "Invoke " << pc->first << "->testUnit()" << std::endl;
			if( pc->second->testUnit() )
				++succeed;
			else
				++problems;
		}
	}
	std::cout << "xbn_xslt::testUnit() done" << std::endl;
	std::cout << "--------------------------------------------------"<<std::endl;
	std::cout << "> successfuly " << succeed << std::endl;
	std::cout << "> problems " << problems << std::endl;
	std::cout << "> totaly run " << succeed+problems << std::endl;
	std::cout << "--------------------------------------------------"<<std::endl;
	return problems==0;
}

//------------------------------------------------------------------------------------------------------------------
//			Plugin Manager
//------------------------------------------------------------------------------------------------------------------
void					xbn_xslt::initXSLT()
{
	addPlugin( new xsltplugin_xsl_apply_imports() );
	addPlugin( new xsltplugin_xsl_apply_templates() );
	addPlugin( new xsltplugin_xsl_attribute() );
	addPlugin( new xsltplugin_xsl_attribute_set() );
	addPlugin( new xsltplugin_xsl_call_template() );
	addPlugin( new xsltplugin_xsl_choose() );
	addPlugin( new xsltplugin_xsl_comment() );
	addPlugin( new xsltplugin_xsl_copy() );
	addPlugin( new xsltplugin_xsl_copy_of() );
	addPlugin( new xsltplugin_xsl_decimal_format() );
	addPlugin( new xsltplugin_xsl_element() );
	addPlugin( new xsltplugin_xsl_fallback() );
	addPlugin( new xsltplugin_xsl_for_each() );
	addPlugin( new xsltplugin_xsl_if() );
	addPlugin( new xsltplugin_xsl_include() );
	addPlugin( new xsltplugin_xsl_import() );
	addPlugin( new xsltplugin_xsl_key() );
	addPlugin( new xsltplugin_xsl_message() );
	addPlugin( new xsltplugin_xsl_namespace_alias() );
	addPlugin( new xsltplugin_xsl_number() );
	addPlugin( new xsltplugin_xsl_otherwise() );
	addPlugin( new xsltplugin_xsl_output() );
	addPlugin( new xsltplugin_xsl_param() );
	addPlugin( new xsltplugin_xsl_preserve_space() );
	addPlugin( new xsltplugin_xsl_processing_instruction() );
	addPlugin( new xsltplugin_xsl_sort() );
	addPlugin( new xsltplugin_xsl_strip_space() );
	addPlugin( new xsltplugin_xsl_stylesheet() );
	addPlugin( new xsltplugin_xsl_text() );
	addPlugin( new xsltplugin_xsl_transform() );
	addPlugin( new xsltplugin_xsl_template() );
	addPlugin( new xsltplugin_xsl_value_of() );
	addPlugin( new xsltplugin_xsl_variable() );
	addPlugin( new xsltplugin_xsl_when() );
	addPlugin( new xsltplugin_xsl_with_param() );
}

xbn_xslt_plugin_base*	xbn_xslt::getPlugin( std::string name )
{
	if( s_plugin_map.empty() )
	{
		initXSLT();
	}
	return s_plugin_map[ name ];
}

void					xbn_xslt::addPlugin( xbn_xslt_plugin_base* ptr_plugin )
{
	if( s_plugin_map[ ptr_plugin->name ] )
		delete s_plugin_map[ ptr_plugin->name ];
	s_plugin_map[ ptr_plugin->name ] = ptr_plugin;
}

