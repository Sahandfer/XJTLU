import random
import hmac

from ecc.Key import Key
from hashlib import sha256,md5
from ecc.elliptic import mul

DOMAINS = {
    # Bits : (p, order of E(GF(P)), parameter b, base point x, base point y)

    256: (0xffffffff00000001000000000000000000000000ffffffffffffffffffffffff,
          0xffffffff00000000ffffffffffffffffbce6faada7179e84f3b9cac2fc632551,
          0x5ac635d8aa3a93e7b3ebbd55769886bc651d06b0cc53b0f63bce3c3e27d2604b,
          0x6b17d1f2e12c4247f8bce6e563a440f277037d812deb33a0f4a13945d898c296,
          0x4fe342e2fe1a7f9b8ee7eb4a7c0f9e162bce33576b315ececbb6406837bf51f5)
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
            # 1. A send M1=(PKax,PKay) to B
            keypair = Key.generate(256)
            PKax = keypair._pub[1][0]
            PKay = keypair._pub[1][1]
            PKa = (PKax,PKay)
            SKa = keypair._priv[1]
            M1=str(PKax)+','+str(PKay)

            # 2. B receive M1 from A,generate my keypair, generate Nb, compute Cb, send M2
            PKax=M1.split(',')[0]
            PKay=M1.split(',')[1]
            PKa=(int(PKax),int(PKay))
            keypair = Key.generate(256)
            PKbx = keypair._pub[1][0]
            PKby = keypair._pub[1][1]
            SKb = keypair._priv[1]
            Kb=mul(c_p,c_q,c_n,PKa,SKb)
            Nb=random.randint(000000,999999)
            stringcb=str(PKbx)+PKax+str(Nb)
            newmd5=md5()
            newmd5.update(stringcb.encode())
            cb=newmd5.hexdigest()
            M2=str(PKbx)+','+str(PKby)+','+cb

 
            # 3. A receive M2, send Na
            PKbx = M2.split(',')[0]
            PKby = M2.split(',')[1]
            cb = M2.split(',')[2]
            PKb = (int(PKbx),int(PKby))
            Ka=mul(c_p,c_q,c_n,PKb,SKa)  
            Na=random.randint(000000,999999)
            M3=str(Na)

            # 4. B receive M3=Na, send M4=Nb, compute and show digb
            Na=int(M3)
            M4=str(Nb)
            hmac_string=str(PKax)+str(PKbx)+str(Na)+str(Nb)
            newhash=hmac.new(str(Kb[0]).encode(),''.encode(),sha256)
            newhash.update(hmac_string.encode())
            digb=newhash.hexdigest()[0:4]      
            print ('B side: digest is',digb)
            print('the shared secret is', Kb)  

            # 5. A receive M4, verify cb, compute and show diga
            Nb=int(M4)
            stringcb=PKbx+str(PKax)+str(Nb)
            newmd5=md5()
            newmd5.update(stringcb.encode())
            cb_check=newmd5.hexdigest()
            if cb_check==cb:
                hmac_string=str(PKax)+PKbx+str(Na)+str(Nb)
                newhash=hmac.new(str(Ka[0]).encode(),''.encode(),sha256)
                newhash.update(hmac_string.encode())
                diga=newhash.hexdigest()[0:4]        
                print ('A side: digest is',diga)
                print('the shared secret is', Ka)
            else:
                print('A side: cb is invalid, protocol fails')
            token=1
            
    except KeyboardInterrupt:
        print("KeyboardInterrupt")
    #sys.exit(0)

    







