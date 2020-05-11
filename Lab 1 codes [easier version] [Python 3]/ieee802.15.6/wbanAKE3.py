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
            # 1. A side: send M1=(B,A,Na,PKax,PKay) to B
            # 1.1) generate my (A) keypair PKa SKa
            keypair = Key.generate(256)
            PKax = keypair._pub[1][0]
            PKay = keypair._pub[1][1]
            PKa = (PKax,PKay)
            SKa = keypair._priv[1]
            # 1.2) generate my (A) nonce Na
            Na=random.randint(000000,999999)
            # 1.3) compute ca
            stringca=str(Na)+idA+idB+str(PKax)+str(PKay)
            newmd5=md5()
            newmd5.update(stringca.encode())
            ca=newmd5.hexdigest()
            # 1.4) A->B: M1=(B,A,ca,PKax,PKay)
            M1=idA+','+idB+','+ca+','+str(PKax)+','+str(PKay)

            # 2. B receive M1 from A, generate my keypair, generate Nb, compute Kb and macb, send M2
            # 2.1) receive M1=(B,A,ca,PKax,PKay) from B
            ca=M1.split(',')[2]
            PKax=M1.split(',')[3]
            PKay=M1.split(',')[4]
            PKa=(int(PKax),int(PKay))
            # 2.2) generate my keypair 
            keypair = Key.generate(256)
            PKbx = keypair._pub[1][0]
            PKby = keypair._pub[1][1]
            SKb = keypair._priv[1]
            # 2.3) genearate my nonce Nb
            Nb=random.randint(000000,999999)
            # 2.4) compute Kb and macb
            Kb=mul(c_p,c_q,c_n,PKa,SKb)
            hmac_stringb=idA+idB+ca+str(Nb)
            newhash=hmac.new(str(Kb[0]).encode(),''.encode(),sha256)
            newhash.update(hmac_stringb.encode())
            macb=newhash.hexdigest()  
            # 2.4) send M2
            M2=idA+','+idB+','+str(Nb)+','+str(PKbx)+','+str(PKby)+','+macb

 
            # 3. A side: 1)receive M2, 2)compute Ka, 3)compute maca,macb_check 4)send M3 5)compute and show digest diga
            # 3.1) receive M2 from B, M2=(A,B,Nb,PKbx,PKby)
            Nb = M2.split(',')[2]
            PKbx = M2.split(',')[3]
            PKby = M2.split(',')[4]
            macb=M2.split(',')[5]
            PKb = (int(PKbx),int(PKby))
            # 3.2) compute Ka
            Ka=mul(c_p,c_q,c_n,PKb,SKa)          
            # 3.3) compute maca,macb_check
            hmac_stringb=idA+idB+str(ca)+Nb
            newhash=hmac.new(str(Ka[0]).encode(),''.encode(),sha256)
            newhash.update(hmac_stringb.encode())
            macb_check=newhash.hexdigest()
            if macb_check==macb:
                hmac_stringa=idB+idA+Nb+str(ca)
                newhash=hmac.new(str(Ka[0]).encode(),''.encode(),sha256)
                newhash.update(hmac_stringa.encode())
                maca=newhash.hexdigest()
                # 3.4) A->B: M3=(Na,maca)
                M3=str(Na)+','+maca
                # 3.5) compute and show digest diga
                hmac_stringa=str(Na)+str(Nb)
                newhash=hmac.new(str(Ka[0]).encode(),''.encode(),sha256)
                newhash.update(hmac_stringa.encode())
                diga=newhash.hexdigest()[0:4]         
                print ('A side: digest is',diga)
                print ('the share secret is',Ka)             
            else:
                print('A side: macb is invalid, protocol fails')

            # 4. B receive M3 from A, verify maca, verify ca, compute and show digb
            # 4.1) receive M3=maca from A
            Na=M3.split(',')[0]
            maca=M3.split(',')[1]
            hmac_stringa=idB+idA+str(Nb)+str(ca)
            newhash=hmac.new(str(Kb[0]).encode(),''.encode(),sha256)
            newhash.update(hmac_stringa.encode())
            maca_check=newhash.hexdigest()
            if maca_check==maca:
                stringca=Na+idA+idB+PKax+PKay
                newmd5=md5()
                newmd5.update(stringca.encode())
                ca_check=newmd5.hexdigest()
                if ca_check==ca:                  
                    hmac_stringa=str(Na)+str(Nb)
                    newhash=hmac.new(str(Kb[0]).encode(),''.encode(),sha256)
                    newhash.update(hmac_stringa.encode())
                    digb=newhash.hexdigest()[0:4]         
                    print ('B side: digest is',digb)
                    print ('the shared secret is', Kb)
                else:
                    print('B side: commitA is invalid, protocol fails')
            else:
                print('B side: maca is invalid, protocol fails')
                
            token=1
            
    except KeyboardInterrupt:
        print("KeyboardInterrupt")
    #sys.exit(0)

    







