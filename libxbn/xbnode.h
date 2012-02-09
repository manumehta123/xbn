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
#ifndef XBNODE_H
#define XBNODE_H
#include "xbstring.h"
#include "sptr.h"
#include <list>
#include <deque>

//#pragma pack(push,4)
class xbnode;
class xbnode_binary;
typedef std::list< sptr<xbnode> > xbnode_list;

class xbnode : public sptr_class
{
	friend class xbdata;
public:
	//------------------------------------------------------------------------------------------------------------------
	//		Node Typen auflistung
	//------------------------------------------------------------------------------------------------------------------
	enum NodeType
	{
		xbn_mask_all	= 65535,
		xbn_root		= 1,
		xbn_node		= 2,
		xbn_attribute	= 4,
		xbn_comment		= 8,
		xbn_cdata		= 16,
		xbn_doctype		= 32,
		xbn_text		= 64,
		xbn_instruction	= 128,
		xbn_temp		= 256
	};

	//------------------------------------------------------------------------------------------------------------------
	//		Eingehaengtes Objekt/Datum
	//------------------------------------------------------------------------------------------------------------------
public:
	xbnode_binary		*m_ptrBinary;

	//------------------------------------------------------------------------------------------------------------------
	//		Member - Werte
	//------------------------------------------------------------------------------------------------------------------
protected:
	xbnode*				m_ptrParent;	// parent Node or Empty
	std::string			m_Data;			// Name / Value
	xbnode_list			m_Nodes;		// child Nodes
	NodeType			m_Type;			// Knotentyp

	//------------------------------------------------------------------------------------------------------------------
	//		Node Name Helper
	//------------------------------------------------------------------------------------------------------------------
public:
	std::string			getName();
	std::string			getNamespace();
	std::string			getFullname();
	void				setFullname( std::string FullName );

	//------------------------------------------------------------------------------------------------------------------
	//		PlainValue Accessor ohne konvertierungen
	//------------------------------------------------------------------------------------------------------------------
public:
	sptr<xbnode>		appendValueNode();
	sptr<xbnode>		getValueNode( bool bInsertNewIfNonde=false );
	std::string			getValue();
	void				setValue( std::string Value );

	//------------------------------------------------------------------------------------------------------------------
	//		Attribut Selektoren
	//------------------------------------------------------------------------------------------------------------------
public:
	sptr<xbnode>		getAttribute( std::string attribute_name );
	uint_xbn			getAttributes( xbnode_list &result_lst );

	std::string			getAttributeText( std::string attribute_name, std::string s_default="" );
	void				setAttributeText( std::string attribute_name, std::string text );

	//------------------------------------------------------------------------------------------------------------------
	//		Childnode selektoren
	//------------------------------------------------------------------------------------------------------------------
public:
	bool				hasChildNodes( uint_xbn filter_flags = xbnode::xbn_node );
	uint_xbn			getChildNodes( xbnode_list &result_lst, bool bRecursive=false,
									   uint_xbn filter_flags = xbnode::xbn_node );

	uint_xbn			getParentNodes( xbnode_list &result_lst, uint_xbn filter_flags = xbnode::xbn_node|xbnode::xbn_root );
	uint_xbn			getFollowingNodes( xbnode_list &result_lst, uint_xbn filter_flags = xbnode::xbn_node );
	uint_xbn			getPrecedingNodes( xbnode_list &result_lst, uint_xbn filter_flags = xbnode::xbn_node );

	sptr<xbnode>		getParent();	// O(1)
	sptr<xbnode>		getRoot();		// O(M) M = m_ptrParent chain
	uint_xbn			getPosition();	// O(N) N = m_Nodes.size() !
	std::string			getNodePath();	// O(N*M)

	//------------------------------------------------------------------------------------------------------------------
	//		Value Type Bestimmen
	//------------------------------------------------------------------------------------------------------------------
public:
	static std::string	getTypeName( xbnode::NodeType type );
	xbnode::NodeType	getType();
	bool				isPattern();
	bool				isBool();
	bool				isNumeric();
	bool				isText();

	//------------------------------------------------------------------------------------------------------------------
	//		Value operatoren mit xml2text und text2xml wrappern
	//------------------------------------------------------------------------------------------------------------------
public:
	bool				getBool();
	double				getNumeric();
	std::string			getText();
	void				setText( std::string text );
	void				appendText( std::string text );

	//------------------------------------------------------------------------------------------------------------------
	//		Vergleichsoperatoren
	//------------------------------------------------------------------------------------------------------------------
public:
	int					equals( sptr<xbnode> ptr_node );

	//------------------------------------------------------------------------------------------------------------------
	//	Konstruktor Destruktor
	//------------------------------------------------------------------------------------------------------------------
private:
						xbnode();
public:
	virtual				~xbnode();

	//------------------------------------------------------------------------------------------------------------------
	//	Konstruktions Helfer
	//------------------------------------------------------------------------------------------------------------------
public:
	static	sptr<xbnode>	createNode( sptr<xbnode> &parent, NodeType type );
	static	sptr<xbnode>	createNode( xbnode *parent, NodeType type );
	sptr<xbnode>			createNode( NodeType type );
	sptr<xbnode>			cloneNode( sptr<xbnode> ptr_parent_node = sptr<xbnode>::Empty, uint_xbn filter_flags = xbnode::xbn_mask_all );

	//------------------------------------------------------------------------------------------------------------------
	//	linked list Helfer (parent/child previous/next)
	//------------------------------------------------------------------------------------------------------------------
	void					removeNode();	// O(N)
	void					removeNode( sptr<xbnode> &child_node_to_remove );


	//------------------------------------------------------------------------------------------------------------------
	//	Fehler Helfer
	//------------------------------------------------------------------------------------------------------------------
	void				raiseError( std::string message, const char* file=__FILE__, int line=__LINE__ );
};
//#pragma pack(pop)
#endif // XBNODE_H
