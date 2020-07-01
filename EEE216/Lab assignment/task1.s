	AREA ArmExample,	Code  ; code area declaration and name
	ENTRY	; program entry point
		 MOV r1, #10  	;move 10 (Decimal) to register r1
		 MOV r2, #&10 	;move 10 (Hexadecimal) to register r2
	SWI &0	 ;system instruction (infinite loop)
	END	;end the program