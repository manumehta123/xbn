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
#include "xbn_xpath_plugins.h"
#include "xbn_helper.h"
#include "xbn_document.h"

xpathplugin_xbn_plus::xpathplugin_xbn_plus()
{
	min_parameter = 2;
	max_parameter = 2;
	name          = "xbn:+";
}
bool            xpathplugin_xbn_plus::testUnit()
{
	return	testPass("0 + 0"	, 1, xbnode::xbn_temp, "0")
		&	testPass("1 + 0"	, 1, xbnode::xbn_temp, "1")
		&	testPass("0 + 1"	, 1, xbnode::xbn_temp, "1")
		&	testPass("1 + 1"	, 1, xbnode::xbn_temp, "2");
}
bool           xpathplugin_xbn_plus::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
		return false;

	xbn_state arg1(state);
	if( !pxpath->process( arg1, *(state.pCurrent_token) ) )
		return false;

	xbn_state arg2(state);
	if( !pxpath->process( arg2, *(state.pCurrent_token) ) )
		return false;

	if( arg1.ResultNodeList.size()!=arg2.ResultNodeList.size() &&
		(arg1.ResultNodeList.size()>1&&
		 arg2.ResultNodeList.size()>1) )
	{
		pxpath->raiseError( name+"() resultsizes arg1,arg2 does not match",&state, __FILE__, __LINE__ );
		return false;
	}

	for( xbnode_list::iterator pc_arg1=arg1.ResultNodeList.begin(),pe_arg1=arg1.ResultNodeList.end(),
							   pc_arg2=arg2.ResultNodeList.begin(),pe_arg2=arg2.ResultNodeList.end();
			pc_arg1!=pe_arg1 && pc_arg2!=pe_arg2;
			++pc_arg1,++pc_arg2 )
	{
		if( pc_arg1==pe_arg1 ) pc_arg1=arg1.ResultNodeList.begin();
		if( pc_arg2==pe_arg2 ) pc_arg2=arg2.ResultNodeList.begin();

		if( (*pc_arg1)->isNumeric() && (*pc_arg2)->isNumeric() )
		{
			std::string wert = zahlToString( (*pc_arg1)->getNumeric()+(*pc_arg2)->getNumeric()  );
			state.ResultNodeList.push_back( state.pStack->createTempNode( wert ) );
		}
	}
	return true;
}

//----------------------------------------------------------------------------------------------------------------------
xpathplugin_xbn_minus::xpathplugin_xbn_minus()
{
	min_parameter = 2;
	max_parameter = 2;
	name          = "xbn:-";
}
bool            xpathplugin_xbn_minus::testUnit()
{
	return	testPass("0 - 0"	, 1, xbnode::xbn_temp, "0")
		|	testPass("1 - 0"	, 1, xbnode::xbn_temp, "1")
		|	testPass("0 - 1"	, 1, xbnode::xbn_temp, "-1")
		|	testPass("1 - 1"	, 1, xbnode::xbn_temp, "0");
}
bool            xpathplugin_xbn_minus::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
		return false;

	xbn_state arg1(state);
	if( !pxpath->process( arg1, *(state.pCurrent_token) ) )
		return false;

	xbn_state arg2(state);
	if( !pxpath->process( arg2, *(state.pCurrent_token) ) )
		return false;

	if( arg1.ResultNodeList.size()!=arg2.ResultNodeList.size() &&
		(arg1.ResultNodeList.size()>1&&
		 arg2.ResultNodeList.size()>1) )
	{
		pxpath->raiseError( name+"() resultsizes arg1,arg2 does not match",&state, __FILE__, __LINE__ );
		return false;
	}

	for( xbnode_list::iterator pc_arg1=arg1.ResultNodeList.begin(),pe_arg1=arg1.ResultNodeList.end(),
							   pc_arg2=arg2.ResultNodeList.begin(),pe_arg2=arg2.ResultNodeList.end();
			pc_arg1!=pe_arg1 && pc_arg2!=pe_arg2;
			++pc_arg1,++pc_arg2 )
	{
		if( pc_arg1==pe_arg1 ) pc_arg1=arg1.ResultNodeList.begin();
		if( pc_arg2==pe_arg2 ) pc_arg2=arg2.ResultNodeList.begin();

		if( (*pc_arg1)->isNumeric() && (*pc_arg2)->isNumeric() )
		{
			std::string wert = zahlToString( (*pc_arg1)->getNumeric()-(*pc_arg2)->getNumeric()  );
			state.ResultNodeList.push_back( state.pStack->createTempNode( wert ) );
		}
	}
	return true;
}

//----------------------------------------------------------------------------------------------------------------------
xpathplugin_xbn_mul::xpathplugin_xbn_mul()
{
	min_parameter = 2;
	max_parameter = 2;
	name          = "xbn:*";
}
bool            xpathplugin_xbn_mul::testUnit()
{
	return	testPass("0 * 0"	, 1, xbnode::xbn_temp, "0")
		|	testPass("1 * 0"	, 1, xbnode::xbn_temp, "0")
		|	testPass("0 * 1"	, 1, xbnode::xbn_temp, "0")
		|	testPass("1 * 1"	, 1, xbnode::xbn_temp, "1")
		|	testPass("2 * 1"	, 1, xbnode::xbn_temp, "2")
		|	testPass("2 * 2"	, 1, xbnode::xbn_temp, "4")
		|	testPass("-1 * 1"	, 1, xbnode::xbn_temp, "-1")
		|	testPass("-1 * -1"	, 1, xbnode::xbn_temp, "1")
		|	testPass("(1 + 2) * 2"	, 1, xbnode::xbn_temp, "6")
		|	testPass("1 + 2 * 2"	, 1, xbnode::xbn_temp, "5")
		|	testPass("1 * 2 + 2"	, 1, xbnode::xbn_temp, "4");
}
bool            xpathplugin_xbn_mul::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
		return false;

	xbn_state arg1(state);
	if( !pxpath->process( arg1, *(state.pCurrent_token) ) )
		return false;

	xbn_state arg2(state);
	if( !pxpath->process( arg2, *(state.pCurrent_token) ) )
		return false;

	if( arg1.ResultNodeList.size()!=arg2.ResultNodeList.size() &&
		(arg1.ResultNodeList.size()>1&&
		 arg2.ResultNodeList.size()>1) )
	{
		pxpath->raiseError( name+"() resultsizes arg1,arg2 does not match",&state, __FILE__, __LINE__ );
		return false;
	}

	for( xbnode_list::iterator pc_arg1=arg1.ResultNodeList.begin(),pe_arg1=arg1.ResultNodeList.end(),
							   pc_arg2=arg2.ResultNodeList.begin(),pe_arg2=arg2.ResultNodeList.end();
			pc_arg1!=pe_arg1 && pc_arg2!=pe_arg2;
			++pc_arg1,++pc_arg2 )
	{
		if( pc_arg1==pe_arg1 ) pc_arg1=arg1.ResultNodeList.begin();
		if( pc_arg2==pe_arg2 ) pc_arg2=arg2.ResultNodeList.begin();

		if( (*pc_arg1)->isNumeric() && (*pc_arg2)->isNumeric() )
		{
			std::string wert = zahlToString( (*pc_arg1)->getNumeric() * (*pc_arg2)->getNumeric()  );
			state.ResultNodeList.push_back( state.pStack->createTempNode( wert ) );
		}
	}
	return true;
}

//----------------------------------------------------------------------------------------------------------------------
xpathplugin_xbn_div::xpathplugin_xbn_div()
{
	min_parameter = 2;
	max_parameter = 2;
	name          = "xbn:div";
}
bool            xpathplugin_xbn_div::testUnit()
{
	return	testPass("0 div 0"	, 1, xbnode::xbn_temp, "#inf")
		|	testPass("1 div 0"	, 1, xbnode::xbn_temp, "#inf")
		|	testPass("0 div 1"	, 1, xbnode::xbn_temp, "0")
		|	testPass("1 div 1"	, 1, xbnode::xbn_temp, "1")
		|	testPass("2 div 1"	, 1, xbnode::xbn_temp, "2")
		|	testPass("2 div 2"	, 1, xbnode::xbn_temp, "1")
		|	testPass("-1 div 1"	, 1, xbnode::xbn_temp, "-1")
		|	testPass("-1 div -1"	, 1, xbnode::xbn_temp, "1");
}
bool            xpathplugin_xbn_div::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
		return false;

	xbn_state arg1(state);
	if( !pxpath->process( arg1, *(state.pCurrent_token) ) )
		return false;

	xbn_state arg2(state);
	if( !pxpath->process( arg2, *(state.pCurrent_token) ) )
		return false;

	if( arg1.ResultNodeList.size()!=arg2.ResultNodeList.size() &&
		(arg1.ResultNodeList.size()>1&&
		 arg2.ResultNodeList.size()>1) )
	{
		pxpath->raiseError( name+"() resultsizes arg1,arg2 does not match",&state, __FILE__, __LINE__ );
		return false;
	}

	for( xbnode_list::iterator pc_arg1=arg1.ResultNodeList.begin(),pe_arg1=arg1.ResultNodeList.end(),
							   pc_arg2=arg2.ResultNodeList.begin(),pe_arg2=arg2.ResultNodeList.end();
			pc_arg1!=pe_arg1 && pc_arg2!=pe_arg2;
			++pc_arg1,++pc_arg2 )
	{
		if( pc_arg1==pe_arg1 ) pc_arg1=arg1.ResultNodeList.begin();
		if( pc_arg2==pe_arg2 ) pc_arg2=arg2.ResultNodeList.begin();

		if( (*pc_arg1)->isNumeric() && (*pc_arg2)->isNumeric() )
		{
			double divisor = (*pc_arg2)->getNumeric();
			std::string wert = divisor!=0 ? zahlToString( (*pc_arg1)->getNumeric()/divisor ) : "#inf";
			state.ResultNodeList.push_back( state.pStack->createTempNode( wert ) );
		}
	}
	return true;
}

//----------------------------------------------------------------------------------------------------------------------
xpathplugin_xbn_mod::xpathplugin_xbn_mod()
{
	min_parameter = 2;
	max_parameter = 2;
	name          = "xbn:mod";
}
bool            xpathplugin_xbn_mod::testUnit()
{
	return	testPass("0 mod 0"	, 1, xbnode::xbn_temp, "#err")
		|	testPass("1 mod 0"	, 1, xbnode::xbn_temp, "#err")
		|	testPass("0 mod 1"	, 1, xbnode::xbn_temp, "0")
		|	testPass("1 mod 1"	, 1, xbnode::xbn_temp, "0")
		|	testPass("2 mod 1"	, 1, xbnode::xbn_temp, "0")
		|	testPass("2 mod 2"	, 1, xbnode::xbn_temp, "0")
		|	testPass("6 mod 5"	, 1, xbnode::xbn_temp, "1")
		|	testPass("12 mod 10"	, 1, xbnode::xbn_temp, "2");
}
bool            xpathplugin_xbn_mod::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
		return false;

	xbn_state arg1(state);
	if( !pxpath->process( arg1, *(state.pCurrent_token) ) )
		return false;

	xbn_state arg2(state);
	if( !pxpath->process( arg2, *(state.pCurrent_token) ) )
		return false;

	if( arg1.ResultNodeList.size()!=arg2.ResultNodeList.size() &&
		(arg1.ResultNodeList.size()>1&&
		 arg2.ResultNodeList.size()>1) )
	{
		pxpath->raiseError( name+"() resultsizes arg1,arg2 does not match",&state, __FILE__, __LINE__ );
		return false;
	}

	for( xbnode_list::iterator pc_arg1=arg1.ResultNodeList.begin(),pe_arg1=arg1.ResultNodeList.end(),
							   pc_arg2=arg2.ResultNodeList.begin(),pe_arg2=arg2.ResultNodeList.end();
			pc_arg1!=pe_arg1 && pc_arg2!=pe_arg2;
			++pc_arg1,++pc_arg2 )
	{
		if( pc_arg1==pe_arg1 ) pc_arg1=arg1.ResultNodeList.begin();
		if( pc_arg2==pe_arg2 ) pc_arg2=arg2.ResultNodeList.begin();

		if( (*pc_arg1)->isNumeric() && (*pc_arg2)->isNumeric() )
		{
			int modulant = (int)( (*pc_arg2)->getNumeric() );
			std::string wert = modulant ? zahlToString( (int)(*pc_arg1)->getNumeric()% modulant ) : "#err";
			state.ResultNodeList.push_back( state.pStack->createTempNode( wert ) );
		}

	}
	return true;
}

