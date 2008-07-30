1,/\.byte 0/ c \
\
		#include "1541-tests.inc" \
\
tmp_zp1		= $2c \
tmp_zp2		= $3b \
tmp_page	= $0700 \
\
		* = $0300 \

# must be before /jsr print/...!
/^error/,$ c \
error: \
		pla \
		pla \
		lda #$ff \
		sta test_result \
		lda pb \
		sta test_errcode \
		cli \
		rts
		
/^waitborder/,/^i\?s\?border/ d

/\.block/ d
/\.bend/ d

/^count/ H
/^opcodes/,/^$/ H
/^sr/ G

/jsr print/,/jmp \$e16f/ c \
		lda #0 \
		sta test_result \
		cli \
		rts

#TMPview bugs on bit!
s/\(bit .*\),x/\1/

#noc is an opcode in dreamass
s/noc/no_c/

s/172/tmp_zp1/
s/173/tmp_zp1+1/
s/174/tmp_zp2/
s/175/tmp_zp2+1/
s/$1000/tmp_page/
s/$\([1-9a-f][0-9a-f]\{3\}\)/label_\1/
s/^\(mem.*=\).*/\1 tmp_page+$ff/
		