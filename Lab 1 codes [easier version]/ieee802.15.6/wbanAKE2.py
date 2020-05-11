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
    server_ip = "192.168.0.111"
    server_port = 6633

    # initialization
    p, n, b, x, y = DOMAINS[256]
    c_p = 3
    c_n = p
    c_q = p - b
    idA='00000001'
    idB='00000002'
    PW=(1234,5678)
    token=0
    

    
    try:
        while (token==0):
            # 1. A side: send M1=(B,A,Na,PKapwx,PKapwy) to B
            #1.1) generate my (A) keypair PKa SKa
            keypair = Key.generate(256)
            PKax = keypair._pub[1][0]
            PKay = keypair._pub[1][1]
            PKa = (PKax,PKay)
            SKa = keypair._priv[1]
            # 1.2) compute PKapw
            negPW=neg(PW,c_n)
            PKapw=add(c_p,c_q,c_n,PKa,negPW)
            #1.2) generate my (A) nonce Na
            Na=random.randint(000000,999999)
            # 1.3) A->B: M1=(B,A,Na,PKax,PKay)
            M1=idA+','+idB+','+str(Na)+','+str(PKapw[0])+','+str(PKapw[1])


            # 2. B side: 1)receive M1 from A, 2)generate my keypair 3)generate Nb 4) send M2
            # 2.1) receive M1=(B,A,Na,PKax,PKay) from B
            Na=M1.split(',')[2]
            PKapwx=M1.split(',')[3]
            PKapwy=M1.split(',')[4]
            PKapw=(long(PKapwx),long(PKapwy))
            # 2.2) generate my keypair
            keypair = Key.generate(256)
            PKbx = keypair._pub[1][0]
            PKby = keypair._pub[1][1]
            SKb = keypair._priv[1]
            # 2.3) genearate my nonce Nb
            Nb=random.randint(000000,999999)
            # 2.4) B->A: M2=(A,B,Nb,PKbx,PKby)
            M2=idA+','+idB+','+str(Nb)+','+str(PKbx)+','+str(PKby)

 
            # 3. A side: 1)receive M2, 2)compute Ka, 3)compute maca,macb_check 4)send M3
            # 3.1) receive M2 from B, M2=(A,B,Nb,PKbx,PKby)
            Nb = M2.split(',')[2]
            PKbx = M2.split(',')[3]
            PKby = M2.split(',')[4]
            PKb = (long(PKbx),long(PKby))
            # 3.2) compute Ka
            Ka=mul(c_p,c_q,c_n,PKb,SKa)          
            # 3.3) compute maca,macb_check
            hmac_stringa=idB+idA+Nb+str(Na)
            newhash=hmac.new(str(Ka[0]),'',sha256)
            newhash.update(hmac_stringa)
            maca=newhash.hexdigest()
            hmac_stringb=idA+idB+str(Na)+Nb
            newhash=hmac.new(str(Ka[0]),'',sha256)
            newhash.update(hmac_stringb) 
            macb_check=newhash.hexdigest()
            # 3.4) A->B: M3=(maca)
            M3=maca

            # 4. B side: 1) receive M3 from A 2) compute Kb 3) compute maca_check, macb 4)verfiy maca 5)send M4
            # 4.1) receive M3=maca from A
            maca=M3
            # 4.2) compute Kb
            PKa=add(c_p,c_q,c_n,PKapw,PW)
            Kb=mul(c_p,c_q,c_n,PKa,SKb)
            # 4.3) compute maca_check, macb
            hmac_stringa=idB+idA+str(Nb)+Na
            newhash=hmac.new(str(Kb[0]),'',sha256)
            newhash.update(hmac_stringa)
            maca_check=newhash.hexdigest()
            hmac_stringb=idA+idB+Na+str(Nb)
            newhash=hmac.new(str(Kb[0]),'',sha256)
            newhash.update(hmac_stringb) 
            macb=newhash.hexdigest()        
            # 4.4) verify maca           
            if maca_check==maca:
                # 4.5) send M4
                M4=macb
                print 'B side: maca is valid'
                print('the shared secrety is', Kb)
            else:
                print 'B side: maca is invalid, protocol fails'

            # 5. A side: 1)receive M4, 2)verify macb
            macb=M4
            if str(macb_check)==macb:
                print 'A side: macb is valid'
                print ('the shared secret is', Ka)
            else:
                print 'A side: macb is invalid, protocol fails'
            token=1
            
    except KeyboardInterrupt:
        s.close()
        print("KeyboardInterrupt")
    #sys.exit(0)

    







