import errno
import socket
import time
import random
import hmac


from time import clock
from collections import OrderedDict
from ecc.Key import Key
from hashlib import sha256,md5
from ecc.elliptic import mul,add,neg
from ecc.ecdsa import sign,verify
from time import clock

DOMAINS = {
    # Bits : (p, order of E(GF(P)), parameter b, base point x, base point y)

    256: (0xffffffff00000001000000000000000000000000ffffffffffffffffffffffffL,
          0xffffffff00000000ffffffffffffffffbce6faada7179e84f3b9cac2fc632551L,
          0x5ac635d8aa3a93e7b3ebbd55769886bc651d06b0cc53b0f63bce3c3e27d2604bL,
          0x6b17d1f2e12c4247f8bce6e563a440f277037d812deb33a0f4a13945d898c296L,
          0x4fe342e2fe1a7f9b8ee7eb4a7c0f9e162bce33576b315ececbb6406837bf51f5L),      
}

if __name__== '__main__':

    global Ra,Tb,p,n,b,x,y,c_p,c_q,c_n,M1,M2,M3,Ka,macb
    
    # initialization
    p, n, b, x, y = DOMAINS[256]
    c_p = 3
    c_n = p
    c_q = p - b
    token=0

    
    try:
        while (token==0):

            # 1. A side: send M1=(helloA,PKax,PKay) to B
            #1.1) generate my (A) keypair PKa SKa
            keypair = Key.generate(256)
            PKax = keypair._pub[1][0]
            PKay = keypair._pub[1][1]
            PKa = (PKax,PKay)
            SKa = keypair._priv[1]
            # 1.2) A->B: M1=(helloA,PKax,PKay)
            
            # 2. B side: 1)receive M1 from A, 2)generate my keypair 3) send M2
            # 2.1) receive M1=(helloA,PKax,PKay) from A            
            PKa=(long(PKax),long(PKay))
            # 2.2) generate my keypair 
            keypair = Key.generate(256)
            PKbx = keypair._pub[1][0]
            PKby = keypair._pub[1][1]
            SKb = keypair._priv[1]            
            # 2.3) B->A: M2=(helloB,PKbx,PKby)
 
            # 3. A side: 1)receive M2, 2)compute ecdsa signature sa 3)send M3
            # 3.1) receive M2 from B, M2=(helloB,PKbx,PKby)
            PKb = (long(PKbx),long(PKby))       
            # 3.2) compute sa
            hstringa='helloA'+str(PKax)+str(PKay)
            md5a=md5()
            md5a.update(hstringa)
            ha=md5a.hexdigest()[8:-8]
            ha=int(ha,16)
            sa=sign(ha,(256,int(SKa)))
            # 3.3) A->B: M3=(sa)

            # 4. B side: 1) receive M3 from A 2) verify ecdsa signature sa 3) compute ecdsa signature sb 4)send M4
            # 4.1) receive M3=sa from A                    
            # 4.2) verify sa
            hstringa="helloA"+str(PKax)+str(PKay)
            md5a=md5()
            md5a.update(hstringa)
            ha=md5a.hexdigest()[8:-8] 
            ha=int(ha,16) 
            if verify(ha,sa,(256,(int(PKax),int(PKay))))==True:
                Kb=mul(c_p,c_q,c_n,PKa,SKb)
                # 4.3) compute sb
                hstringb='helloB'+str(PKbx)+str(PKby)
                md5b=md5()
                md5b.update(hstringb)
                hb=md5b.hexdigest()[8:-8]
                hb=int(hb,16) 
                sb=sign(hb,(256,int(SKb)))           
                # 4.4) send M4
                print 'Server side: signature of client is valid'
                print('the shared secrety is', Kb)
            else:
                print 'Server side: signature of client is invalid, protocol fails'
                
            # 4. A side: 1)receive M4, 2)verify sb
            stringb="helloB"+str(PKbx)+str(PKby)
            md5b=md5()
            md5b.update(stringb)
            hb=md5b.hexdigest()[8:-8]
            hb=int(hb,16)            
            if verify(hb,sb,(256,(int(PKbx),int(PKby))))==True:
                Ka=mul(c_p,c_q,c_n,PKb,SKa) 
                print 'Client side: signature of sever is valid'
                print ('the shared secret is', Ka)
            else:
                print 'Client side signature of server is invalid, protocol fails'              
            token=1
            
    except KeyboardInterrupt:
        s.close()
        print("KeyboardInterrupt")
    #sys.exit(0)

    







