*version 9.1 454797441
u 102
Q? 3
I? 3
V? 4
? 5
C? 2
R? 2
@libraries
@analysis
.AC 1 3 0
+0 101
+1 10
+2 1.00K
.DC 0 0 0 2 0 2
+ 0 0 IBQ
+ 0 4 0
+ 0 5 100u
+ 0 6 0.1u
+ 1 0 IB
+ 1 4 0
+ 1 5 40u
+ 1 6 4u
@targets
@attributes
@translators
a 0 u 13 0 0 0 hln 100 PCBOARDS=PCB
a 0 u 13 0 0 0 hln 100 PSPICE=PSPICE
a 0 u 13 0 0 0 hln 100 XILINX=XILINX
@setup
unconnectedPins 0
connectViaLabel 0
connectViaLocalLabels 0
NoStim4ExtIFPortsWarnings 1
AutoGenStim4ExtIFPorts 1
@index
pageloc 1 0 3546 
@status
n 0 118:10:10:12:52:19;1541825539 e 
s 0 118:10:10:12:52:22;1541825542 e 
*page 1 0 970 720 iA
@ports
port 65 GND_EARTH 410 470 d
port 66 GND_EARTH 410 410 d
port 74 GND_EARTH 820 430 v
@parts
part 61 c 460 470 h
a 0 u 13 0 15 25 hln 100 VALUE=0.1uF
a 0 sp 0 0 0 10 hlb 100 PART=c
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 ap 9 0 15 0 hln 100 REFDES=C1
a 0 a 0:13 0 0 0 hln 100 PKGREF=C1
part 62 Q2N2222 620 430 h
a 0 sp 11 0 25 40 hln 100 PART=Q2N2222
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=TO-18
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=Q3
a 0 xp 9 0 -5 5 hln 100 REFDES=Q3
part 76 VDC 760 380 h
a 0 sp 0 0 22 37 hln 100 PART=VDC
a 0 x 0:13 0 0 0 hln 100 PKGREF=VCC
a 1 xp 9 0 24 7 hcn 100 REFDES=VCC
a 1 u 13 0 -11 18 hcn 100 DC=9V
part 77 VDC 760 440 h
a 0 sp 0 0 22 37 hln 100 PART=VDC
a 0 x 0:13 0 0 0 hln 100 PKGREF=-VCC
a 1 xp 9 0 24 7 hcn 100 REFDES=-VCC
a 1 u 13 0 -11 18 hcn 100 DC=9V
part 75 r 640 390 v
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R1
a 0 ap 9 0 15 0 hln 100 REFDES=R1
a 0 u 13 0 15 25 hln 100 VALUE=3k
part 63 IDC 450 410 v
a 0 x 0:13 0 0 0 hln 100 PKGREF=IBQ
a 1 xp 9 0 20 10 hcn 100 REFDES=IBQ
a 0 sp 11 0 0 50 hln 100 PART=IDC
a 1 u 13 0 -9 21 hcn 100 DC=16.753uA
part 64 VAC 460 470 d
a 0 x 0:13 0 0 0 hln 100 PKGREF=Vs
a 0 sp 0 0 0 50 hln 100 PART=VAC
a 1 xp 9 0 25 15 hcn 100 REFDES=Vs
a 0 u 13 0 -9 23 hcn 100 ACMAG=0.1V
part 1 titleblk 970 720 h
a 1 s 13 0 350 10 hcn 100 PAGESIZE=A
a 1 s 13 0 180 60 hcn 100 PAGETITLE=
a 1 s 13 0 300 95 hrn 100 PAGENO=1
a 1 s 13 0 340 95 hrn 100 PAGECOUNT=1
part 101 nodeMarker 680 400 h
a 0 s 0 0 0 0 hln 100 PROBEVAR=
a 0 a 0 0 4 22 hlb 100 LABEL=4
@conn
w 52
a 0 sr 0:3 0 645 408 hcn 100 LABEL=Vin
a 0 up 0:33 0 0 0 hln 100 V=
s 620 430 530 430 51
a 0 up 33 0 545 429 hct 100 V=
a 0 sr 3 0 575 428 hcn 100 LABEL=Vin
s 530 410 490 410 53
s 530 470 530 430 57
s 490 470 530 470 55
s 530 430 530 410 73
w 50
a 0 up 0:33 0 0 0 hln 100 V=
s 410 410 450 410 49
a 0 up 33 0 430 409 hct 100 V=
w 48
a 0 up 0:33 0 0 0 hln 100 V=
s 460 470 470 470 47
a 0 up 33 0 465 469 hct 100 V=
w 46
a 0 up 0:33 0 0 0 hln 100 V=
s 420 470 410 470 45
a 0 up 33 0 415 469 hct 100 V=
w 79
a 0 up 0:33 0 0 0 hln 100 V=
s 760 420 760 430 78
s 760 430 820 430 80
a 0 up 33 0 790 429 hct 100 V=
s 760 430 760 440 82
w 85
a 0 up 0:33 0 0 0 hln 100 V=
s 760 380 760 330 84
s 760 330 640 330 86
a 0 up 33 0 700 329 hct 100 V=
s 640 330 640 350 88
w 93
a 0 up 0:33 0 0 0 hln 100 V=
s 760 480 760 490 92
s 760 490 640 490 94
a 0 up 33 0 700 489 hct 100 V=
s 640 490 640 450 96
w 91
a 0 up 0:33 0 0 0 hln 100 V=
a 0 sr 0 0 0 0 hln 100 LABEL=Vout
s 640 400 680 400 98
a 0 sr 3 0 660 398 hcn 100 LABEL=Vout
s 640 390 640 400 90
a 0 up 33 0 642 400 hlt 100 V=
s 640 400 640 410 100
@junction
j 460 470
+ p 61 1
+ p 64 +
j 490 410
+ p 63 -
+ w 52
j 490 470
+ p 61 2
+ w 52
j 620 430
+ p 62 b
+ w 52
j 530 430
+ w 52
+ w 52
j 450 410
+ p 63 +
+ w 50
j 410 410
+ s 66
+ w 50
j 460 470
+ p 61 1
+ w 48
j 460 470
+ p 64 +
+ w 48
j 420 470
+ p 64 -
+ w 46
j 410 470
+ s 65
+ w 46
j 760 420
+ p 76 -
+ w 79
j 820 430
+ s 74
+ w 79
j 760 440
+ p 77 +
+ w 79
j 760 430
+ w 79
+ w 79
j 760 380
+ p 76 +
+ w 85
j 640 350
+ p 75 2
+ w 85
j 760 480
+ p 77 -
+ w 93
j 640 450
+ p 62 e
+ w 93
j 640 410
+ p 62 c
+ w 91
j 640 390
+ p 75 1
+ w 91
j 640 400
+ w 91
+ w 91
j 680 400
+ p 101 pin1
+ w 91
@attributes
a 0 s 0:13 0 0 0 hln 100 PAGETITLE=
a 0 s 0:13 0 0 0 hln 100 PAGENO=1
a 0 s 0:13 0 0 0 hln 100 PAGESIZE=A
a 0 s 0:13 0 0 0 hln 100 PAGECOUNT=1
@graphics
