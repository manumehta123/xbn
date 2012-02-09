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
#include "xbnode.h"
#include "xbn_helper.h"
#include <iostream>
#include <algorithm>


std::string xbnode::getTypeName( xbnode::NodeType type )
{
	std::string ret;
	switch( type )
	{
	case xbnode::xbn_root:
		ret = "!ROOT";
		break;
	case xbnode::xbn_doctype:
		ret = "!DOCTYPE";
		break;
	case xbnode::xbn_node:
		ret = "!NODE";
		break;
	case xbnode::xbn_temp:
		ret = "!TEMP";
		break;
	case xbnode::xbn_text:
		ret = "!TEXT";
		break;
	case xbnode::xbn_instruction:
		ret = "!INSTUCTION";
		break;
	case xbnode::xbn_attribute:
		ret = "!ATTRIBUTE";
		break;
	case xbnode::xbn_comment:
		ret = "!COMMENT";
		break;
	case xbnode::xbn_cdata:
		ret = "!CDATA";
		break;
	default:
		ret = "!UNDEF";
		break;
	}
	return ret;
}

xbnode::NodeType	xbnode::getType()
{
	return this->m_Type;
}

std::string			xbnode::getName()
{
	size_t nsq = m_Data.find(':');
	if( nsq!=std::string::npos )
		return m_Data.substr(nsq+1);

	return m_Data;
}

std::string			xbnode::getNamespace()
{
	size_t nsq = m_Data.find(':');
	if( nsq!=std::string::npos )
		return m_Data.substr(0,nsq-1);

	return "";
}

std::string			xbnode::getFullname()
{
	return this->m_Data;
}

void				xbnode::setFullname( std::string FullName )
{
	this->m_Data = FullName;
}

sptr<xbnode>	xbnode::appendValueNode()
{
	sptr<xbnode> ret_node;
	switch( this->m_Type )
	{
	case xbn_attribute:
	case xbn_node:
	case xbn_root:
		{
			ret_node = this->createNode( this, xbn_text );
		}break;
	case xbn_text:
	case xbn_temp:
	case xbn_comment:
	case xbn_cdata:
	case xbn_instruction:
	case xbn_doctype:
		ret_node = this;
		break;
	default:
		raiseError( "xbnode::getValueNode() drop value", __FILE__,__LINE__ );
		break;
	}

	return ret_node;
}

sptr<xbnode>	xbnode::getValueNode( bool bInsertNewIfNonde )
{
	sptr<xbnode> ret_node;
	switch( this->m_Type )
	{
	case xbn_attribute:
	case xbn_node:
	case xbn_root:
		{
			xbnode_list col;
			if( this->getChildNodes( col, false, xbnode::xbn_text ) )
			{
				ret_node = col.front();
			}
			else
			{
				if( bInsertNewIfNonde )
				{
					ret_node = this->createNode( this, xbn_text );
				}
			}
		}break;
	case xbn_text:
	case xbn_temp:
	case xbn_comment:
	case xbn_cdata:
	case xbn_instruction:
	case xbn_doctype:
		ret_node = this;
		break;
	default:
		raiseError( "xbnode::getValueNode() drop value", __FILE__,__LINE__ );
		break;
	}

	return ret_node;
}

std::string			xbnode::getValue()
{
	sptr<xbnode> node = this->getValueNode();
	if( node )
		return node->m_Data;
	return "";
}

void				xbnode::setValue( std::string wert )
{
	getValueNode( true )->m_Data = wert;
}

sptr<xbnode>	xbnode::getAttribute( std::string attribute_name )
{
	for( xbnode_list::iterator pc = m_Nodes.begin(), pe=m_Nodes.end(); pc!=pe; ++pc )
	{
		if( ((*pc)->m_Type & xbn_attribute) &&
			((*pc)->getFullname()==attribute_name || (*pc)->getName()==attribute_name) )
		{
			return *pc;
		}
	}
	return sptr<xbnode>::Empty;
}

uint_xbn				xbnode::getAttributes( xbnode_list &result_lst )
{
	return getChildNodes( result_lst, false, xbnode::xbn_attribute );
}

bool				xbnode::hasChildNodes( uint_xbn filter_flags )
{
	for( xbnode_list::iterator pc = m_Nodes.begin(), pe=m_Nodes.end(); pc!=pe; ++pc )
	{
		if( (*pc)->m_Type & filter_flags )
		{
			return true;
		}
	}
	return false;
}

uint_xbn				xbnode::getChildNodes( xbnode_list &result_lst, bool bRecursive, uint_xbn filter_flags )
{
	uint_xbn count = 0;
	for( xbnode_list::iterator pc=m_Nodes.begin(), pe=m_Nodes.end(); pc!=pe; ++pc )
	{
		if( (*pc)->m_Type & filter_flags )
		{
			result_lst.push_back( *pc );
			++count;

			if( bRecursive && (*pc)->m_Type==xbnode::xbn_node )
			{
				count+= (*pc)->getChildNodes( result_lst, bRecursive, filter_flags );
			}
		}
	}
	return count;
}

uint_xbn			xbnode::getParentNodes( xbnode_list &result_lst,	uint_xbn filter_flags )
{
	uint_xbn count = 0;
	xbnode*	ptr_node = this->m_ptrParent;
	while( ptr_node )
	{
		if( ptr_node->m_Type&filter_flags )
		{
			result_lst.push_back( ptr_node );
			++count;
			ptr_node = ptr_node->m_ptrParent;
		}
		else
		{
			break;
		}
	}
	return count;
}

uint_xbn			xbnode::getFollowingNodes( xbnode_list &result_lst, uint_xbn filter_flags )
{
	uint_xbn count = 0;

	xbnode_list::iterator pe= this->m_ptrParent->m_Nodes.end();
	xbnode_list::iterator pc= std::find( this->m_ptrParent->m_Nodes.begin(),pe, this );

	if( pe!=pc ) ++pc;
	for( ;pc!=pe; ++pc )
	{
		if( (*pc)->m_Type&filter_flags )
		{
			result_lst.push_back( *pc );
			++count;
		}
	}
	return count;
}

uint_xbn			xbnode::getPrecedingNodes( xbnode_list &result_lst, uint_xbn filter_flags )
{
	uint_xbn count = 0;

	xbnode_list::reverse_iterator pe= this->m_ptrParent->m_Nodes.rend();
	xbnode_list::reverse_iterator pc= std::find( this->m_ptrParent->m_Nodes.rbegin(),pe, this );

	if( pe!=pc ) ++pc;
	for( ;pc!=pe; ++pc )
	{
		if( (*pc)->m_Type&filter_flags )
		{
			result_lst.push_back( *pc );
			++count;
		}
	}
	return count;
}

//------------------------------------------------------------------------------------------------------------------
//	Konstruktions Helfer
//------------------------------------------------------------------------------------------------------------------
sptr<xbnode>	xbnode::createNode( xbnode *parent, NodeType type )
{
	sptr<xbnode> new_clone = new xbnode();

	// Primaerdaten Kopieren
	new_clone->m_Type      = type;
	new_clone->m_ptrParent = parent;

	if( parent )
	{
		if( new_clone->m_Type & xbn_attribute )
			parent->m_Nodes.push_front( new_clone );
		else
			parent->m_Nodes.push_back( new_clone );
	}
	return new_clone;
}

sptr<xbnode>	xbnode::createNode( sptr<xbnode> &parent, NodeType type )
{
	return createNode( (xbnode*)parent, type );
}

sptr<xbnode>	xbnode::createNode( NodeType type )
{
	return createNode( this, type );
}

void			xbnode::removeNode()
{
	if( m_ptrParent )
	{
		this->m_ptrParent->m_Nodes.remove( this );
		this->m_ptrParent = NULL;
	}
}

void			xbnode::removeNode( sptr<xbnode> &child_node_to_remove )
{
	if( child_node_to_remove )
	{
		this->m_Nodes.remove( child_node_to_remove );
		child_node_to_remove->m_ptrParent = NULL;
	}
}

sptr<xbnode>	xbnode::cloneNode( sptr<xbnode> ptr_parent_node, uint_xbn filter_flags )
{
	sptr<xbnode> new_clone = xbnode::createNode( ptr_parent_node, this->m_Type );

	// Primaerdaten Zeiger Kopieren
	new_clone->m_ptrBinary = this->m_ptrBinary;
	new_clone->m_Data = this->m_Data;

	uint_xbn ext_filter_flags = filter_flags;
	if( filter_flags&xbn_attribute ) ext_filter_flags|=xbn_text;

	// Childs kopieren
	for( xbnode_list::iterator pc = m_Nodes.begin(), pe=m_Nodes.end(); pc!=pe; ++pc )
	{
		if( (*pc)->m_Type & filter_flags )
		{
			(*pc)->cloneNode( new_clone, ext_filter_flags );
		}
	}

	return new_clone;
}

sptr<xbnode>	xbnode::getParent()
{
	return this->m_ptrParent;
}

sptr<xbnode>	xbnode::getRoot()
{
	sptr<xbnode> node = this;
	while( node && node->m_Type!=xbnode::xbn_root )
	{
		node = node->m_ptrParent;
	}
	return node;
}

uint_xbn			xbnode::getPosition()
{
	uint_xbn pos=1;
	if( m_ptrParent && !m_ptrParent->m_Nodes.empty() )
	{
		for( xbnode_list::iterator pc = m_ptrParent->m_Nodes.begin(), pe=m_ptrParent->m_Nodes.end(); pc!=pe; ++pc )
		{
			if( *pc == this )
				break;
			if( (*pc)->m_Type & xbnode::xbn_node ) ++pos;
		}
	}
	return pos;
}

std::string		xbnode::getNodePath()
{
	std::string ret;
	sptr<xbnode> node = this;
	while( node && node->m_Type!=xbnode::xbn_root )
	{
		std::string tag;
		switch( node->m_Type )
		{
		case xbn_attribute:
			tag = "@"+node->getFullname();
			break;
		case xbn_cdata:
		case xbn_comment:
		case xbn_text:
		case xbn_doctype:
		case xbn_instruction:
		case xbn_temp:
			tag = xbnode::getTypeName( node->m_Type );
			break;
		case xbn_node:
			tag = node->getFullname()+"["+ zahlToString( node->getPosition() ) +"]";
			break;
		default:
			tag = "!UNDEF("+zahlToString( (int)node->m_Type )+")";
			break;
		}
		ret = "/"+tag+ret;
		node = node->getParent();
	}

	return ret;
}

bool	xbnode::isPattern()
{
	if( this->getText()!="" )
		return true;
	return false;
}

bool	xbnode::isBool()
{
	if( this->getText()=="true" ||
		this->getText()=="false" )
		return true;

	return false;
}

bool	xbnode::isNumeric()
{
	if( this->getText()!="" && this->getText().find_first_not_of("-0123456789.")==std::string::npos )
		return true;
	return false;
}

bool	xbnode::isText()
{
	return this->m_Type!=xbnode::xbn_root;
}

bool	xbnode::getBool()
{
	if( isBool() )
		return (this->getText()=="true");
	if( isNumeric() )
		return getNumeric()!=0;
	if( isText() )
		return !getText().empty();

	raiseError( "getBool() cant convert", __FILE__,__LINE__);
	return false;
}

double	xbnode::getNumeric()
{
	if( isBool() )
		return getBool()? 1:0;
	if( isNumeric() )
		return stringToZahl( getText() );

	raiseError( "getNumeric() cant convert", __FILE__,__LINE__);
	return 0;
}

std::string	xbnode::getText()
{
	std::string ret;
	switch( m_Type )
	{
	case xbn_attribute:
		ret = getValue();
		if( ret.find_first_of("\"'")==0 &&
			ret.find_last_of("\"'")==ret.size()-1 )
		{
			ret=ret.substr(1,ret.size()-2);
		}
		break;
	case xbn_cdata:
	case xbn_comment:
	case xbn_text:
	case xbn_temp:
		ret = getValue();
		break;
	case xbn_node:
		{
			xbnode_list list;
			getChildNodes( list, false, xbnode::xbn_text|xbnode::xbn_cdata );
			for(xbnode_list::iterator pc=list.begin(), pe=list.end(); pc!=pe; ++pc )
			{
				ret+=(*pc)->getValue();
			}
		}break;
	default:
		raiseError( "getText() cant convert", __FILE__,__LINE__);
		break;
	}

	return Xml2Text( ret );
}

void	xbnode::setText( std::string text )
{
	switch( m_Type )
	{
	case xbn_attribute:
	case xbn_text:
	case xbn_temp:
		setValue( Text2Xml( text ) );
		break;
	case xbn_cdata:
	case xbn_comment:
	case xbn_instruction:
	case xbn_doctype:
		setValue( text );
		break;
	case xbn_node:
		{
			setValue( Text2Xml( text ) );
		}break;
	default:
		raiseError( "setText() cant convert '"+text+"' to "+getTypeName( this->m_Type ) , __FILE__,__LINE__);
		break;
	}
}

void	xbnode::appendText( std::string text )
{
	if( hasChildNodes() )
	{
		// !TEXT einfuegen
		sptr<xbnode> neu_text = new xbnode();
		neu_text->m_Type = xbnode::xbn_text;
		neu_text->setText( text );
		neu_text->m_ptrParent = this;
		this->m_Nodes.push_back( neu_text );
	}
	else
	{
		setText( getText() + text );
	}
}

int		xbnode::equals( sptr<xbnode> ptr_node )
{
	//std::cout << "equals " << this->getText() << "==" << ptr_node->getText() << std::endl;

	if( ptr_node==this )
		return 0;

	if( this->isNumeric() && ptr_node->isNumeric() )
	{
		double v1 = this->getNumeric(), v2=ptr_node->getNumeric();
		if( v1>v2 ) return -1;
		if( v1<v2 ) return 1;
		return 0;
	}

	if( this->isText() && ptr_node->isText() )
	{
		std::string v1 = this->getText(), v2 = ptr_node->getText();
		if( v1>v2 ) return -1;
		if( v1<v2 ) return 1;
		return 0;
	}

	raiseError( "equals() cant convert types", __FILE__,__LINE__);
	return -666;
}


std::string		xbnode::getAttributeText( std::string attribute_name, std::string s_default )
{
	sptr<xbnode> result= getAttribute( attribute_name );

	return result ? result->getText() : s_default;
}

void			xbnode::setAttributeText( std::string attribute_name, std::string text )
{
	sptr<xbnode> result= getAttribute( attribute_name );
	if( result==sptr<xbnode>::Empty )
	{
		result = this->createNode( xbnode::xbn_attribute );
		result->m_Data = attribute_name;
		result->setValue( text );
	}
	else
	{
		result->setValue( text );
	}
}

void	xbnode::raiseError( std::string message, const char* file, int line )
{
	std::cerr << file << ":" << line << "#" << message << std::endl;
}

xbnode::xbnode()
{
	this->m_Type		= xbnode::xbn_root;
	this->m_ptrParent = NULL;
	this->m_ptrBinary = NULL;
}

xbnode::~xbnode()
{
	if( this->m_ptrBinary )
	{
		this->m_ptrBinary = NULL;
	}
}

