
		.setpet

Timeout_Sec		= $30
Timeout_Min		= $00

FileZp_SecAdr 		= $b9
FileZp_Device 		= $ba
FileZp_Status 		= $90

Basic_PrintString	= $ab1e

File_SetName		= $ffbd
File_Open		= $f3d5
File_OpenSendName	= $f3fa
File_Close		= $f642

File_Listen		= $ffb1
File_Talk		= $ffb4
File_SecListen		= $ff93
File_SecTalk		= $ff96
File_UnListen 		= $ffae
File_UnTalk		= $ffab

File_ReadByte 		= $ffa5
File_WriteByte		= $ffa8

test_cnt		= $57
stackp_tmp		= $58

test_result		= $fb
test_errcode		= $fc
zp_pnt			= $fd
zp_tmp			= $ff

nmi_vector		= $0318
old_nmi_handler 	= $0334

direntry_buf		= $033c
direntry_name		= direntry_buf + 8
direntry_type		= direntry_buf + $1a

dircache		= $6000
test_avail		= dircache + $100 * $10
test_result_map		= test_avail + $100
test_errcode_map	= test_result_map + $100


#macro print (string) {
		lda #<{string}
		ldy #>{string}
		jsr Basic_PrintString
}

		* = $0801
		.word $080b,1541
		.text $9e,"2061",0,0,0

		.print (string_header)

		lda #0
		tax
init1:
		sta test_avail,x
		sta test_result_map,x
		sta test_errcode_map,x
		inx
		bne init1

		jsr setup_watchdog

		.print (string_scanning)

		lda #dirname_len
		ldx #<(dirname)
		ldy #>(dirname)
		jsr File_SetName

		lda #$60
		sta FileZp_SecAdr
		jsr File_Open

		lda FileZp_Device
		jsr File_Talk
		lda FileZp_SecAdr
		jsr File_SecTalk

next_dir_entry:
		jsr get_direntry
		bit FileZp_Status
		bvc next_dir_entry

		jsr File_UnTalk
		jsr File_Close

		.print (string_ok)

		lda #0
		sta test_cnt
next_test:
		ldx test_cnt
		lda test_avail,x
		beq no_test

		.print (string_running_pre)
		lda test_cnt
		lsr
		lsr
		lsr
		lsr
		ora #>(dircache)
		tay
		lda test_cnt
		asl
		asl
		asl
		asl
		jsr Basic_PrintString
		.print (string_running_post)

		tsx
		stx stackp_tmp
		jsr do_test

		lda test_result
		bmi test_failed
		bne test_ok_data
		;.print (string_ok)
		 jsr dummy
		jmp end_test
test_ok_data:
		jsr hex2str_caps
		stx string_ok_result
		sta string_ok_result+1
		lda test_errcode
		jsr hex2str_caps
		stx string_ok_result+3
		sta string_ok_result+4
		.print (string_ok_data)
		jmp end_test
test_failed:
		cmp #$80
		bne normal_fail
		.print (string_diskerr)
		jmp end_test
normal_fail		
		jsr hex2str_caps
		stx string_failed_result
		sta string_failed_result+1
		lda test_errcode
		jsr hex2str_caps
		stx string_failed_result+3
		sta string_failed_result+4
		.print (string_failed)
end_test:
no_test:
		inc test_cnt
		beq *+5
		jmp next_test
exit:
		jsr clear_watchdog
		.print (string_waitkey)
		jsr $ffe4
		beq *-3
		jsr show_map
		rts

do_test:
		lda test_cnt
		jsr hex2str_small
		stx cmd_start_test+1
		sta cmd_start_test+2

		lda #0
		sta $dd0b
		sta $dd0a
		sta $dd09
		sta $dd08

		ldx #cmd_start_test - cmds
		ldy #cmd_start_test_len
		jsr Send_Command
		jsr Get_Status
		bcs utility_failed

		ldx #cmd_get_result - cmds
		ldy #cmd_get_result_len
		jsr Send_Command

		lda FileZp_Device
		jsr File_Talk
		lda #$6F
		jsr File_SecTalk
		jsr File_ReadByte
		sta test_result
		jsr File_ReadByte
		sta test_errcode
utility_failed:
		ldx test_cnt
		lda test_result
		sta test_result_map,x
		lda test_errcode
		sta test_errcode_map,x
		lda #0
		sta $dd0b

		jmp File_UnTalk

dummy:
		 jsr hex2str_caps
		 stx string_ok_result
		 sta string_ok_result+1
		 lda $dd09
		 jsr hex2str_caps
		 stx string_ok_result+3
		 sta string_ok_result+4
		 .print (string_ok_data)
		 rts

setup_watchdog:
		lda $dd0f
		ora #$80
		sta $dd0f
		ldx #0
		stx $dd0b
		lda #Timeout_Min
		sta $dd0a
		lda #Timeout_Sec
		sta $dd09
		stx $dd08
		lda $dd0f
		and #$7f
		sta $dd0f
		stx $dd0b
		ldx nmi_vector
		ldy nmi_vector+1
		stx old_nmi_handler
		sty old_nmi_handler+1

		ldx #<(nmi_handler)
		ldy #>(nmi_handler)
		stx nmi_vector
		sty nmi_vector+1
		lda #$84
		sta $dd0d
		rts

clear_watchdog:
		lda #$7f
		sta $dd0d
		lda $dd0d
		ldx old_nmi_handler
		ldy old_nmi_handler+1
		stx nmi_vector
		sty nmi_vector+1
		rts

nmi_handler:
.(
		.print (string_timeout)
		ldx test_cnt
		lda #$80
		sta test_result_map,x
		sta test_errcode_map,x
		inx
		lda #0
_1:
		sta test_avail,x
		inx
		bne _1
		ldx stackp_tmp
		txs
		jmp exit
.)


Send_Command:
.(
		lda #0
		sta FileZp_Status
		lda FileZp_Device
		jsr File_Listen
		lda #$6F
		jsr File_SecListen
_1:
		lda cmds,x
		jsr File_WriteByte
		inx
		dey
		bne _1

		jmp File_UnListen
.)


Get_Status:
.(
		lda FileZp_Device
		jsr File_Talk
		lda #$6F
		jsr File_SecTalk
		jsr File_ReadByte
		sta string_diskerr_result
		jsr File_ReadByte
		sta string_diskerr_result+1
		jsr File_UnTalk
		
		lda #'0'
		cmp string_diskerr_result
		bne disk_error 
		cmp string_diskerr_result+1
		bne disk_error
		clc
		rts
disk_error:
		ldx #$80
		stx test_result
		inx
		stx test_errcode
		sec
		rts
.)

get_direntry:
.(
		ldy #0
_1:
		jsr File_ReadByte
		sta direntry_buf,y
		bit FileZp_Status
		bvs gd_error
		iny
		cpy #$20
		bcc _1

		lda direntry_type
		cmp #'u'
		bne gd_nocopy

		lda direntry_name+1
		jsr str2hex
		bcs gd_nocopy
		pha
		ora #>(dircache)
		sta zp_pnt+1
		pla
		asl
		asl
		asl
		asl
		sta zp_tmp

		lda direntry_name+2
		jsr str2hex
		bcs gd_nocopy
		pha
		asl
		asl
		asl
		asl
		sta zp_pnt
		pla
		ora zp_tmp
		tax
		inc test_avail,x

		ldy #15
		lda #0
		sta (zp_pnt),y
		dey
_2:
		lda direntry_name+1,y
		cmp #$22
		bne gd_no_convert
		lda #$20
gd_no_convert:
		sta (zp_pnt),y
		dey
		bpl _2
gd_nocopy:
		clc
		rts
gd_error:
		sec
		rts
.)

str2hex:
		sec
		sbc #$30
		bcc s2h_err
		cmp #$0a
		bcc s2h_ok
		sbc #7
		cmp #$0a
		bcc s2h_err
		cmp #$10
s2h_ok:
		rts
s2h_err:
		sec
		rts

hex2str_small:
		ldx #$07-1
		.byte $2c
hex2str_caps:
		ldx #$27-1
		stx h2s_caps
		pha
		lsr
		lsr
		lsr
		lsr
		jsr hex2str2
		tax
		pla
		and #$0f
hex2str2:
		clc
		adc #$30
		cmp #$3a
		bcc *+4
h2s_caps		= *+1
		adc #7-1
		rts


show_map:
.(
		.print (map_header)

		ldx #0
_1:
		txa
		and #$0f
		bne sm_no_cr
		stx zp_tmp
		txa
		jsr hex2str_caps
		stx map_line_pre+2
		.print (map_line_pre)
		ldx zp_tmp
sm_no_cr:
		lda test_avail,x
		bne sm_test_avail
		lda #$9b
		ldy #'-'
		bne sm_print
sm_test_avail:
		lda test_result_map,x
		bmi sm_test_false
		lda #$99
		ldy #186
		bne sm_print
sm_test_false:
		cmp #$81
		lda #$96
                bcs sm_test_err
                ldy test_errcode_map,x
                pha
                lda map_err_table-$80,y
                tay
                pla
                .byte $2c
sm_test_err:
		ldy #'x'
sm_print:
		jsr $ffd2
		tya
		jsr $ffd2
		lda #' '
		jsr $ffd2
next_elem:
		inx
		bne _1
		.print (map_info_tables)
		rts
.)

dirname:
			.text "$&*=u"
dirname_len	= * - dirname


cmds:
cmd_start_test:
			.text "&XX*"
cmd_start_test_len = * - cmd_start_test

cmd_get_result:
			.text "m-r",$14,$00,2
cmd_get_result_len = * - cmd_get_result


string_header:		.text $93,$05,$0e,"1541 Test Framework V0.3", $0d
			.text "by Ninja / The Dreams in 2008",$0d,$0d,0
string_ok:		.text $99,"OK",$05,$0d,0
string_ok_data:		.text $99,"OK ("
string_ok_result:	.text "00/00"
			.text ")",$05,$0d,0
string_failed:		.text $96,"FAILED! ("
string_failed_result:	.text "00/00"
			.text ")",$05,$0d,0
string_diskerr:		.text $96,"DISK ERR! ("
string_diskerr_result:	.text "00"
			.text ")",$05,$0d,0
string_timeout:		.text $96,"TIMEOUT!!",$05,$0d,0
string_scanning:	.text "Scanning for tests: ",0
string_running_pre:	.text "Test '",0
string_running_post:	.text "': ",0
string_waitkey:		.text "Press a key to continue.",$0d,0

map_header:		.text $93,$0e,"Result matrix:",$0d
			.text "   0 1 2 3 4 5 6 7 8 9 A B C D E F",0
map_line_pre: 		.text $0d,$05,"00 ",0

map_info_tables:
			.text $0d,$05
			; FIXME: do not hardcode addresses!
			.text "Result-Map is at $7100.",$0d
			.text "Errcode-Map is at $7200.",$0d
			.text 0
map_err_table:
			.text "T","D"
			