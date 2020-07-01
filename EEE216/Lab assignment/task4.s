	AREA ArmExample,	Code  ; code area declaration and name
	ENTRY	; program entry point
Main	
        MOV	R1, #Value1	;load the first value into R1
		MOV	R2, #Value2	;load the second value into R2
		CMP R1, R2;
		BNE	Store
		SWI &0
Store	
        LDR	R3, Value
		LDR R4, fault
		STR R3, [R4]
Value1	DCW &1234	;the first value
		align
Value2	DCW &1234	;the second value
Value	DCW 0xFF
fault	DCD &FFFFFFF0

		END	;end of the program

; If we don't use align, we would get the following error:
; "Added 2 bytes of padding at address 0x26"