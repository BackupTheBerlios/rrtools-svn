
	; true-23.42 - deliver "OK (23/42)" (internal test for the framework)
	; Returns: $23/42 (always)
	
	#include "1541-tests.inc"
	
	* = $0300

	lda #$23
	sta test_result
	lda #$42
	sta test_errcode
	rts
