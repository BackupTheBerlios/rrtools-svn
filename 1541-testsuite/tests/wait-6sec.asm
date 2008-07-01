
	; wait-6sec - wait 6 seconds, watchdog at 5 seconds should trigger
	;		 (internal test for the framework)
	; Returns: $00/00 (always)

	#include "1541-tests.inc"
	
	* = $0300

              sec
              lda #6*4
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
