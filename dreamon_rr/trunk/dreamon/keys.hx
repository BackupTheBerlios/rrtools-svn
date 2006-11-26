/***************************************************************************
 *   Copyright (C) 2000 - 2006 by Christoph Thelen                         *
 *   DocBacardi@the-dreams.de                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


/*-----------------------------------*/

Key_MSi = 0             ;Switch Akku Size
Key_XSi = 1             ;Switch XReg Size

Key_Rep = 2             ;Switch Option - Follow Rep/Sep
Key_VHu = 3             ;Switch Option - Verbose Hunt

 ;Key_130 - Key_139 = Switch intern $01
Key_130=$04      : Key_131=Key_130+1:Key_132=Key_131+1:Key_133=Key_132+1
Key_134=Key_133+1: Key_135=Key_134+1:Key_136=Key_135+1:Key_137=Key_136+1
Key_138=Key_137+1: Key_139=Key_138+1

Key_F1 =Key_139+1 : Key_F2 =Key_F1 +1: Key_F3 =Key_F2 +1: Key_F4 =Key_F3 +1
Key_F5 =Key_F4 +1 : Key_F6 =Key_F5 +1: Key_F7 =Key_F6 +1: Key_F8 =Key_F7 +1
Key_F9 =Key_F8 +1 : Key_F10=Key_F9 +1: Key_F11=Key_F10+1: Key_F12=Key_F11+1
Key_F13=Key_F12+1 : Key_F14=Key_F13+1: Key_F15=Key_F14+1: Key_F16=Key_F15+1

Key_Map= Key_F16+1	;Memory Map Option (aka Debug)

Key_BSp = $c0           ;Backspace
Key_Del = $c1           ;Delete
Key_Ins = $c2           ;Insert

Key_SRe = $c4           ;Shift Return
Key_URe = $c5		;Return Up

Key_CUp = $c6           ;Cursor Up
Key_CDo = $c7           ;Cursor Down
Key_CLe = $c8           ;Cursor Left
Key_CRi = $c9           ;Cursor Right

Key_Hme = $ca           ;Home
Key_Clr = $cb           ;Clear Home

Key_Stp = $cc           ;Stop
Key_Run = $cd           ;Run/Stop

Key_ROn = $ce           ;Revers On
Key_ROf = $cf           ;Revers Off

Key_CSh = $d0           ;C= and Shift

Key_SUp = $d1		;Top of Screen
Key_SDo = $d2		;Bottom of Screen
Key_SLe = $d3		;Beginning of Line
Key_SRi = $d4		;End of Line

Key_Vid = $d5		;Switch Video Mode
Key_VSU = $d6		;Video SubMode Up
Key_VSD = $d7		;Video SubMode Down

Key_ILi	= $d8		;Insert Line
Key_KLi	= $d9		;Kill Line
Key_ELi	= $da		;Erase Line

Key_PMa	= $db		;Program Bank Mapping
Key_DMa = $dc		;Data Bank Mapping
Key_NMa = $dd		;No Mapping

Key_No  = $df		;No key pressed

Key_C0 =$e0       :Key_C1 =Key_C0 +1:Key_C2 =Key_C1 +1:Key_C3 =Key_C2 +1
Key_C4 =Key_C3 +1 :Key_C5 =Key_C4 +1:Key_C6 =Key_C5 +1:Key_C7 =Key_C6 +1
Key_C8 =Key_C7 +1 :Key_C9 =Key_C8 +1:Key_C10=Key_C9 +1:Key_C11=Key_C10+1
Key_C12=Key_C11+1 :Key_C13=Key_C12+1:Key_C14=Key_C13+1:Key_C15=Key_C14+1


Key_CR = $fe		;Return
Spi_Idn = $ff

/*-----------------------------------*/

