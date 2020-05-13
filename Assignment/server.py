import socket
import time
import random
import hmac

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

if __name__ == '__main__':
    
    global Ta,Rb,p,n,b,x,y,c_p,c_q,c_n,M1,M2,M3,M4, dhkey

    HOST = '192.168.0.3'
    PORT = 6666

    # initialization
    p, n, b, x, y=DOMAINS[256]
    c_p=3
    c_n=p
    c_q=p-b
    addressA='00000001'
    addressB='00000002'
    PW=(1234,5678)
    flag = False
    
    #TCP link
    sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    sock.bind((HOST,PORT))
    print('Listen to connections from initiators...')
    sock.listen(5)
    
    try:
        while(not flag):
            connection, address = sock.accept()
            print('Connected to initiator via ', address)
            # Stage 2
            # 2.1) Acknowledge M1=(B,A,Na,PKax,PKay) from initiator A
            M1=connection.recv(1024).decode()
            Na=M1.split(',')[2]
            PKapsx=M1.split(',')[3]
            PKapsy=M1.split(',')[4]
            PKaps=(int(PKapsx),int(PKapsy))
            # 2.2) Generate a random keypair
            keypair = Key.generate(256)
            # 2.3) Select private key SKa
            SKb = keypair._priv[1]
            # 2.4) Compute public key PKa
            PKbx = keypair._pub[1][0]
            PKby = keypair._pub[1][1]
            PKb = (PKbx,PKby)
            # 2.5) Select Nonce B (Nb)
            Nb=random.randint(000000,999999)
            # 2.6) Send M2=(A,B,Nb,PKbx,PKby) to initiator A
            M2=addressA+','+addressB+','+str(Nb)+','+str(PKbx)+','+str(PKby)
            connection.send(M2.encode())
            
            # Stage 3 - Responder Side
            # 3.1) Recover PKa
            PKa= add(c_p,c_q,c_n,PKaps,PW)
            # 3.2) Compute DHKey and macB
            dhkey= mul(c_p,c_q,c_n,PKa,SKb)
            hmac_stringb=addressA+addressB+Na+str(Nb)
            newhash=hmac.new(str(dhkey[0]).encode(),''.encode(),sha256)
            newhash.update(hmac_stringb.encode())
            macb=newhash.hexdigest()
            # 3.3) Send M3=(A,B,Nb,PKbx,PKby, macb) to initiator A
            M3=addressA+','+addressB+','+str(Nb)+','+str(PKbx)+','+str(PKby)+','+macb
            connection.send(M3.encode())
            
            # Stage 5
            # 5.1) Receive M4=(B,A,Na,PKax,PKay,maca) from initiator A
            M4=connection.recv(1024).decode()
            Na=M4.split(',')[2]
            PKapsx=M4.split(',')[3]
            PKapsy=M4.split(',')[4]
            PKaps=(int(PKapsx),int(PKapsy))
            maca=M4.split(',')[5]
            # 5.2) Check if maca is correct
            hmac_stringa=addressA+addressB+str(Nb)+Na
            newhash=hmac.new(str(dhkey[0]).encode(),''.encode(),sha256)
            newhash.update(hmac_stringa.encode())
            maca_check=newhash.hexdigest()
            if (maca == str(maca_check)):
                print("maca is valid")
                print("Shared secret key => ", dhkey)
            else:
                print("Invalid macb! connection stopped...")
            flag = True
                
    except KeyboardInterrupt:
        print('>>>quit')