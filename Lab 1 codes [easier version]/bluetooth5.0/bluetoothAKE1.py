import errno
import socket
import time
import random
import hmac


from time import clock
from collections import OrderedDict
from ecc.Key import Key
from hashlib import sha256
from ecc.elliptic import mul,add,neg
from time import clock

DOMAINS = {
    # Bits : (p, order of E(GF(P)), parameter b, base point x, base point y)

    256: (0xffffffff00000001000000000000000000000000ffffffffffffffffffffffffL,
          0xffffffff00000000ffffffffffffffffbce6faada7179e84f3b9cac2fc632551L,
          0x5ac635d8aa3a93e7b3ebbd55769886bc651d06b0cc53b0f63bce3c3e27d2604bL,
          0x6b17d1f2e12c4247f8bce6e563a440f277037d812deb33a0f4a13945d898c296L,
          0x4fe342e2fe1a7f9b8ee7eb4a7c0f9e162bce33576b315ececbb6406837bf51f5L)      
}

if __name__== '__main__':

    global Ra,Tb,p,n,b,x,y,c_p,c_q,c_n,M1,M2,M3,Ka,macb


    # initialization
    p, n, b, x, y = DOMAINS[256]
    c_p = 3
    c_n = p
    c_q = p - b
    idA='00000001'
    idB='00000002'
    token=0

    
    
    try:
        while (token==0):
            print('connection up')
            print ('connected')
            # 1. A side: send M1=(PKax,PKay) to B
            #1.1) generate my (A) keypair PKa SKa
            keypair = Key.generate(256)
            PKax = keypair._pub[1][0]
            PKay = keypair._pub[1][1]
            PKa = (PKax,PKay)
            SKa = keypair._priv[1]
            M1=str(PKax)+','+str(PKay)

            # 2.B side 1)receive M1=(PKax,PKay) from A, 2) send M2=(PKbx,PKby) to A
            PKax=M1.split(',')[0]
            PKay=M1.split(',')[1]
            PKa=(long(PKax),long(PKay))
            keypair = Key.generate(256)
            PKbx = keypair._pub[1][0]
            PKby = keypair._pub[1][1]
            SKb = keypair._priv[1]
            M2=str(PKbx)+','+str(PKby)

            # 3. A side: 1) receive M2=(PKbx,PKby) 2)generate Ra, 3) compute hasha 4) send M3=(A,Ra,hasha)
            PKbx=M2.split(',')[0]
            PKby = M2.split(',')[1]
            PKb = (long(PKbx),long(PKby))
            Ra=random.randint(000000,999999)
            hash_stringa=str(PKax)+str(PKay)
            newhash=hmac.new(str(Ra),'',sha256)
            newhash.update(hash_stringa)
            hasha=newhash.hexdigest() 
            M3=idA+','+str(Ra)+','+hasha

            # 4. B side: 1)receive M3=(A,Ra,hasha), 2)generate Rb, 3) compute hashb, 4) send M4=(B,Rb,hashb)
            Ra=M3.split(',')[1]
            hasha=M3.split(',')[2]
            Rb=random.randint(000000,999999)
            hash_stringb=str(PKbx)+str(PKby)
            newhash=hmac.new(str(Rb),'',sha256)
            newhash.update(hash_stringb)
            hashb=newhash.hexdigest() 
            M4=idB+','+str(Rb)+','+hashb  

            # 5. A side: 1) receive M4=(B,Rb,hashb), 2)verify hashb, 3) generate Na, 4) send M5=Na
            Rb=M4.split(',')[1]
            hashb=M4.split(',')[2]
            hash_stringb=str(PKbx)+str(PKby)
            newhash=hmac.new(str(Rb),'',sha256)
            newhash.update(hash_stringb)
            hashb_check=newhash.hexdigest() 
            if hashb_check==hashb:
                Na=random.randint(000000,999999)
                M5=str(Na)
            else:
                print 'A side: hashb is invalid, protocol fails.'

            # 6. B side: 1)receive M5=Na, 2)verify hasha, 3)send M6=Nb
            Na=long(M5)
            hash_stringa=str(PKax)+str(PKay)
            newhash=hmac.new(str(Ra),'',sha256)
            newhash.update(hash_stringa)
            hasha_check=newhash.hexdigest() 
            if hasha_check==hasha:
                Nb=random.randint(000000,999999)
                M6=str(Nb)
            else:
                print 'B side: hasha is invalid, protocol fails.'
                
                
            # 7. A side: 1)receive M6=Nb, 2)compute Ka, 3)compute maca, 4)send M7=maca
            Nb=long(M6)
            Ka=mul(c_p,c_q,c_n,PKb,SKa)
            hmac_stringa=str(Na)+str(Nb)+str(Rb)+idA+idB
            newhash=hmac.new(str(Ka[0]),'',sha256)
            newhash.update(hmac_stringa)
            maca=newhash.hexdigest()
            M7=maca             

            # 8. B side: 1)receive M7=maca, 2)compute Kb, 3)verify maca, 4)compute macb, 5)send M8=macb
            maca=M7
            Kb=mul(c_p,c_q,c_n,PKa,SKb)
            hmac_stringa=str(Na)+str(Nb)+str(Rb)+idA+idB
            newhash=hmac.new(str(Kb[0]),'',sha256)
            newhash.update(hmac_stringa)
            maca_check=newhash.hexdigest()
            if maca_check==maca:
                hmac_stringb=str(Nb)+str(Na)+str(Ra)+idB+idA
                newhash=hmac.new(str(Kb[0]),'',sha256)
                newhash.update(hmac_stringb)
                macb=newhash.hexdigest()                                         
                M8=macb
                print 'B side: maca is valid'
                print('the shared secrety is', Kb)
            else:
                print 'B side: maca is invalid, protocol fails.'
                    
            # 9. 1)receive M8=macb, 2)verify macb
            macb=M8
            hmac_stringb=str(Nb)+str(Na)+str(Ra)+idB+idA
            newhash=hmac.new(str(Ka[0]),'',sha256)
            newhash.update(hmac_stringb)
            macb_check=newhash.hexdigest() 
            if macb_check==macb:
                print 'A side: macb is valid'
                print('the shared secrety is', Ka)
            else:
                print 'macb is invalid, protocol fails.'
             


            token=1
            
    except KeyboardInterrupt:
        s.close()
        print("KeyboardInterrupt")
    #sys.exit(0)

    







