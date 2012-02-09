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
#include "xpath_plugins/xbn_xpath_plugins_1_0.h"
#include "xbn_helper.h"
#include "xbstring.h"
#include "xbn_document.h"

//----------------------------------------------------------------------------------------------------------------------
xpathplugin_normalize_space::xpathplugin_normalize_space()
{
	min_parameter = 1;
	max_parameter = 1;
	name          = "normalize-space";
}
bool            xpathplugin_normalize_space::testUnit()
{
	return testPass("normalize-space('Hallo')",1,xbnode::xbn_temp,"Hallo")
			|testPass("normalize-space(' Hallo')",1,xbnode::xbn_temp,"Hallo")
			|testPass("normalize-space('Hallo ')",1,xbnode::xbn_temp,"Hallo");
}
bool            xpathplugin_normalize_space::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
		return false;

	xbn_state arg1(state);
	if( !pxpath->process( arg1, *(state.pCurrent_token) ) )
	{
		pxpath->raiseError( this->name + "() could not process arg1", &state,__FILE__,__LINE__ );
		return false;
	}

	for( xbnode_list::iterator pc_arg1=arg1.ResultNodeList.begin(),pe_arg1=arg1.ResultNodeList.end();
			pc_arg1!=pe_arg1;
			++pc_arg1 )
	{
		std::string wert = std_string_trim( (*pc_arg1)->getText() );
		state.ResultNodeList.push_back(  state.pStack->createTempNode( wert ) );
	}

	return true;
}



//----------------------------------------------------------------------------------------------------------------------
xpathplugin_string::xpathplugin_string()
{
	min_parameter = 1;
	max_parameter = 1;
	name          = "string";
}
bool            xpathplugin_string::testUnit()
{
	return testPass( "string(12)", 1,		xbnode::xbn_temp, "12" )
		|	testPass( "string(true())", 1,	xbnode::xbn_temp, "true" );
}
bool            xpathplugin_string::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
		return false;

	xbn_state arg1(state);
	if( !pxpath->process( arg1, *(state.pCurrent_token) ) )
	{
		pxpath->raiseError( this->name + "() could not process arg1", &state,__FILE__,__LINE__ );
		return false;
	}

	for( xbnode_list::iterator pc_arg1=arg1.ResultNodeList.begin(),pe_arg1=arg1.ResultNodeList.end();
			pc_arg1!=pe_arg1;
			++pc_arg1 )
	{
		state.ResultNodeList.push_back(  state.pStack->createTempNode( (*pc_arg1)->getText() ) );
	}

	return true;
}

//----------------------------------------------------------------------------------------------------------------------
xpathplugin_starts_with::xpathplugin_starts_with()
{
	min_parameter = 2;
	max_parameter = 2;
	name          = "starts-with";
}
bool            xpathplugin_starts_with::testUnit()
{
	return testPass( "starts-with('Hallo','Ha')", 1,		xbnode::xbn_temp, "true" )
			|testPass( "starts-with('Hallo','lo')", 1,		xbnode::xbn_temp, "false" );
}
bool            xpathplugin_starts_with::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
		return false;

	xbn_state arg1(state);
	if( !pxpath->process( arg1, *(state.pCurrent_token) ) )
	{
		pxpath->raiseError( this->name + "() could not process arg1", &state,__FILE__,__LINE__ );
		return false;
	}
	xbn_state arg2(state);
	if( !pxpath->process( arg2, *(state.pCurrent_token) ) )
	{
		pxpath->raiseError( this->name + "() could not process arg2", &state,__FILE__,__LINE__ );
		return false;
	}

	if( arg1.ResultNodeList.size()!=arg2.ResultNodeList.size() )
	{
		pxpath->raiseError( this->name + "() argsize does not match arg1 arg2", &state,__FILE__,__LINE__ );
		return false;
	}

	for( xbnode_list::iterator pc_arg1=arg1.ResultNodeList.begin(),pe_arg1=arg1.ResultNodeList.end(),
								pc_arg2=arg2.ResultNodeList.begin();
			pc_arg1!=pe_arg1;
			++pc_arg1, ++pc_arg2 )
	{
		std::string wert1 = (*pc_arg1)->getText();
		std::string wert2 = (*pc_arg2)->getText();

		state.ResultNodeList.push_back(
				state.pStack->createTempNode(
						wert1.find( wert2 )==0?"true":"false"
					)
				);
	}
	return true;
}

//----------------------------------------------------------------------------------------------------------------------
xpathplugin_substring_before::xpathplugin_substring_before()
{
	min_parameter = 2;
	max_parameter = 2;
	name          = "substring-before";
}
bool            xpathplugin_substring_before::testUnit()
{
	return testPass("substring-before('test=wert','=wert')",1, xbnode::xbn_temp,"test")
			|testPass("substring-before('test=wert','wert')",1, xbnode::xbn_temp,"test=");
}
bool            xpathplugin_substring_before::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
		return false;

	xbn_state arg1(state);
	if( !pxpath->process( arg1, *(state.pCurrent_token) ) )
	{
		pxpath->raiseError( this->name + "() could not process arg1", &state,__FILE__,__LINE__ );
		return false;
	}
	xbn_state arg2(state);
	if( !pxpath->process( arg2, *(state.pCurrent_token) ) )
	{
		pxpath->raiseError( this->name + "() could not process arg2", &state,__FILE__,__LINE__ );
		return false;
	}

	if( arg1.ResultNodeList.size()!=arg2.ResultNodeList.size() )
	{
		pxpath->raiseError( this->name + "() argsize does not match arg1 arg2", &state,__FILE__,__LINE__ );
		return false;
	}

	for( xbnode_list::iterator pc_arg1=arg1.ResultNodeList.begin(),pe_arg1=arg1.ResultNodeList.end(),
								pc_arg2=arg2.ResultNodeList.begin();
			pc_arg1!=pe_arg1;
			++pc_arg1, ++pc_arg2 )
	{
		std::string wert1 = (*pc_arg1)->getText();
		std::string wert2 = (*pc_arg2)->getText();
		size_t p = wert1.find( wert2 );
		if( p!=std::string::npos )
		{
			wert1 = wert1.substr(0,p);
		}
		else
		{
			wert1 = "";
		}

		state.ResultNodeList.push_back(
				state.pStack->createTempNode(
						wert1
					)
				);
	}
	return true;
}

//----------------------------------------------------------------------------------------------------------------------
xpathplugin_substring_after::xpathplugin_substring_after()
{
	min_parameter = 2;
	max_parameter = 2;
	name          = "substring-after";
}
bool            xpathplugin_substring_after::testUnit()
{
	return testPass("substring-after('test=wert','test=')",1, xbnode::xbn_temp,"wert")
			&testPass("substring-after('test=wert','test')",1, xbnode::xbn_temp,"=wert");

}
bool            xpathplugin_substring_after::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
		return false;

	xbn_state arg1(state);
	if( !pxpath->process( arg1, *(state.pCurrent_token) ) )
	{
		pxpath->raiseError( this->name + "() could not process arg1", &state,__FILE__,__LINE__ );
		return false;
	}
	xbn_state arg2(state);
	if( !pxpath->process( arg2, *(state.pCurrent_token) ) )
	{
		pxpath->raiseError( this->name + "() could not process arg2", &state,__FILE__,__LINE__ );
		return false;
	}

	if( arg1.ResultNodeList.size()!=arg2.ResultNodeList.size() )
	{
		pxpath->raiseError( this->name + "() argsize does not match arg1 arg2", &state,__FILE__,__LINE__ );
		return false;
	}

	for( xbnode_list::iterator pc_arg1=arg1.ResultNodeList.begin(),pe_arg1=arg1.ResultNodeList.end(),
								pc_arg2=arg2.ResultNodeList.begin();
			pc_arg1!=pe_arg1;
			++pc_arg1, ++pc_arg2 )
	{
		std::string wert1 = (*pc_arg1)->getText();
		std::string wert2 = (*pc_arg2)->getText();
		size_t p = wert1.find( wert2 );
		if( p!=std::string::npos )
		{
			wert1 = wert1.substr(p+wert2.length());
		}
		else
		{
			wert1 = "";
		}

		state.ResultNodeList.push_back(
				state.pStack->createTempNode(
						wert1
					)
				);
	}
	return true;
}

//----------------------------------------------------------------------------------------------------------------------
xpathplugin_substring::xpathplugin_substring()
{
	min_parameter = 2;
	max_parameter = 3;
	name          = "substring";
}
bool            xpathplugin_substring::testUnit()
{
	return	testPass( "substring('Hallo',1,4)", 1, xbnode::xbn_temp, "Hall" )
		&	testPass( "substring('Hallo',1,5)", 1, xbnode::xbn_temp, "Hallo" )
		&	testPass( "substring('Hallo',2,2)", 1, xbnode::xbn_temp, "al" )
		&	testPass( "substring('Hallo',3,3)", 1, xbnode::xbn_temp, "llo" )
		&	testPass( "substring('Hallo',4,4)", 1, xbnode::xbn_temp, "lo" );
}
bool            xpathplugin_substring::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
		return false;

	xbn_state arg1(state);
	if( !pxpath->process( arg1, *(state.pCurrent_token) ) )
		return false;

	xbn_state arg2(state);
	if( !pxpath->process( arg2, *(state.pCurrent_token) ) )
		return false;

	bool use_arg3=false;
	xbn_state arg3(state);
	if( pxpath->peekFunctionList( *(state.pCurrent_token) ) )
	{
		if( !pxpath->process( arg3, *(state.pCurrent_token) ) )
			return false;

		use_arg3 = true;
	}

	if( arg1.ResultNodeList.size()!=arg2.ResultNodeList.size() ||
		(use_arg3 &&  arg1.ResultNodeList.size()!=arg3.ResultNodeList.size())  )
	{
		pxpath->raiseError( "resultsizes arg1,arg2,arg3 does not match",&state, __FILE__, __LINE__ );
		return false;
	}

	for( xbnode_list::iterator pc_arg1=arg1.ResultNodeList.begin(),pe_arg1=arg1.ResultNodeList.end(),
							   pc_arg2=arg2.ResultNodeList.begin(),
							   pc_arg3=arg3.ResultNodeList.begin();
			pc_arg1!=pe_arg1;
			++pc_arg1, ++pc_arg2, ++pc_arg3 )
	{
		std::string text = (*pc_arg1)->getText();
		int			p    = (int)(*pc_arg2)->getNumeric()-1;
		int			q    = use_arg3 ? (int)(*pc_arg3)->getNumeric() : text.length()-p ;

		if( p<0 )
		{
			pxpath->raiseError( name+"() arg1 <1" );
			return false;
		}
		if( q<0 )
		{
			pxpath->raiseError( name+"() arg2 <0" );
			return false;
		}
		if( p>(int)text.length() )
		{
			p=0;
			q=0;
		}
		if( p+q>(int)text.length())
		{
			q = text.length() - p;
		}

		state.ResultNodeList.push_back( state.pStack->createTempNode( text.substr(p,q) ) );
	}
	return true;
}

//----------------------------------------------------------------------------------------------------------------------
xpathplugin_string_length::xpathplugin_string_length()
{
	min_parameter = 1;
	max_parameter = 1;
	name          = "string-length";
}
bool            xpathplugin_string_length::testUnit()
{
	return	testPass( "string-length('Hallo')", 1, xbnode::xbn_temp, "5" )
		&	testPass( "string-length('')", 1, xbnode::xbn_temp, "0" );
}
bool            xpathplugin_string_length::operator() (xbn_state &state, xbn_xpath *pxpath )
{
	if( !state.pCurrentNode )
		return false;

	xbn_state arg1(state);
	if( !pxpath->process( arg1, *(state.pCurrent_token) ) )
	{
		pxpath->raiseError( this->name + "() could not process arg1", &state,__FILE__,__LINE__ );
		return false;
	}

	for( xbnode_list::iterator pc_arg1=arg1.ResultNodeList.begin(),pe_arg1=arg1.ResultNodeList.end();
			pc_arg1!=pe_arg1;
			++pc_arg1 )
	{
		state.ResultNodeList.push_back( state.pStack->createTempNode( zahlToString( (*pc_arg1)->getText().size() ) ) );
	}

	return true;
}
