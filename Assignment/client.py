import errno
import socket
import time
import random
import hmac

from collections import OrderedDict
from ecc.Key import Key
from hashlib import sha256
from ecc.elliptic import mul, add, neg

DOMAINS = {
    # Bits : (p, order of E(GF(P)), parameter b, base point x, base point y)
    256: (
        0xFFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFF,
        0xFFFFFFFF00000000FFFFFFFFFFFFFFFFBCE6FAADA7179E84F3B9CAC2FC632551,
        0x5AC635D8AA3A93E7B3EBBD55769886BC651D06B0CC53B0F63BCE3C3E27D2604B,
        0x6B17D1F2E12C4247F8BCE6E563A440F277037D812DEB33A0F4A13945D898C296,
        0x4FE342E2FE1A7F9B8EE7EB4A7C0F9E162BCE33576B315ECECBB6406837BF51F5,
    )
}

if __name__ == "__main__":

    global Ra, Tb, p, n, b, x, y, c_p, c_q, c_n, M1, M2, M3, M4, dhkey, macb
    server_ip = "192.168.0.3"
    server_port = 6666

    # Variable initialization
    p, n, b, x, y = DOMAINS[256]
    c_p = 3
    c_n = p
    c_q = p - b
    addressA = "00000001"
    addressB = "00000002"
    PW = (1234, 5678)
    flag = False
    
    # TCP connection to Responder B
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.setblocking(1)
    print("Initializing socket connection to responder B...")
    sock.connect((server_ip, server_port))
    
    try:
        while(not flag):
            print('Socket connected to responder B')
            # Stage 1
            # 1.1) Generate a random keypair
            keypair = Key.generate(256)
            # 1.2) Select private key SKa
            SKa = keypair._priv[1]
            # 1.3) Compute public key PKa
            PKax = keypair._pub[1][0]
            PKay = keypair._pub[1][1]
            PKa = (PKax,PKay)
            # 1.4) Compute password-scrambled public key PKaps
            PKaps = add(c_p, c_q, c_n, PKa, neg(PW, c_n))
            # 1.5) Select Nonce A (Na)
            Na=random.randint(000000,999999)
            # 1.6) Send M1=(B,A,Na,PKax,PKay) to responder B
            M1=addressB+','+addressA+','+str(Na)+','+str(PKaps[0])+','+str(PKaps[1])
            sock.send(M1.encode())
            
            # Stage 3 - Initiator Side
            # 3.1) Receive M2=(A,B,Nb,PKbx,PKby) from responder B
            M2 = sock.recv(1024).decode()
            Nb = M2.split(',')[2]
            PKbx = M2.split(',')[3]
            PKby = M2.split(',')[4]
            PKb = (int(PKbx),int(PKby))
            # 3.2) Compute DHKey and maca
            dhkey= mul(c_p,c_q,c_n,PKb,SKa)
            hmac_stringa=addressB+addressA+Nb+str(Na)
            newhash=hmac.new(str(dhkey[0]).encode(),''.encode(),sha256)
            newhash.update(hmac_stringa.encode())
            maca=newhash.hexdigest()
            
            # Stage 4
            # 4.1) Receive M3=(A,B,Nb,PKbx,PKby,macb) from responder B
            M3 = sock.recv(1024).decode()
            Nb = M3.split(',')[2]
            PKbx = M3.split(',')[3]
            PKby = M3.split(',')[4]
            PKb = (int(PKbx),int(PKby))
            macb = M3.split(',')[5]
            # 4.2) Check if macb is correct
            hmac_stringb=addressA+addressB+str(Na)+Nb
            newhash=hmac.new(str(dhkey[0]).encode(),''.encode(),sha256)
            newhash.update(hmac_stringb.encode())
            macb_check=newhash.hexdigest()
            if (macb == str(macb_check)):
                print("macb is valid")
                # 4.3) Send M4=(B,A,Na,PKax,PKay,maca) to responder B
                M4=addressB+','+addressA+','+str(Na)+','+str(PKaps[0])+','+str(PKaps[1])+','+maca
                sock.send(M4.encode())
                print("Shared secret key => ", dhkey)
            else:
                print("Invalid macb! connection stopped...")
            flag = True
    except KeyboardInterrupt:
        print('>>>quit')
                
            