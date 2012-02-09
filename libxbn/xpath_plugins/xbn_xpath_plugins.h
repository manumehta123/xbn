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
#ifndef XBN_XPATH_PLUGINS_H
#define XBN_XPATH_PLUGINS_H

#include <string>
#include "xbn_state.h"
#include "xbn_xpath.h"

//---------------------------------------------------
//  base_class_plugins
//---------------------------------------------------
class xbn_xpath_plugin_base
{
public:
	uint_xbn	min_parameter;
	uint_xbn	max_parameter;
	std::string name;

				xbn_xpath_plugin_base();
	virtual		~xbn_xpath_plugin_base();

	bool		testPass(
						std::string pattern,
						uint_xbn result_count=1,
						uint_xbn type=xbnode::xbn_temp,
						std::string result=""
										 );

	virtual bool testUnit()=0;

	//-------------------------------------------------------------------
	// Eigentliche Plugin Funktion - synchron
	//-------------------------------------------------------------------
	virtual bool operator() (xbn_state &state, xbn_xpath *p_xbn_xpath) = 0;


	//-------------------------------------------------------------------
	// Eigentliche Plugin Funktion - asynchron - test
	//-------------------------------------------------------------------
	//virtual sptr<xbnode> getNextResultNode( xbn_state &state, xbn_xpath *p_xbn_xpath ) = 0;
};

//---------------------------------------------------
//  Plugins XPATH xbn nodes
//---------------------------------------------------
struct xpathplugin_xbn_select : xbn_xpath_plugin_base // /
{
	xpathplugin_xbn_select();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_xbn_pipe : xbn_xpath_plugin_base // |
{
	xpathplugin_xbn_pipe();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_xbn_current : xbn_xpath_plugin_base // .
{
	xpathplugin_xbn_current();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_xbn_parent : xbn_xpath_plugin_base // ..
{
	xpathplugin_xbn_parent();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_xbn_all : xbn_xpath_plugin_base // // (descendant-or-self?)
{
	xpathplugin_xbn_all();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_xbn_axis : xbn_xpath_plugin_base // ::
{
	xpathplugin_xbn_axis();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_xbn_condition : xbn_xpath_plugin_base // [
{
	xpathplugin_xbn_condition();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

//---------------------------------------------------------------------------------------------------------------------
//		logical
//---------------------------------------------------------------------------------------------------------------------
struct xpathplugin_xbn_and : xbn_xpath_plugin_base
{
	xpathplugin_xbn_and();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_xbn_or : xbn_xpath_plugin_base
{
	xpathplugin_xbn_or();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

//---------------------------------------------------------------------------------------------------------------------
//		comparesion
//---------------------------------------------------------------------------------------------------------------------
struct xpathplugin_xbn_equal : xbn_xpath_plugin_base
{
	xpathplugin_xbn_equal();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_xbn_not_equal : xbn_xpath_plugin_base
{
	xpathplugin_xbn_not_equal();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_xbn_equal_or_greater : xbn_xpath_plugin_base
{
	xpathplugin_xbn_equal_or_greater();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_xbn_equal_or_less : xbn_xpath_plugin_base
{
	xpathplugin_xbn_equal_or_less();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_xbn_greater : xbn_xpath_plugin_base
{
	xpathplugin_xbn_greater();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_xbn_less : xbn_xpath_plugin_base
{
	xpathplugin_xbn_less();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

//---------------------------------------------------------------------------------------------------------------------
//		mathematical
//---------------------------------------------------------------------------------------------------------------------
struct xpathplugin_xbn_plus : xbn_xpath_plugin_base
{
	xpathplugin_xbn_plus();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_xbn_minus : xbn_xpath_plugin_base
{
	xpathplugin_xbn_minus();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_xbn_mul : xbn_xpath_plugin_base
{
	xpathplugin_xbn_mul();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_xbn_div : xbn_xpath_plugin_base
{
	xpathplugin_xbn_div();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};

struct xpathplugin_xbn_mod : xbn_xpath_plugin_base
{
	xpathplugin_xbn_mod();
	bool            testUnit();
	bool            operator() (xbn_state &state, xbn_xpath *pxpath );
};


#endif // XBN_XPATH_PLUGINS_H
