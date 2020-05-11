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
    token=0

    
    # TCP connection to responder B
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.setblocking(1)  
    print('begin connection')
    sock.connect((server_ip, server_port))
    
    try:
        while (token==0):
            print('connection up')
            print ('connected')
            # 1. A send M1=(PKax,PKay) to B
            keypair = Key.generate(256)
            PKax = keypair._pub[1][0]
            PKay = keypair._pub[1][1]
            PKa = (PKax,PKay)
            SKa = keypair._priv[1]
            M1=str(PKax)+','+str(PKay)
            sock.send(M1)

 
            # 3. A receive M2, send Na
            M2 = sock.recv(1024)
            PKbx = M2.split(',')[0]
            PKby = M2.split(',')[1]
            cb = M2.split(',')[2]
            PKb = (long(PKbx),long(PKby))
            Ka=mul(c_p,c_q,c_n,PKb,SKa)  
            Na=random.randint(000000,999999)
            M3=str(Na)
            sock.send(M3)

            # 5. A receive M4, verify cb, compute and show diga
            M4=sock.recv(1024)
            Nb=long(M4)
            stringcb=PKbx+str(PKax)+str(Nb)
            newmd5=md5()
            newmd5.update(stringcb)
            cb_check=newmd5.hexdigest()
            if cb_check==cb:
                hmac_string=str(PKax)+PKbx+str(Na)+str(Nb)
                newhash=hmac.new(str(Ka[0]),'',sha256)
                newhash.update(hmac_string)
                diga=newhash.hexdigest()[0:4]        
                print ('digest is',diga)
                print('the shared secret is', Ka)
            else:
                print 'cb is invalid, protocol fails'
            token=1
            
    except KeyboardInterrupt:
        s.close()
        print("KeyboardInterrupt")
    #sys.exit(0)

    







