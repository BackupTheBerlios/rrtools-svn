
	; wait-4sec - wait 4 seconds, watchdog at 5 seconds should not trigger
	;		 (internal test for the framework)
	; Returns: $00/00 (always)

	#include "1541-tests.inc"
	
	* = $0300

              sec
              lda #4*4
l1:
              jsr wait_250ms
              sbc #1
              bne l1
              sta test_result
              sta test_errcode
              rts

wait_250ms:
              ldy #195
l2:
              ldx #0
              dex
              bne * - 1
              dey
              bne l2
              rts
