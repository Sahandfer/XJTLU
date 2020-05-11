#import serial
import socket
import time
import random
import hmac

from collections import OrderedDict
from ecc.Key import Key
from hashlib import sha256,md5
from ecc.elliptic import mul,add,neg
from ecc.curves import get_curve
from time import clock

DOMAINS = {
    # Bits : (p, order of E(GF(P)), parameter b, base point x, base point y)
    256: (0xffffffff00000001000000000000000000000000ffffffffffffffffffffffffL,
          0xffffffff00000000ffffffffffffffffbce6faada7179e84f3b9cac2fc632551L,
          0x5ac635d8aa3a93e7b3ebbd55769886bc651d06b0cc53b0f63bce3c3e27d2604bL,
          0x6b17d1f2e12c4247f8bce6e563a440f277037d812deb33a0f4a13945d898c296L,               0x4fe342e2fe1a7f9b8ee7eb4a7c0f9e162bce33576b315ececbb6406837bf51f5L)
}

if __name__ == '__main__':

    global Ta,Rb,p,n,b,x,y,c_p,c_q,c_n,M1,M2,M3,Kb

    HOST = '192.168.0.111'
    PORT = 6633

    # initialization
    p, n, b, x, y=DOMAINS[256]
    c_p=3
    c_n=p
    c_q=p-b
    idA='00000001'
    idB='00000002'
    token=0

    print('Begin')

    #TCP link
    sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    sock.bind((HOST,PORT))

    print('Listen to the connection from client...')
    sock.listen(5)
    try:
        while (token==0):
            connection, address = sock.accept()
            print('Connected. Got connection from ', address)

            # 2. B receive M1 from A, generate my keypair, generate Nb, compute Kb and macb, send M2
            # 2.1) receive M1=(B,A,ca,PKax,PKay) from B
            M1=connection.recv(1024)
            ca=M1.split(',')[2]
            PKax=M1.split(',')[3]
            PKay=M1.split(',')[4]
            PKa=(long(PKax),long(PKay))
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
            newhash=hmac.new(str(Kb[0]),'',sha256)
            newhash.update(hmac_stringb) 
            macb=newhash.hexdigest()  
            # 2.4) send M2
            M2=idA+','+idB+','+str(Nb)+','+str(PKbx)+','+str(PKby)+','+macb
            connection.send(M2)

            # 4. B receive M3 from A, verify maca, verify ca, compute and show digb
            # 4.1) receive M3=maca from A
            M3=connection.recv(1024)
            Na=M3.split(',')[0]
            maca=M3.split(',')[1]
            hmac_stringa=idB+idA+str(Nb)+str(ca)
            newhash=hmac.new(str(Kb[0]),'',sha256)
            newhash.update(hmac_stringa)
            maca_check=newhash.hexdigest()
            if maca_check==maca:
                stringca=Na+idA+idB+PKax+PKay
                newmd5=md5()
                newmd5.update(stringca)
                ca_check=newmd5.hexdigest()
                if ca_check==ca:                  
                    hmac_stringa=str(Na)+str(Nb)
                    newhash=hmac.new(str(Kb[0]),'',sha256)
                    newhash.update(hmac_stringa)
                    digb=newhash.hexdigest()[0:4]         
                    print ('digest is',digb)
                    print ('the shared secret is', Kb)
                else:
                    print 'commitA is invalid, protocol fails'
            else:
                print 'maca is invalid, protocol fails'
       

            token=1

    except KeyboardInterrupt:
        print('>>>quit')
    #sys.exit(0)




