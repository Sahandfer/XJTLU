*version 9.1 913429608
u 425
Q? 8
I? 3
V? 10
? 14
R? 5
C? 3
@libraries
@analysis
.AC 1 3 0
+0 101
+1 10
+2 1000K
.DC 0 0 0 2 0 2
+ 0 0 IBQ
+ 0 4 0
+ 0 5 100u
+ 0 6 0.01u
+ 1 0 Ib
+ 1 4 0
+ 1 5 40u
+ 1 6 4u
.TRAN 0 0 0 0
+0 0ns
+1 1000ns
.LOADBIAS 0 
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
pageloc 1 0 6247 
@status
n 0 118:10:08:18:33:35;1541673215 e 
s 2832 118:10:08:18:41:55;1541673715 e 
*page 1 0 970 720 iA
@ports
port 123 GND_EARTH 390 440 d
port 122 GND_EARTH 390 380 d
port 263 GND_EARTH 900 300 h
port 264 GND_EARTH 900 330 h
port 406 GND_EARTH 790 440 h
@parts
part 138 c 440 440 h
a 0 u 13 0 15 25 hln 100 VALUE=0.1uF
a 0 sp 0 0 0 10 hlb 100 PART=c
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=C1
a 0 ap 9 0 15 0 hln 100 REFDES=C1
part 258 Q2N2907A 360 320 u
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=TO-18
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 sp 11 0 5 40 hln 100 PART=Q2N2907A
a 0 x 0:13 0 0 0 hln 100 PKGREF=Q1
a 0 xp 9 0 5 5 hln 100 REFDES=Q1
part 256 r 340 410 v
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=R3
a 0 ap 9 0 15 0 hln 100 REFDES=R3
a 0 u 13 0 15 30 hln 100 VALUE=20k
part 260 VDC 850 220 h
a 0 sp 0 0 22 37 hln 100 PART=VDC
a 1 u 13 0 -11 18 hcn 100 DC=9V
a 0 x 0:13 0 0 0 hln 100 PKGREF=Vcc
a 1 xp 9 0 24 7 hcn 100 REFDES=Vcc
part 259 VDC 850 370 h
a 0 sp 0 0 22 37 hln 100 PART=VDC
a 1 u 13 0 -11 18 hcn 100 DC=9V
a 0 x 0:13 0 0 0 hln 100 PKGREF=-Vcc
a 1 xp 9 0 24 7 hcn 100 REFDES=-Vcc
part 89 Q2N2222 600 400 h
a 0 sp 11 0 25 40 hln 100 PART=Q2N2222
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=TO-18
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=Q3
a 0 xp 9 0 -5 5 hln 100 REFDES=Q3
part 404 c 790 400 v
a 0 sp 0 0 0 10 hlb 100 PART=c
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=CK05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 a 0:13 0 0 0 hln 100 PKGREF=C2
a 0 ap 9 0 15 0 hln 100 REFDES=C2
a 0 u 13 0 15 40 hln 100 VALUE=0.1uF
part 407 r 720 430 v
a 0 sp 0 0 0 10 hlb 100 PART=r
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=RC05
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=R
a 0 xp 9 0 15 0 hln 100 REFDES=R
a 0 u 13 0 15 30 hln 100 VALUE=5k
part 400 Q2N2222 700 350 h
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=TO-18
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 x 0:13 0 0 0 hln 100 PKGREF=Q4
a 0 xp 9 0 5 5 hln 100 REFDES=Q4
a 0 sp 11 0 -30 35 hln 100 PART=Q2N2222
part 121 IDC 430 380 v
a 0 x 0:13 0 0 0 hln 100 PKGREF=IBQ
a 1 xp 9 0 20 10 hcn 100 REFDES=IBQ
a 0 sp 11 0 0 50 hln 100 PART=IDC
a 1 u 13 0 -9 21 hcn 100 DC=5.5579uA
part 137 VAC 440 440 d
a 0 x 0:13 0 0 0 hln 100 PKGREF=Vs
a 0 sp 0 0 0 50 hln 100 PART=VAC
a 1 xp 9 0 25 15 hcn 100 REFDES=Vs
a 0 u 13 0 -9 23 hcn 100 ACMAG=0V
part 405 VAC 790 400 h
a 0 sp 0 0 0 50 hln 100 PART=VAC
a 0 x 0:13 0 0 0 hln 100 PKGREF=V1
a 1 xp 9 0 20 10 hcn 100 REFDES=V1
a 0 u 13 0 -9 23 hcn 100 ACMAG=0.01V
part 262 Q2N2907A 600 320 U
a 0 s 0:13 0 0 0 hln 100 PKGTYPE=TO-18
a 0 s 0:13 0 0 0 hln 100 GATE=
a 0 sp 11 0 70 35 hln 100 PART=Q2N2907A
a 0 x 0:13 0 0 0 hln 100 PKGREF=Q2
a 0 xp 9 0 10 40 hln 100 REFDES=Q2
part 1 titleblk 970 720 h
a 1 s 13 0 350 10 hcn 100 PAGESIZE=A
a 1 s 13 0 180 60 hcn 100 PAGETITLE=
a 1 s 13 0 340 95 hrn 100 PAGECOUNT=1
a 1 s 13 0 300 95 hrn 100 PAGENO=1
part 422 nodeMarker 720 370 h
a 0 s 0 0 0 0 hln 100 PROBEVAR=
a 0 a 0 0 4 22 hlb 100 LABEL=12
part 424 iMarker 620 340 h
a 0 s 0 0 0 0 hln 100 PROBEVAR=
a 0 a 0 0 6 20 hlb 100 LABEL=13
@conn
w 361
a 0 up 0:33 0 0 0 hln 100 V=
s 360 320 400 320 233
s 400 320 600 320 364
a 0 up 33 0 500 319 hct 100 V=
s 400 320 400 350 235
s 340 340 340 350 340
s 340 350 340 370 367
s 400 350 340 350 244
a 0 up 33 0 370 349 hct 100 V=
s 340 370 340 380 257
w 142
a 0 up 0:33 0 0 0 hln 100 V=
s 400 440 390 440 189
a 0 up 33 0 395 439 hct 100 V=
w 200
a 0 up 0:33 0 0 0 hln 100 V=
s 440 440 450 440 201
a 0 up 33 0 445 439 hct 100 V=
w 375
a 0 up 0:33 0 0 0 hln 100 V=
s 390 380 430 380 139
a 0 up 33 0 410 379 hct 100 V=
w 224
a 0 up 0:33 0 0 0 hln 100 V=
s 850 330 850 370 225
s 900 330 850 330 223
a 0 up 33 0 875 329 hct 100 V=
w 220
a 0 up 0:33 0 0 0 hln 100 V=
s 850 300 900 300 221
a 0 up 33 0 875 299 hct 100 V=
s 850 260 850 300 219
w 214
a 0 up 0:33 0 0 0 hln 100 V=
s 620 460 620 420 105
s 620 460 340 460 385
a 0 up 33 0 480 459 hct 100 V=
s 340 460 340 410 387
s 850 460 720 460 383
s 850 410 850 460 381
s 720 460 620 460 414
s 720 430 720 460 412
w 390
a 0 up 0:33 0 0 0 hln 100 V=
s 340 300 340 220 389
s 620 300 620 220 253
s 340 220 620 220 391
s 850 220 720 220 251
a 0 up 33 0 735 219 hct 100 V=
s 720 220 620 220 421
s 720 330 720 220 419
w 411
a 0 up 0:33 0 0 0 hln 100 V=
a 0 sr 0 0 0 0 hln 100 LABEL=Vout
s 720 370 720 390 410
a 0 sr 3 0 722 380 hln 100 LABEL=Vout
s 720 370 790 370 417
a 0 up 33 0 755 369 hct 100 V=
w 130
a 0 up 0:33 0 0 0 hln 100 V=
a 0 sr 0 0 0 0 hln 100 LABEL=Vin
s 600 400 510 400 212
a 0 up 33 0 525 399 hct 100 V=
a 0 sr 3 0 555 398 hcn 100 LABEL=Vin
s 510 380 470 380 119
s 470 440 510 440 129
s 510 440 510 400 332
s 510 400 510 380 380
w 230
a 0 up 0:33 0 0 0 hln 100 V=
s 620 350 700 350 401
s 620 340 620 350 304
a 0 up 33 0 622 340 hlt 100 V=
s 620 350 620 380 403
@junction
j 600 320
+ p 262 b
+ w 361
j 360 320
+ p 258 b
+ w 361
j 400 320
+ w 361
+ w 361
j 340 340
+ p 258 c
+ w 361
j 340 370
+ p 256 2
+ w 361
j 340 350
+ w 361
+ w 361
j 470 380
+ p 121 -
+ w 130
j 470 440
+ p 138 2
+ w 130
j 600 400
+ p 89 b
+ w 130
j 510 400
+ w 130
+ w 130
j 390 440
+ s 123
+ w 142
j 440 440
+ p 138 1
+ w 200
j 430 380
+ p 121 +
+ w 375
j 390 380
+ s 122
+ w 375
j 620 420
+ p 89 e
+ w 214
j 340 410
+ p 256 1
+ w 214
j 340 300
+ p 258 e
+ w 390
j 620 300
+ p 262 e
+ w 390
j 620 460
+ w 214
+ w 214
j 850 220
+ p 260 +
+ w 390
j 620 220
+ w 390
+ w 390
j 850 410
+ p 259 -
+ w 214
j 850 370
+ p 259 +
+ w 224
j 900 330
+ s 264
+ w 224
j 900 300
+ s 263
+ w 220
j 850 260
+ p 260 -
+ w 220
j 790 400
+ p 405 +
+ p 404 1
j 790 440
+ s 406
+ p 405 -
j 620 340
+ p 262 c
+ w 230
j 620 380
+ p 89 c
+ w 230
j 620 350
+ w 230
+ w 230
j 720 390
+ p 407 2
+ w 411
j 720 430
+ p 407 1
+ w 214
j 720 460
+ w 214
+ w 214
j 790 370
+ p 404 2
+ w 411
j 720 220
+ w 390
+ w 390
j 440 440
+ p 138 1
+ p 137 +
j 400 440
+ p 137 -
+ w 142
j 440 440
+ p 137 +
+ w 200
j 720 370
+ p 422 pin1
+ w 411
j 700 350
+ p 400 b
+ w 230
j 720 370
+ p 400 e
+ w 411
j 720 330
+ p 400 c
+ w 390
j 720 370
+ p 422 pin1
+ p 400 e
j 620 340
+ p 424 pin1
+ p 262 c
j 620 340
+ p 424 pin1
+ w 230
@attributes
a 0 s 0:13 0 0 0 hln 100 PAGETITLE=
a 0 s 0:13 0 0 0 hln 100 PAGENO=1
a 0 s 0:13 0 0 0 hln 100 PAGESIZE=A
a 0 s 0:13 0 0 0 hln 100 PAGECOUNT=1
@graphics
