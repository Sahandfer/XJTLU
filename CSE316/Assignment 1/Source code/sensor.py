import socket
import time
import random
import hmac

from hashlib import sha256
from ecc.Key import Key
from ecc.elliptic import mul, add, neg
from ecc.curves import get_curve

if __name__ == "__main__":

    global bits, c_n, n, c_p, c_q, x, y, M1, M2, M3, M4, ACK, dhkey, maca, f

    hostIP = "192.168.0.3"
    hostPort = 6666

    # initialization
    bits, c_n, n, c_p, c_q, (x, y) = get_curve(256)
    addressA = "2020051701"
    addressB = "2020051702"
    PW = (1614650, 31601100)
    flag = False

    # TCP connection to coordinator B
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.setblocking(1)
    print("Initializing socket connection to coordinator B...")
    sock.connect((hostIP, hostPort))

    try:
        while not flag:
            print("Socket connected to coordinator B")
            startTime = time.time()

            # Stage 1
            # 1.1) Generate a random keypair
            keypair = Key.generate(256)
            # 1.2) Select private key SKa
            SKa = keypair._priv[1]
            # 1.3) Compute public key PKa
            PKax = keypair._pub[1][0]
            PKay = keypair._pub[1][1]
            PKa = (PKax, PKay)
            # 1.4) Compute password-scrambled public key PKaps
            PKaps = add(c_p, c_q, c_n, PKa, neg(PW, c_n))
            # 1.5) Select Nonce A (Na)
            Na = random.randint(000000, 999999)
            # 1.6) Send M1=(B,A,Na,PKax,PKay) to coordinator B
            M1 = (
                addressB
                + ","
                + addressA
                + ","
                + str(Na)
                + ","
                + str(PKaps[0])
                + ","
                + str(PKaps[1])
            )
            sock.send(M1.encode())
            # 1.7) Wait for coordinator B to acknowledge M1
            ACK = sock.recv(1024).decode()
            if ACK == "M1":
                print("M1 Acknowledged! Continuing the protocol")
            else:
                print("M1 was NOT acknowledged...stopping the protocol")
                flag = True
                break

            # Stage 3
            # 3.1) Receive and acknowledge M2=(A,B,Nb,PKbx,PKby) from coordinator B
            M2 = sock.recv(1024).decode()
            Nb = M2.split(",")[2]
            PKbx = M2.split(",")[3]
            PKby = M2.split(",")[4]
            PKb = (int(PKbx), int(PKby))
            sock.send("M2".encode())
            # 3.2) Calculate shared secret key dhkey
            dhkey = mul(c_p, c_q, c_n, PKb, SKa)

            # Stage 5
            # 5.1) Receive and acknowledge M3=(A,B,Nb,PKbx,PKby,macb) from coordinator B
            M3 = sock.recv(1024).decode()
            Nb = M3.split(",")[2]
            PKbx = M3.split(",")[3]
            PKby = M3.split(",")[4]
            PKb = (int(PKbx), int(PKby))
            macb = M3.split(",")[5]
            sock.send("M3".encode())
            # 5.2) Compute DHKey and maca
            hmac_stringa = addressB + addressA + Nb + str(Na)
            newhash = hmac.new(str(dhkey[0]).encode(), "".encode(), sha256)
            newhash.update(hmac_stringa.encode())
            maca = newhash.hexdigest()
            # 5.3) Check if macb is correct
            hmac_stringb = addressA + addressB + str(Na) + Nb
            newhash = hmac.new(str(dhkey[0]).encode(), "".encode(), sha256)
            newhash.update(hmac_stringb.encode())
            macb_check = newhash.hexdigest()
            if macb == str(macb_check):
                print("macb is valid")
                # 5.4) Send M4=(B,A,Na,PKax,PKay,maca) to coordinator B
                M4 = (
                    addressB
                    + ","
                    + addressA
                    + ","
                    + str(Na)
                    + ","
                    + str(PKaps[0])
                    + ","
                    + str(PKaps[1])
                    + ","
                    + maca
                )
                sock.send(M4.encode())
                ACK = sock.recv(1024).decode()
                if ACK == "M4":
                    print("M4 Acknowledged! Continuing the protocol")
                else:
                    print("M4 was NOT acknowledged...stopping the protocol")
                    flag = True
                    break
                endTime = time.time()
                print("Shared secret key => ", dhkey)
                print("\nRuntime: %f seconds" % (endTime - startTime))
            else:
                print("Invalid macb! connection stopped...")
            flag = True
    except KeyboardInterrupt:
        print(">>>quit")
