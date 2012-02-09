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
#ifndef XBN_XSLT_PLUGINS_1_0_H
#define XBN_XSLT_PLUGINS_1_0_H

#include "xbn_xslt_plugins.h"

//---------------------------------------------------
//  Plugins  XSLT 1.0
//---------------------------------------------------
struct xsltplugin_xsl_template : xbn_xslt_plugin_base
{
	xsltplugin_xsl_template();

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};


struct xsltplugin_xsl_apply_imports : xbn_xslt_plugin_base
{
	xsltplugin_xsl_apply_imports();

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_apply_templates : xbn_xslt_plugin_base
{
	xsltplugin_xsl_apply_templates( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_attribute : xbn_xslt_plugin_base
{
	xsltplugin_xsl_attribute( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_attribute_set : xbn_xslt_plugin_base
{
	xsltplugin_xsl_attribute_set( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_call_template : xbn_xslt_plugin_base
{
	xsltplugin_xsl_call_template( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_choose : xbn_xslt_plugin_base
{
	xsltplugin_xsl_choose( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_when : xbn_xslt_plugin_base
{
	xsltplugin_xsl_when( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_otherwise : xbn_xslt_plugin_base
{
	xsltplugin_xsl_otherwise( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_comment : xbn_xslt_plugin_base
{
	xsltplugin_xsl_comment( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_copy : xbn_xslt_plugin_base
{
	xsltplugin_xsl_copy( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_copy_of : xbn_xslt_plugin_base
{
	xsltplugin_xsl_copy_of( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_decimal_format : xbn_xslt_plugin_base
{
	xsltplugin_xsl_decimal_format( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_element : xbn_xslt_plugin_base
{
	xsltplugin_xsl_element( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_fallback : xbn_xslt_plugin_base
{
	xsltplugin_xsl_fallback( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_for_each : xbn_xslt_plugin_base
{
	xsltplugin_xsl_for_each( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_if : xbn_xslt_plugin_base
{
	xsltplugin_xsl_if( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_include : xbn_xslt_plugin_base
{
	xsltplugin_xsl_include( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_import : xbn_xslt_plugin_base
{
	xsltplugin_xsl_import( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_key : xbn_xslt_plugin_base
{
	xsltplugin_xsl_key( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_message : xbn_xslt_plugin_base
{
	xsltplugin_xsl_message( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_namespace_alias : xbn_xslt_plugin_base
{
	xsltplugin_xsl_namespace_alias( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_number : xbn_xslt_plugin_base
{
	xsltplugin_xsl_number( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_output : xbn_xslt_plugin_base
{
	xsltplugin_xsl_output( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_param : xbn_xslt_plugin_base
{
	xsltplugin_xsl_param( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_preserve_space : xbn_xslt_plugin_base
{
	xsltplugin_xsl_preserve_space( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_processing_instruction : xbn_xslt_plugin_base
{
	xsltplugin_xsl_processing_instruction( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_strip_space : xbn_xslt_plugin_base
{
	xsltplugin_xsl_strip_space( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_stylesheet : xbn_xslt_plugin_base
{
	xsltplugin_xsl_stylesheet( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_transform : xbn_xslt_plugin_base
{
	xsltplugin_xsl_transform( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_sort : xbn_xslt_plugin_base
{
	xsltplugin_xsl_sort( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );

	static bool sort( sptr<xbnode> sort_node, xbnode_list &col_liste, xbn_state &state, xbn_xslt *p_xbn_xslt  );
};

struct xsltplugin_xsl_text : xbn_xslt_plugin_base
{
	xsltplugin_xsl_text( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_value_of : xbn_xslt_plugin_base
{
	xsltplugin_xsl_value_of( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_variable : xbn_xslt_plugin_base
{
	xsltplugin_xsl_variable(  );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

struct xsltplugin_xsl_with_param : xbn_xslt_plugin_base
{
	xsltplugin_xsl_with_param( );

	virtual bool testUnit();
	virtual bool operator() (xbn_state &state, xbn_xslt *p_xbn_xslt );
};

#endif // XBN_XSLT_PLUGINS_1_0_H
