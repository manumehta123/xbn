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

xpathplugin_format_number::xpathplugin_format_number()
{
	min_parameter = 2;
	max_parameter = 2;
	name          = "format-number";
/*
[Zahl]	Der umzuwandelnde Wert. Es kann sich auch um den Inhalt eines Elements oder den Wert einer Variablen handeln. Dabei wird der Wert intern zunächst als Zahl umgewandelt, und zwar so, als würde die Funktion  number() angewendet.
[Formatregel]	Eine Darstellungs-Syntax für die Formatierung der umgewandelten Zahl. Die Syntax der Formatregel orientiert sich dabei an dem Schema, das in Java 1.1 für die decimal_format-Klasse implementiert ist. Allerdings gibt es keine zwingende Korrelation zwischen der XPath-Syntax und der Java-Implementierung. Folgende Zeichen sind üblich:
0 = eine Ziffer
# = eine Ziffer, 0 wird jedoch nicht angezeigt
. = Platzhalter für Dezimalpunkt-Trennzeichen
, = Platzhalter für ein Gruppierungs-Trennzeichen, z.B. für Tausender
; = zum Trennen von mehreren Formaten
- = negatives Vorzeichen als Voreinstellung
% = Wert mit 100 multiplizieren und als Prozentwert anzeigen
? = Wert mit 1000 multiplizieren und als Promillewert anzeigen
¤ = Währungssymbol, wird durch das voreingestellte Währungssymbol ersetzt (noch nicht in Java 1.1!).
' = zum Maskieren von format-bedeutenden Zeichen wie 0, #, . usw.
[Name]	(optional) Name eines Formats, das mit  xsl:decimal-format definiert wird.
Liefert eine Zeichenkette mit der formatierten Zahl zurück.
  */
}
bool            xpathplugin_format_number::testUnit()
{
	return testPass("format-number(1)",1,xbnode::xbn_temp,"1")
			&testPass("format-number(1,'##0.0')",1,xbnode::xbn_temp,"1.0")
			&testPass("format-number(123.45,'##0.0')",1,xbnode::xbn_temp,"123.45")
			&testPass("format-number(1,'##0.00')",1,xbnode::xbn_temp,"1.00");
}
bool            xpathplugin_format_number::operator() (xbn_state &state, xbn_xpath *pxpath )
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

		// ToDo: wert1 nach wert2 formatieren...

		state.ResultNodeList.push_back(
				state.pStack->createTempNode(
						wert1
					)
				);
	}
	return true;
}

//----------------------------------------------------------------------------------------------------------------------
xpathplugin_number::xpathplugin_number()
{
	min_parameter = 1;
	max_parameter = 1;
	name          = "number";
}
bool            xpathplugin_number::testUnit()
{
	return testPass( "number('12')", 1, xbnode::xbn_temp, "12" )
		&	testPass( "number(false())", 1, xbnode::xbn_temp, "0" )
		&	testPass( "number(true())", 1, xbnode::xbn_temp, "1" );
}
bool            xpathplugin_number::operator() (xbn_state &state, xbn_xpath *pxpath )
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
		state.ResultNodeList.push_back(  state.pStack->createTempNode( zahlToString( (*pc_arg1)->getNumeric() ) ) );
	}

	return true;
}
