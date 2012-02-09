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
#include <sstream>
#include "xbdata.h"
#include "xbstring.h"
#include "xbnode.h"
#include "xbnparser.h"
#include "xbnnode_plugins.h"
#include "save_delete.h"
#include "xbn_helper.h"


xbdata::xbdata()
{
	//std::cout << std::hex << this << "::xbdata()" << std::endl; )
	m_data = "";
	m_in_buildprocess = false;
	m_ptr_xbnode_root = sptr<xbnode>::Empty;
	m_ptr_plugin_manager = NULL;

	read( "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n" );
}

xbdata::xbdata( std::string data )
{
	//std::cout << std::hex << this << "::xbdata(data)" << std::endl;
	m_data = "";
	m_ptr_xbnode_root = sptr<xbnode>::Empty;
	m_ptr_plugin_manager= NULL;
	m_in_buildprocess = false;
	read( data );
}

xbdata::xbdata( std::istream &input_stream, uint_xbn capacity )
{
	//std::cout << std::hex << this << "::xbdata(stream)" << std::endl;
	m_data = "";
	if( capacity ) m_data.reserve( capacity );
	m_ptr_xbnode_root = sptr<xbnode>::Empty;
	m_ptr_plugin_manager= NULL;
	m_in_buildprocess = false;
	read( input_stream );
}

xbdata::~xbdata()
{
	//std::cout << std::hex << this << "::~xbdata()" << std::endl;
	m_data = "";
}

void		xbdata::setPluginManager(xbnnode_plugin_manager	*ptr_plugin_manager)
{
	m_ptr_plugin_manager = ptr_plugin_manager;
}

sptr<xbnode>	xbdata::getRootNode()
{
	return m_ptr_xbnode_root;
}

bool		xbdata::read( std::istream &input_stream, uint_xbn capacity )
{
	m_data = "";
	m_ptr_xbnode_root = sptr<xbnode>::Empty;

	// Loading & Parsing
	std::clog << std::endl;
	m_ptr_xbnode_root = create_xbnode( xbnode::createNode(0,xbnode::xbn_root), input_stream, capacity );
	std::clog << "\n#msg done" << std::endl;
	return m_ptr_xbnode_root;
}

bool		xbdata::read( std::string data )
{
	m_data = data;
	m_ptr_xbnode_root = sptr<xbnode>::Empty;

	std::stringstream ss( m_data );
	m_ptr_xbnode_root = create_xbnode( xbnode::createNode(0,xbnode::xbn_root), ss, m_data.length() );
	return m_ptr_xbnode_root;
}

sptr<xbnode>	xbdata::create_xbnode( sptr<xbnode> ptr_rootnode, std::istream &input_stream, uint_xbn capacity )
{
	xbnparser		xbnp;
	sptr<xbnode>	ptr_current_node = ptr_rootnode;
	bool			bInAttribute=false;

	m_in_buildprocess = true;
	int old_percent	= -1;
	while( xbnp.processStream(input_stream) && xbnp.getToken()!="" )
	{
		//std::cout << "token " << xbnp.getToken() << std::endl;

		int new_percent = (100*input_stream.tellg())/capacity;
		if( new_percent!=old_percent )
		{
			std::clog << "\r#msg parsing "<<new_percent << "% (" << sptr_class::getCurrentObjectCount() <<")";
			std::clog.flush();
			old_percent=new_percent;
		}

		std::string token = xbnp.getToken();

		if( token=="<" ) // neuer Knoten, ende !TEXT
		{
			if( ptr_current_node->getType()!=xbnode::xbn_node &&
				ptr_current_node->getType()!=xbnode::xbn_root )
			{
				raiseError("< node requires node or root "+xbnp.getToken() + " in ", __FILE__, __LINE__ );
				break;
			}

			// Knotennamen auslesen
			if( !xbnp.processStream(input_stream) )
			{
				raiseError("unexpected eof() ", __FILE__, __LINE__ );
				break;
			}

			ptr_current_node = ptr_current_node->createNode( xbnode::xbn_node );
			ptr_current_node->m_Data = xbnp.getToken();

			if( m_ptr_plugin_manager )
			{
				xbnnode_plugin_base* plugin = m_ptr_plugin_manager->getPlugin( xbnp.getToken() );
				if( plugin )
				{
					ptr_current_node->m_ptrBinary = plugin->createBinary( ptr_current_node );
				}
			}
			bInAttribute = true;
		}else
		if( token==">" ) // ende der Attributliste, anfang !TEXT
		{

			bInAttribute = false;
		}else
		if( token=="</" ) // ende eines knotens, ende !TEXT
		{
			if( ptr_current_node->getType()!=xbnode::xbn_node &&
				ptr_current_node->getType()!=xbnode::xbn_root )
			{
				raiseError("</ requires node or root "+xbnp.getToken(), __FILE__, __LINE__ );
				break;
			}

			// Knotennamen abgleichen
			if( !xbnp.processStream(input_stream) )
			{
				raiseError("unexpected eof() ", __FILE__, __LINE__ );
				break;
			}
			if( xbnp.getToken()!=ptr_current_node->m_Data )
			{
				raiseError("closing token does not match "+xbnp.getToken()+"!="+ptr_current_node->getFullname(), __FILE__, __LINE__ );
				break;
			}

			// Abschliessendes > verifizieren
			if( !xbnp.processStream(input_stream) || xbnp.getToken()!=">" )
			{
				raiseError("unexpected eof() ", __FILE__, __LINE__ );
				break;
			}

			if( ptr_current_node->m_ptrBinary )
				ptr_current_node->m_ptrBinary->OnLoad();

			ptr_current_node = ptr_current_node->getParent();
		}else
		if( token=="/>" ) // ende eines knotens, anfang !TEXT
		{
			if( ptr_current_node->getType()!=xbnode::xbn_node &&
				ptr_current_node->getType()!=xbnode::xbn_root )
			{
				raiseError("/> requires node or root "+xbnp.getToken(), __FILE__,__LINE__ );
				break;
			}
			if( ptr_current_node->m_ptrBinary )
				ptr_current_node->m_ptrBinary->OnLoad();

			ptr_current_node = ptr_current_node->getParent();
			bInAttribute = false;
		}else
		if( token=="<?" ) // begin instruktion,  ende !TEXT
		{
			if(  ptr_current_node->getType()!=xbnode::xbn_root )
			{
				raiseError("instructions can only appear in root node "+xbnp.getToken(), __FILE__, __LINE__ );
				break;
			}

			std::string data =  xbnp.getToken()+xbnp.readTill( input_stream, "?>");
			if( data.length()<4 )
			{
				raiseError("!INSTRUCTION requires <? ?> structure ",__FILE__,__LINE__ );
				break;
			}
			data = data.substr(2,data.length()-4);

			// new DocType Node
			ptr_current_node = ptr_current_node->createNode( xbnode::xbn_instruction );
			ptr_current_node->m_Data = data;
			ptr_current_node = ptr_current_node->getParent();
		}else
		if( token=="?>" ) // ende instruktion
		{
			raiseError("?> out of !INSTRUCTION ",__FILE__,__LINE__ );
			break;
		}else
		if( token=="<!--" ) // begin Kommentar , ende !TEXT
		{
			if( ptr_current_node->getType()!=xbnode::xbn_node &&
				ptr_current_node->getType()!=xbnode::xbn_root )
			{
				raiseError("!COMMENT requires !NODE|!ROOT "+xbnp.getToken(),__FILE__,__LINE__ );
				break;
			}

			std::string data = xbnp.getToken() + xbnp.readTill( input_stream, "-->");
			if( data.length()<7 )
			{
				raiseError("!COMMENT requires <!-- --> structure ",__FILE__,__LINE__ );
				break;
			}
			data = data.substr(4, data.length()-7 );

			ptr_current_node = ptr_current_node->createNode( xbnode::xbn_comment );
			ptr_current_node->m_Data = data;
			ptr_current_node = ptr_current_node->getParent();
		}else
		if( token=="<![CDATA[" ) // beginn cdata , ende !TEXT
		{
			if( ptr_current_node->getType()!=xbnode::xbn_node &&
				ptr_current_node->getType()!=xbnode::xbn_root )
			{
				raiseError("!CDATA requires !NODE|!ROOT "+xbnp.getToken(),__FILE__,__LINE__ );
				break;
			}

			std::string data = xbnp.getToken() + xbnp.readTill( input_stream, "]]>");
			if( data.length()<12 )
			{
				raiseError("!CDATA requires <![CDATA[ ]]> structure ",__FILE__,__LINE__ );
				break;
			}
			data = data.substr(9, data.length()-12 );

			ptr_current_node = ptr_current_node->createNode( xbnode::xbn_cdata );
			ptr_current_node->m_Data = data;
			ptr_current_node = ptr_current_node->getParent();
		}else
		if( token=="<!" )
		{
			if( ptr_current_node->getType()!=xbnode::xbn_node &&
				ptr_current_node->getType()!=xbnode::xbn_root )
			{
				raiseError("!DOCTYPE requires !NODE|!ROOT "+xbnp.getToken(),__FILE__,__LINE__ );
				break;
			}

			std::string data = xbnp.getToken() + xbnp.readTill( input_stream, ">");
			if( data.length()<3 )
			{
				raiseError("!DOCTYPE requires <! > structure ",__FILE__,__LINE__ );
				break;
			}
			data = data.substr(2, data.length()-3 );

			ptr_current_node = ptr_current_node->createNode( xbnode::xbn_doctype );
			ptr_current_node->m_Data = data;
			ptr_current_node = ptr_current_node->getParent();
		}
		else // Attribut
		{
			if( bInAttribute )
			{
				if(	ptr_current_node->getType()!=xbnode::xbn_node )
				{
					raiseError("attribute requires node "+xbnp.getToken(), __FILE__, __LINE__ );
					break;
				}

				std::string attribut_key = xbnp.getToken();

				// Abschliessendes > verifizieren
				if( !xbnp.processStream(input_stream) || xbnp.getToken()!="=" )
				{
					raiseError("unexpected eof()/token "+ xbnp.getToken(), __FILE__, __LINE__ );
					break;
				}
				if( !xbnp.processStream(input_stream) )
				{
					raiseError("unexpected eof()/token ", __FILE__, __LINE__ );
					break;
				}
				std::string attribut_value = xbnp.getToken();


				// Attribut
				ptr_current_node = ptr_current_node->createNode( xbnode::xbn_attribute );
				ptr_current_node->m_Data = attribut_key;
				ptr_current_node->appendValueNode()->m_Data = attribut_value;

				ptr_current_node = ptr_current_node->getParent();
			}
			else
			{
				std::string data = xbnp.getToken() + xbnp.readTillStop( input_stream, '<' );

				if( data.length()>0 && data.find_first_not_of(" \r\n\t")!=std::string::npos )
				{
					if(	ptr_current_node->getType()!=xbnode::xbn_node )
					{
						raiseError("!TEXT ["+data+"] requires !Node gets "+ xbnode::getTypeName( ptr_current_node->getType() ), __FILE__, __LINE__ );
						break;
					}
					ptr_current_node->appendValueNode()->m_Data = data;
				}
			}
		}
	}

	m_in_buildprocess = false;
	return ptr_rootnode;
}

bool		xbdata::write( std::ostream &output_stream )
{
	return flush_xbnode( sptr<xbnode>::Empty, output_stream );
}

bool		 xbdata::flush_xbnode( sptr<xbnode> ptr_node, std::ostream &output_stream )
{
	sptr<xbnode>	ptr_current_node = ptr_node ? ptr_node : m_ptr_xbnode_root;

	if( ptr_current_node )
	{
		bool ret=true;

		if( false )
		{
			switch( ptr_current_node->getType() )
			{
			case xbnode::xbn_doctype:
				output_stream << "xbn_doctype:";
				break;
			case xbnode::xbn_root:
				output_stream << "xbn_root:";
				break;
			case xbnode::xbn_node:
				output_stream << "xbn_node:";
				break;
			case xbnode::xbn_comment:
				output_stream << "xbn_comment:";
				break;
			case xbnode::xbn_cdata:
				output_stream << "xbn_cdata:";
				break;
			case xbnode::xbn_text:
				output_stream << "xbn_text:";
				break;
			case xbnode::xbn_temp:
				output_stream << "xbn_temp:";
				break;
			case xbnode::xbn_attribute:
				output_stream << "xbn_attribute:";
				break;
			case xbnode::xbn_instruction:
				output_stream << "xbn_instruction:";
				break;
			default:
				output_stream << "undef:";
				break;
			}
		}

		switch( ptr_current_node->getType() )
		{
		case xbnode::xbn_instruction:
			{
				std::string name = ptr_current_node->m_Data;

				output_stream << "<?" << name;
				xbnode_list att_col;
				if( ptr_current_node->getAttributes( att_col ) )
				{
					for( xbnode_list::iterator pc = att_col.begin(), pe = att_col.end();pc!=pe;++pc )
					{
						output_stream << " ";
						ret &= flush_xbnode( *pc, output_stream );
					}
				}
				output_stream << "?>"<<std::endl;
			}
			break;
		case xbnode::xbn_doctype:
			{
				std::string name = ptr_current_node->m_Data;

				output_stream << "<!" << name;
				xbnode_list att_col;
				if( ptr_current_node->getAttributes( att_col ) )
				{
					for( xbnode_list::iterator pc = att_col.begin(), pe = att_col.end();pc!=pe;++pc )
					{
						output_stream << " ";
						ret &= flush_xbnode( *pc, output_stream );
					}
				}
				output_stream << "/>"<<std::endl;
			}
			break;
		case xbnode::xbn_root:
			{
				//output_stream << "<>"<<std::endl;
				xbnode_list node_col;
				if( ptr_current_node->getChildNodes( node_col, false, xbnode::xbn_node|xbnode::xbn_text|xbnode::xbn_cdata ) )
				{
					for( xbnode_list::iterator pc = node_col.begin(), pe = node_col.end();pc!=pe;++pc )
					{
						ret &= flush_xbnode( *pc, output_stream );
					}
				}
				//output_stream << "</>"<<std::endl;
			}break;
		case xbnode::xbn_node:
			{
				std::string name = ptr_current_node->m_Data;
				std::string wert = ptr_current_node->getValue();

				output_stream << "<" << name;
				xbnode_list att_col;
				if( ptr_current_node->getAttributes( att_col ) )
				{
					for( xbnode_list::iterator pc = att_col.begin(), pe = att_col.end();pc!=pe;++pc )
					{
						output_stream << " ";
						ret &= flush_xbnode( *pc, output_stream );
					}
				}
				xbnode_list node_col;
				if( ptr_current_node->getChildNodes( node_col, false, xbnode::xbn_node|xbnode::xbn_text|xbnode::xbn_cdata ) )
				{
					output_stream << ">"<<std::endl;
					for( xbnode_list::iterator pc = node_col.begin(), pe = node_col.end();pc!=pe;++pc )
					{
						ret &= flush_xbnode( *pc, output_stream );
					}
					output_stream << "</"<<name<<">"<<std::endl;
				}
				else
					if( wert.length() )
				{
					output_stream << ">" <<  wert << "</"<<name<<">"<<std::endl;
				}
				else
				{
					output_stream << "/>" << std::endl;
				}
			}break;
		case xbnode::xbn_comment:
			output_stream << "<!--" << ptr_current_node->m_Data << "-->" << std::endl;
			break;
		case xbnode::xbn_cdata:
			output_stream << "<![CDATA[[" << ptr_current_node->m_Data << "]]>" << std::endl;
			break;
		case xbnode::xbn_text:
			output_stream << ptr_current_node->m_Data;
			break;
		case xbnode::xbn_temp:
			//raiseError( "temp_node in xbnodetree !" );
			output_stream << ptr_current_node->m_Data;
			break;
		case xbnode::xbn_attribute:
			output_stream <<  ptr_current_node->m_Data << "=" <<  ptr_current_node->getValue();
			break;
		default:
			// Ignorieren
			raiseError( "flush() undef type in nodechain", __FILE__, __LINE__ );
			ret=false;
			break;
		}
		return ret;
	}
	return false;
}

void		xbdata::raiseError( std::string message, const char *file, int line  )
{
	std::cerr << "xbdata::raiseError" << std::endl;
	std::cerr << "["<< std::dec << line << "]" << file << " " << message << std::endl;
}
