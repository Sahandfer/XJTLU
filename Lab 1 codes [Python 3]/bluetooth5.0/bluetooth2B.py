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


DOMAINS = {
    # Bits : (p, order of E(GF(P)), parameter b, base point x, base point y)
    256: (0xffffffff00000001000000000000000000000000ffffffffffffffffffffffff,
          0xffffffff00000000ffffffffffffffffbce6faada7179e84f3b9cac2fc632551,
          0x5ac635d8aa3a93e7b3ebbd55769886bc651d06b0cc53b0f63bce3c3e27d2604b,
          0x6b17d1f2e12c4247f8bce6e563a440f277037d812deb33a0f4a13945d898c296,
          0x4fe342e2fe1a7f9b8ee7eb4a7c0f9e162bce33576b315ececbb6406837bf51f5)
}

if __name__ == '__main__':

    global Ta,Rb,p,n,b,x,y,c_p,c_q,c_n,M1,M2,M3,Kb

    HOST = '127.0.0.1'
    PORT = 9002

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

            # 2. B receive M1 from A,generate my keypair, generate Nb, compute Cb, send M2
            M1=connection.recv(1024).decode()
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
            connection.send(M2.encode())

            # 4. B receive M3=Na, send M4=Nb, compute and show digb
            M3=connection.recv(1024).decode()
            Na=int(M3)
            M4=str(Nb)
            connection.send(M4.encode())
            hmac_string=str(PKax)+str(PKbx)+str(Na)+str(Nb)
            newhash=hmac.new(str(Kb[0]).encode(),''.encode(),sha256)
            newhash.update(hmac_string.encode())
            digb=newhash.hexdigest()[0:4]      
            print ('digest is',digb)
            print('the shared secret is', Kb)           
            token=1

    except KeyboardInterrupt:
        print('>>>quit')
    #sys.exit(0)




