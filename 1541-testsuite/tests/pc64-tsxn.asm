; pc64-tsxn.asm: specialized opcode test - Public Domain
; converted for the 1541-Testsuite by Wolfram Sang (Ninja/The Dreams)
; original PC64-Testsuite by Wolfgang Lorenz

		#include "1541-tests.inc"

		* = $0300

		.start_test
		ldx #$40
		stx $1c0e

		lda #%00011011
		sta db
		lda #%11000110
		sta ab
		lda #%10110001
		sta xb
		lda #%01101100
		sta yb
		lda #0
		sta pb
		tsx
		stx sb

		stx saves+1
		ldx #0
stack		= $0100
s0		lda stack,x
tmp_page	= $0500
		sta tmp_page,x
		inx
		bne s0

		lda #0
		sta sb

next		lda db
		sta dr
		sta da

		lda ab
		sta ar

		lda yb
		sta yr

		lda pb
		ora #%00110000
		and #%01111101
		tax
		lda sb
		cmp #0
		bne nozero
		txa
		ora #%00000010
		tax
		lda sb
nozero		asl
		bcc noneg
		txa
		ora #%10000000
		tax
noneg		stx pr

		lda sb
		sta sr
		sta xr

		ldx sb
		txs
		lda pb
		pha
		lda ab
		ldx xb
		ldy yb
		plp

cmd		tsx

		php
		cld
		sta aa
		stx xa
		sty ya
		pla
		sta pa
		tsx
		stx sa
		jsr check

		inc sb
jmpnext		bne next
		inc pb
		bne jmpnext

saves		ldx #0
		txs
		ldx #0
s1		lda tmp_page,x
		sta stack,x
		inx
		bne s1

		lda #0
test_exit
		sta test_result
		ldx #$c0
		stx $1c0e
		cli
		.end_test

db		.byte 0
ab		.byte 0
xb		.byte 0
yb		.byte 0
pb		.byte 0
sb		.byte 0
da		.byte 0
aa		.byte 0
xa		.byte 0
ya		.byte 0
pa		.byte 0
sa		.byte 0
dr		.byte 0
ar		.byte 0
xr		.byte 0
yr		.byte 0
pr		.byte 0
sr		.byte 0


check
		lda da
		cmp dr
		bne error
		lda aa
		cmp ar
		bne error
		lda xa
		cmp xr
		bne error
		lda ya
		cmp yr
		bne error
		lda pa
		cmp pr
		bne error
		lda sa
		cmp sr
		bne error
		rts

error
		pla
		pla
error_nopla
		lda pb
		sta test_errcode
errcode		lda #$ff
		sta test_exit - 1
		jmp saves
