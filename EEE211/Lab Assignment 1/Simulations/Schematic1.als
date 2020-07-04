* Schematics Aliases *

.ALIASES
C_C1            C1(1=$N_0001 2=Vin )
Q_Q1            Q1(c=$N_0002 b=$N_0002 e=$N_0003 )
R_R3            R3(1=$N_0004 2=$N_0002 )
V_Vcc           Vcc(+=$N_0003 -=0 )
V_-Vcc          -Vcc(+=0 -=$N_0004 )
Q_Q2            Q2(c=$N_0005 b=$N_0002 e=$N_0003 )
Q_Q3            Q3(c=$N_0005 b=Vin e=$N_0004 )
C_C2            C2(1=$N_0006 2=Vout )
R_R             R(1=$N_0004 2=Vout )
Q_Q4            Q4(c=$N_0003 b=$N_0005 e=Vout )
I_IBQ           IBQ(+=0 -=Vin )
V_Vs            Vs(+=$N_0001 -=0 )
V_V1            V1(+=$N_0006 -=0 )
_    _(Vin=Vin)
_    _(Vout=Vout)
.ENDALIASES

