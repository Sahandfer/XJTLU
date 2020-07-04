*version 9.1 1049490283
u 66
Q? 3
R? 2
V? 4
? 2
@libraries
@analysis
.DC 1 0 0 0 1 1
+ 0 0 V3
+ 0 4 -9
+ 0 5 9
+ 0 6 1
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
pageloc 1 0 2997 
@status
c 118:10:08:16:33:31;1541666011
n 0 118:10:08:16:33:42;1541666022 e 
s 2832 118:10:08:16:39:55;1541666395 e 
*page 1 0 970 720 iA
@ports
port 37 GND_EARTH 740 310 h
port 36 GND_EARTH 740 340 h
port 54 GND_EARTH 550 390 h
@parts
part 4 r 430 420 v
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R1
a 0 ap 9 0 15 0 hln 100 REFDES=R1
part 2 Q2N2907A 450 330 u
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=TO-18
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=Q1
a 0 ap 9 0 5 5 hln 100 REFDES=Q1
a 0 sp 11 0 5 40 hln 100 PART=Q2N2907A
part 6 VDC 690 380 h
a 0 sp 0 0 22 37 hln 100 PART=VDC
a 0 a 0:13 0 0 0 hln 100 PKGREF=V2
a 1 ap 9 0 24 7 hcn 100 REFDES=V2
a 1 u 13 0 -11 18 hcn 100 DC=9V
part 5 VDC 690 230 h
a 0 sp 0 0 22 37 hln 100 PART=VDC
a 0 a 0:13 0 0 0 hln 100 PKGREF=V1
a 1 ap 9 0 24 7 hcn 100 REFDES=V1
a 1 u 13 0 -11 18 hcn 100 DC=9V
part 61 VDC 550 360 h
a 0 sp 0 0 22 37 hln 100 PART=VDC
a 0 a 0:13 0 0 0 hln 100 PKGREF=V3
a 1 ap 9 0 24 22 hcn 100 REFDES=V3
part 3 Q2N2907A 530 330 U
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=TO-18
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=Q2
a 0 sp 11 0 70 35 hln 100 PART=Q2N2907A
a 0 ap 9 0 10 40 hln 100 REFDES=Q2
part 1 titleblk 970 720 h
a 1 s 13 0 350 10 hcn 100 PAGESIZE=A
a 1 s 13 0 180 60 hcn 100 PAGETITLE=
a 1 s 13 0 340 95 hrn 100 PAGECOUNT=1
a 1 s 13 0 300 95 hrn 100 PAGENO=1
part 60 iMarker 550 350 h
a 0 s 0 0 0 0 hln 100 PROBEVAR=
a 0 s 0 0 0 0 hln 100 PROBEVAR=
a 0 a 0 0 6 20 hlb 100 LABEL=1
@conn
w 35
a 0 up 0:33 0 0 0 hln 100 V=
s 430 420 430 430 12
s 430 430 690 430 14
a 0 up 33 0 560 429 hct 100 V=
s 690 430 690 420 16
w 39
a 0 up 0:33 0 0 0 hln 100 V=
s 690 270 690 310 38
s 690 310 740 310 40
a 0 up 33 0 715 309 hct 100 V=
w 43
s 740 340 690 340 42
s 690 340 690 380 44
w 65
a 0 up 0:33 0 0 0 hln 100 V=
s 550 400 550 390 63
a 0 up 33 0 552 395 hlt 100 V=
w 64
a 0 up 0:33 0 0 0 hln 100 V=
s 550 360 550 350 62
a 0 up 33 0 552 355 hlt 100 V=
w 19
a 0 up 0:33 0 0 0 hln 100 V=
s 450 330 490 330 18
s 490 330 530 330 22
s 490 330 490 360 20
s 430 350 430 360 7
s 430 380 430 390 9
s 430 360 430 380 25
s 490 360 430 360 23
a 0 up 33 0 460 359 hct 100 V=
w 27
a 0 up 0:33 0 0 0 hln 100 V=
s 690 230 550 230 26
a 0 up 33 0 620 229 hct 100 V=
s 430 230 430 310 28
s 550 230 430 230 32
s 550 310 550 230 30
@junction
j 450 330
+ p 2 b
+ w 19
j 490 330
+ w 19
+ w 19
j 430 350
+ p 2 c
+ w 19
j 430 360
+ w 19
+ w 19
j 690 230
+ p 5 +
+ w 27
j 430 310
+ p 2 e
+ w 27
j 550 230
+ w 27
+ w 27
j 690 420
+ p 6 -
+ w 35
j 690 270
+ p 5 -
+ w 39
j 740 310
+ s 37
+ w 39
j 740 340
+ s 36
+ w 43
j 690 380
+ p 6 +
+ w 43
j 550 360
+ p 61 +
+ w 64
j 550 350
+ p 60 pin1
+ w 64
j 550 400
+ p 61 -
+ w 65
j 550 390
+ s 54
+ w 65
j 430 420
+ p 4 1
+ w 35
j 430 380
+ p 4 2
+ w 19
j 550 350
+ p 3 c
+ p 60 pin1
j 550 310
+ p 3 e
+ w 27
j 550 350
+ p 3 c
+ w 64
j 530 330
+ p 3 b
+ w 19
@attributes
a 0 s 0:13 0 0 0 hln 100 PAGETITLE=
a 0 s 0:13 0 0 0 hln 100 PAGENO=1
a 0 s 0:13 0 0 0 hln 100 PAGESIZE=A
a 0 s 0:13 0 0 0 hln 100 PAGECOUNT=1
@graphics
