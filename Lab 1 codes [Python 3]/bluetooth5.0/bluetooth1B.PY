#import serial
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

    global Ta,Rb,p,n,b,x,y,c_p,c_q,c_n,M1,M2,M3,Kb

    HOST = '127.0.0.1'
    PORT = 9001

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

            # 2. 1)receive M1=(PKax,PKay) from A, 2) send M2=(PKbx,PKby) to B
            M1=connection.recv(1024).decode()
            PKax=M1.split(',')[0]
            PKay=M1.split(',')[1]
            PKa=(int(PKax),int(PKay))
            keypair = Key.generate(256)
            PKbx = keypair._pub[1][0]
            PKby = keypair._pub[1][1]
            SKb = keypair._priv[1]
            M2=str(PKbx)+','+str(PKby)
            connection.send(M2.encode())

            # 4. 1)receive M3=(A,Ra,hasha), 2)generate Rb, 3) compute hashb, 4) send M4=(B,Rb,hashb)
            M3=connection.recv(1024).decode()
            Ra=M3.split(',')[1]
            hasha=M3.split(',')[2]
            Rb=random.randint(000000,999999)
            hash_stringb=str(PKbx)+str(PKby)
            newhash=hmac.new(str(Rb).encode(),''.encode(),sha256)
            newhash.update(hash_stringb.encode())
            hashb=newhash.hexdigest() 
            M4=idB+','+str(Rb)+','+hashb  
            connection.send(M4.encode())

            # 6. 1)receive M5=Na, 2)verify hasha, 3)send M6=Nb
            M5=connection.recv(1024).decode()
            Na=int(M5)
            hash_stringa=str(PKax)+str(PKay)
            newhash=hmac.new(str(Ra).encode(),''.encode(),sha256)
            newhash.update(hash_stringa.encode())
            hasha_check=newhash.hexdigest() 
            if hasha_check==hasha:
                Nb=random.randint(000000,999999)
                M6=str(Nb)
                connection.send(M6.encode())

                # 8. 1)receive M7=maca, 2)compute Kb, 3)verify maca, 4)compute macb, 5)send M8=macb
                M7=connection.recv(1024).decode()
                maca=M7
                Kb=mul(c_p,c_q,c_n,PKa,SKb)
                hmac_stringa=str(Na)+str(Nb)+str(Rb)+idA+idB
                newhash=hmac.new(str(Kb[0]).encode(),''.encode(),sha256)
                newhash.update(hmac_stringa.encode())
                maca_check=newhash.hexdigest()
                if maca_check==maca:
                    hmac_stringb=str(Nb)+str(Na)+str(Ra)+idB+idA
                    newhash=hmac.new(str(Kb[0]).encode(),''.encode(),sha256)
                    newhash.update(hmac_stringb.encode())
                    macb=newhash.hexdigest()                                         
                    M8=macb
                    connection.send(M8.encode())
                    print('maca is valid')
                    print('the shared secrety is', Kb)
                else:
                    print('maca is invalid, protocol fails.')

            else:
                print('hashb is invalid, protocol fails.')

            token=1

    except KeyboardInterrupt:
        print('>>>quit')
    #sys.exit(0)




