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


;--------------------------------------
; SilverSurfer Registers
;--------------------------------------

Surf_RXD = $de08	;R    Receive Latch
Surf_TXD = $de08	;  W  Transmit Latch
Surf_BDL = $de08	;R/W  Baud Divisor Low
Surf_BDH = $de09	;R/W  Baud Divisor High
Surf_IER = $de09	;R/W  Interrupt Enable Register
Surf_FCR = $de0a	;  W  FIFO Control Register
Surf_IIR = $de0a	;R    Interrupt Identification Register
Surf_LCR = $de0b	;R/W  Line Control Register
Surf_MCR = $de0c	;R/W  Modem Control Register
Surf_LSR = $de0d	;R    Line Status Register
Surf_MSR = $de0e	;R    Modem Status Register
Surf_SCR = $de0f	;R/W  Scratch Register

;--------------------------------------
