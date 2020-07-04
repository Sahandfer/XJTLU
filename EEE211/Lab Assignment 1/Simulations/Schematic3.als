* Schematics Aliases *

.ALIASES
C_C1            C1(1=$N_0001 2=Vin )
Q_Q3            Q3(c=Vout b=Vin e=$N_0002 )
V_VCC           VCC(+=$N_0003 -=0 )
V_-VCC          -VCC(+=0 -=$N_0002 )
R_R1            R1(1=Vout 2=$N_0003 )
I_IBQ           IBQ(+=0 -=Vin )
V_Vs            Vs(+=$N_0001 -=0 )
_    _(Vin=Vin)
_    _(Vout=Vout)
.ENDALIASES

