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
#include "xslt_plugins/xbn_xslt_plugins_1_0.h"
#include "xbn_xpath.h"


xsltplugin_xsl_comment::xsltplugin_xsl_comment( )
{
	name = "xsl:comment";
	min_parameter=0;
	max_parameter=0;
	/*
	  The <xsl:comment> element is used to create a comment node in the result tree.
	  */
}

bool xsltplugin_xsl_comment::testUnit()
{
	return true;
}

bool xsltplugin_xsl_comment::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	sptr<xbnode> node = state.pCurrentNode->createNode( xbnode::xbn_comment );

	// Werte Text uebertragen
	node->setText( state.pTemplateNode->getText() );

	// etwaiges sub_template anwenden
	xbn_state sub_state( state );
	sub_state.pCurrentNode = node;
	return p_xbn_xslt->process_template( sub_state );
}


//----------------------------------------------------------------------------------------------------------------------

xsltplugin_xsl_element::xsltplugin_xsl_element( )
{
	name = "xsl:element";
	min_parameter=0;
	max_parameter=3;
	/*
	  The <xsl:element> element is used to create an element node in the output document

name	name	Required. Specifies the name of the element to be created (the value of the name attribute can be set to an expression that is computed at run-time, like this: <xsl:element name="{$country}" />
namespace	URI	Optional. Specifies the namespace URI of the element (the value of the namespace attribute can be set to an expression that is computed at run-time, like this: <xsl:element name="{$country}" namespace="{$someuri}"/>
use-attribute-sets	namelist	Optional. A white space separated list of attribute-sets containing attributes to be added to the element
	  */
	addParameter("name",	false,	"name");
	addParameter("namespace",	true,	"URI");
	addParameter("use-attribute-sets",	true,	"namelist");
}

bool xsltplugin_xsl_element::testUnit()
{
	return true;
}

bool xsltplugin_xsl_element::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	sptr<xbnode> node = state.pCurrentNode->createNode( xbnode::xbn_node );

	// Werte Text uebertragen
	node->setText( state.pTemplateNode->getText() );

	// etwaiges sub_template anwenden
	xbn_state sub_state( state );
	sub_state.pCurrentNode = node;
	return p_xbn_xslt->process_template( sub_state );
}


//----------------------------------------------------------------------------------------------------------------------

xsltplugin_xsl_text::xsltplugin_xsl_text( )
{
	name = "xsl:text";
	min_parameter=0;
	max_parameter=1;
	/*
The <xsl:text> element is used to write literal text to the output.

Tip: This element may contain literal text, entity references, and #PCDATA.

disable-output-escaping	yes
no	Optional. "yes" indicates that special characters (like "<") should be output as is.
"no" indicates that special characters (like "<") should be output as "&lt;". Default is "no".
This attribute is not supported by Netscape 6
	  */
	addParameter("disable-output-escaping",	true,	"yes|no");
}

bool xsltplugin_xsl_text::testUnit()
{
	return true;
}

bool xsltplugin_xsl_text::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	sptr<xbnode> node = state.pCurrentNode->createNode( xbnode::xbn_text );

	// Werte Text uebertragen
	node->setText( state.pTemplateNode->getText() );

	// etwaiges sub_template anwenden
	xbn_state sub_state( state );
	sub_state.pCurrentNode = node;
	return p_xbn_xslt->process_template( sub_state );
}

//----------------------------------------------------------------------------------------------------------------------


xsltplugin_xsl_processing_instruction::xsltplugin_xsl_processing_instruction( )
{
	name = "xsl:processing-instruction";
	min_parameter=0;
	max_parameter=0;
	/*
	  The <xsl:processing-instruction> element writes a processing instruction to the output.

	  name	process-name	Required. Specifies the name of the processing instruction
	  */
	addParameter("name",	false,	"process-name");
}

bool xsltplugin_xsl_processing_instruction::testUnit()
{
	return true;
}

bool xsltplugin_xsl_processing_instruction::operator() (xbn_state &state, xbn_xslt *p_xbn_xslt )
{
	sptr<xbnode> node = state.pCurrentNode->createNode( xbnode::xbn_instruction );

	// Werte Text uebertragen
	node->setText( state.pTemplateNode->getText() );

	// etwaiges sub_template anwenden
	xbn_state sub_state( state );
	sub_state.pCurrentNode = node;
	return p_xbn_xslt->process_template( sub_state );
}
