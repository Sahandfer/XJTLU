	AREA ArmExample,	Code  ; code area declaration and name
	ENTRY	; program entry point
Main	LDR	R1, Initial		;load the initial value into R1
		LDR	R2, Increment	;load the increment value into R2
value	ADD R1, R1, R2	;Increment the current value in R1 by the increment (+1)
		SWI &0	;system structure (infinite loop)
Initial	DCD &00000000	;initial value to be stored in R1
Increment	DCD &00000001	;increment (Which is required to be 1)

		END	;end of the program
