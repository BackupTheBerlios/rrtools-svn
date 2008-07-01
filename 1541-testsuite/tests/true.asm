
	; true - deliver "OK" (internal test for the framework)
	; Returns: $00/00 (always)
	
	#include "1541-tests.inc"
	
	* = $0300

	lda #0
	sta test_result
	sta test_errcode
	rts
