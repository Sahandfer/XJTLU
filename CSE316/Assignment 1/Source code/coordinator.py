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

    HOST = "192.168.0.3" # The ip address of the server
    PORT = 6666 # The port to accept connections from

    # Variable initializations
    bits, c_n, n, c_p, c_q, (x, y) = get_curve(256)
    addressA = "2020051701"
    addressB = "2020051702"
    PW = (1614650, 31601100)
    flag = False

    # TCP link
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind((HOST, PORT))
    print("Listen to connections from initiators...")
    sock.listen(5)

    try:
        while not flag:
            connection, address = sock.accept()
            print("Connected to sensor via ", address)
            startTime = time.time()
            
            # Stage 2
            # 2.1) Receive and acknowledge M1=(B,A,Na,PKax,PKay) from sensor A
            M1 = connection.recv(1024).decode()
            Na = M1.split(",")[2]
            PKapsx = M1.split(",")[3]
            PKapsy = M1.split(",")[4]
            PKaps = (int(PKapsx), int(PKapsy))
            connection.send("M1".encode())
            # 2.2) Generate a random keypair
            keypair = Key.generate(256)
            # 2.3) Select private key SKa
            SKb = keypair._priv[1]
            # 2.4) Compute public key PKa
            PKbx = keypair._pub[1][0]
            PKby = keypair._pub[1][1]
            PKb = (PKbx, PKby)
            # 2.5) Select Nonce B (Nb)
            Nb = random.randint(000000, 999999)
            # 2.6) Send M2=(A,B,Nb,PKbx,PKby) to sensor A
            M2 = (
                addressA
                + ","
                + addressB
                + ","
                + str(Nb)
                + ","
                + str(PKbx)
                + ","
                + str(PKby)
            )
            connection.send(M2.encode())
            # 1.7) Wait for sensor A to acknowledge M2
            ACK = connection.recv(1024).decode()
            if ACK == "M2":
                print("M2 Acknowledged! Continuing the protocol")
            else:
                print("M2 was NOT acknowledged...stopping the protocol")
                flag = True
                break

            # Stage 4
            # 4.1) Recover PKa
            PKa = add(c_p, c_q, c_n, PKaps, PW)
            # 4.2) Compute DHKey and macB
            dhkey = mul(c_p, c_q, c_n, PKa, SKb)
            hmac_stringb = addressA + addressB + Na + str(Nb)
            newhash = hmac.new(str(dhkey[0]).encode(), "".encode(), sha256)
            newhash.update(hmac_stringb.encode())
            macb = newhash.hexdigest()
            # 4.3) Send M3=(A,B,Nb,PKbx,PKby, macb) to sensor A
            M3 = (
                addressA
                + ","
                + addressB
                + ","
                + str(Nb)
                + ","
                + str(PKbx)
                + ","
                + str(PKby)
                + ","
                + macb
            )
            connection.send(M3.encode())
            # 4.4) Wait for sensor A to acknowledge M3
            ACK = connection.recv(1024).decode()
            if ACK == "M3":
                print("M3 Acknowledged! Continuing the protocol")
            else:
                print("M3 was NOT acknowledged...stopping the protocol")
                flag = True
                break

            # Stage 6
            # 6.1) Receive and acknowledge M4=(B,A,Na,PKax,PKay,maca) from sensor A
            M4 = connection.recv(1024).decode()
            Na = M4.split(",")[2]
            PKapsx = M4.split(",")[3]
            PKapsy = M4.split(",")[4]
            PKaps = (int(PKapsx), int(PKapsy))
            maca = M4.split(",")[5]
            connection.send("M4".encode())
            # 6.2) Check if maca is correct
            hmac_stringa = addressB + addressA + str(Nb) + Na
            newhash = hmac.new(str(dhkey[0]).encode(), "".encode(), sha256)
            newhash.update(hmac_stringa.encode())
            maca_check = newhash.hexdigest()
            if maca == str(maca_check):
                print("maca is valid")
                endTime = time.time()
                print("Shared secret key => ", dhkey)
                print("\nRuntime: %f seconds" % (endTime - startTime))
            else:
                print("Invalid maca! connection stopped...")
            flag = True

    except KeyboardInterrupt:
        sock.close()
        print(">>>quit")

