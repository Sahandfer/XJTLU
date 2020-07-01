	AREA ArmExample,	Code  ; code area declaration and name
	ENTRY	; program entry point
Main	LDR	R1, Value	;load the 32 bit value to be moved
		LDR R2, Res		;load the momory address to store the value
value	STR R1, [R2]	;save the value to the memory address Res
		SWI &0	;system structure (Used so that the following lines for the global variables are not visited)
Value	DCD &C123C123	;DCD enables writing 32 bits to memory (global variable value)
Res		DCD &FFFFFFF0   ;DCD enables writing 32 bits to memory (global variable Res)
		END	;end of the program


;Comments about how the code here differes from what was written in VISUAL Arm Emulator
; 1) Indexes are considerably important here and the code would not compile if correct indentations aren't used,
; 	 whereas the code would be auto-indented upon simulation in the emulator.
; 2) Writing the instructions in all capital letters is required, whereas that was not the case in the emulator.
; 3) Placing the global variable after the END instruction would cause "Bad symbol, not defined or external" error when building, 
;	 whereas the global variables in the emulator could be placed both before and after the END instruction