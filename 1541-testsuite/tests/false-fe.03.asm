
	; false-fe.03 - deliver "FAILED (FE/03)" (internal test for the framework)
	; Returns: $FE/03 (always)
	
	#include "1541-tests.inc"
	
	* = $0300

	lda #$fe
	sta test_result
	lda #$03
	sta test_errcode
	rts
