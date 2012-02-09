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
#ifndef XBN_XPATH_PLUGINS_1_0_H
#define XBN_XPATH_PLUGINS_1_0_H

#include "xbn_xpath_plugins.h"

//---------------------------------------------------
//  Plugins XPATH 1.0
//---------------------------------------------------
struct xpathplugin_boolean : xbn_xpath_plugin_base
{
	xpathplugin_boolean();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_ceiling : xbn_xpath_plugin_base
{
	xpathplugin_ceiling();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_floor : xbn_xpath_plugin_base
{
	xpathplugin_floor();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_round : xbn_xpath_plugin_base
{
	xpathplugin_round();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_concat : xbn_xpath_plugin_base
{
	xpathplugin_concat();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_contains : xbn_xpath_plugin_base
{
	xpathplugin_contains();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_count : xbn_xpath_plugin_base
{
	xpathplugin_count();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_current : xbn_xpath_plugin_base
{
	xpathplugin_current();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_document : xbn_xpath_plugin_base
{
	xpathplugin_document();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_element_available : xbn_xpath_plugin_base
{
	xpathplugin_element_available();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_true : xbn_xpath_plugin_base
{
	xpathplugin_true();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_false : xbn_xpath_plugin_base
{
	xpathplugin_false();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_format_number : xbn_xpath_plugin_base
{
	xpathplugin_format_number();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_function_available : xbn_xpath_plugin_base
{
	xpathplugin_function_available();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_generate_id : xbn_xpath_plugin_base
{
	xpathplugin_generate_id();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_id : xbn_xpath_plugin_base
{
	xpathplugin_id();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_not : xbn_xpath_plugin_base
{
	xpathplugin_not();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_last : xbn_xpath_plugin_base
{
	xpathplugin_last();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_local_name : xbn_xpath_plugin_base
{
	xpathplugin_local_name();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_name : xbn_xpath_plugin_base
{
	xpathplugin_name();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_text : xbn_xpath_plugin_base
{
	xpathplugin_text();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_comment : xbn_xpath_plugin_base
{
	xpathplugin_comment();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_position : xbn_xpath_plugin_base
{
	xpathplugin_position();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_node : xbn_xpath_plugin_base
{
	xpathplugin_node();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_normalize_space : xbn_xpath_plugin_base
{
	xpathplugin_normalize_space();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_number : xbn_xpath_plugin_base
{
	xpathplugin_number();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_string : xbn_xpath_plugin_base
{
	xpathplugin_string();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_starts_with : xbn_xpath_plugin_base
{
	xpathplugin_starts_with();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_substring_before : xbn_xpath_plugin_base
{
	xpathplugin_substring_before();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_substring_after : xbn_xpath_plugin_base
{
	xpathplugin_substring_after();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_substring : xbn_xpath_plugin_base
{
	xpathplugin_substring();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_string_length : xbn_xpath_plugin_base
{
	xpathplugin_string_length();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_sum : xbn_xpath_plugin_base
{
	xpathplugin_sum();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_translate : xbn_xpath_plugin_base
{
	xpathplugin_translate();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};


#endif // XBN_XPATH_PLUGINS_1_0_H
