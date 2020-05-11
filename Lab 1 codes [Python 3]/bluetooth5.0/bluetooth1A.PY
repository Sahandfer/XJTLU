import errno
import socket
import time
import random
import hmac



from collections import OrderedDict
from ecc.Key import Key
from hashlib import sha256
from ecc.elliptic import mul,add,neg


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
    server_ip = "127.0.0.1"
    server_port = 9001

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
            # 1. A side: send M1=(PKax,PKay) to B
            #1.1) generate my (A) keypair PKa SKa
            keypair = Key.generate(256)
            PKax = keypair._pub[1][0]
            PKay = keypair._pub[1][1]
            PKa = (int(PKax),int(PKay))
            SKa = keypair._priv[1]
            M1=str(PKax)+','+str(PKay)
            sock.send(M1.encode())

            # 3. 1) receive M2=(PKbx,PKby) 2)generate Ra, 3) compute hasha 4) send M3=(A,Ra,hasha)
            M2=sock.recv(1024).decode()
            PKbx=M2.split(',')[0]
            PKby = M2.split(',')[1]
            PKb = (int(PKbx),int(PKby))
            Ra=random.randint(000000,999999)
            hash_stringa=str(PKax)+str(PKay)
            newhash=hmac.new(str(Ra).encode(),''.encode(),sha256)
            newhash.update(hash_stringa.encode())
            hasha=newhash.hexdigest() 
            M3=idA+','+str(Ra)+','+hasha
            sock.send(M3.encode())

            # 5. 1) receive M4=(B,Rb,hashb), 2)verify hashb, 3) generate Na, 4) send M5=Na
            M4=sock.recv(1024).decode()
            Rb=M4.split(',')[1]
            hashb=M4.split(',')[2]
            hash_stringb=str(PKbx)+str(PKby)
            newhash=hmac.new(str(Rb).encode(),''.encode(),sha256)
            newhash.update(hash_stringb.encode())
            hashb_check=newhash.hexdigest()
            if hashb_check==hashb:
                Na=random.randint(000000,999999)
                M5=str(Na)
                sock.send(M5.encode())
                
                # 7. 1)receive M6=Nb, 2)compute Ka, 3)compute maca, 4)send M7=maca
                M6=sock.recv(1024).decode()
                Nb=int(M6)
                Ka=mul(c_p,c_q,c_n,PKb,SKa)
                hmac_stringa=str(Na)+str(Nb)+str(Rb)+idA+idB
                newhash=hmac.new(str(Ka[0]).encode(),''.encode(),sha256)
                newhash.update(hmac_stringa.encode())
                maca=newhash.hexdigest()
                M7=maca
                sock.send(M7.encode())

                # 9. 1)receive M8=macb, 2)verify macb
                M8=sock.recv(1024).decode()
                macb=M8
                hmac_stringb=str(Nb)+str(Na)+str(Ra)+idB+idA
                newhash=hmac.new(str(Ka[0]).encode(),''.encode(),sha256)
                newhash.update(hmac_stringb.encode())
                macb_check=newhash.hexdigest() 
                if macb_check==macb:
                    print('macb is valid')
                    print('the shared secrety is', Ka)
                else:
                    print('macb is invalid, protocol fails.')
             
            else:
                print('hashb is invalid, protocol fails.')

            token=1
            
    except KeyboardInterrupt:
        s.close()
        print("KeyboardInterrupt")
    #sys.exit(0)

    







