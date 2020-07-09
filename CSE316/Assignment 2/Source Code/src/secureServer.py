# Sahand Sabour - 1614650
# Basic implementation of the proposed method's server
# 1) Change self.SERVER to IP address of your choosing.
# 2) Run this file via:
#    python src/secureServer.py

import socket

from coapthon.server.coap import CoAP
from tools.Resources import COAPResource
from tools.Utils import Utils


class CoAPSecureServer(CoAP):
    def __init__(self):
        self.SERVER = "192.168.0.3"  # Access IP address
        self.PORT = 5684  # Access port for request
        self.SECPORT = 5688  # Access port for authentication
        # List of accepated devices
        self.devices = ["SA20200614_A1", "SA20200614_A2", "SA20200614_A3"]
        # Bind IP and port to the CoAP server
        CoAP.__init__(self, (self.SERVER, self.PORT))
        # Socket for proposed protocol transactions
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind((self.SERVER, self.SECPORT))
        # Declare the available resources and their indexes
        self.add_resource("index/", COAPResource())
        print("Server listening on %s:%d" % (self.SERVER, self.PORT))
        # Start authenting the client
        self.authenticate()

    def authenticate(self):
        utils = Utils()

        # Stage 2
        # 2.1) Receive M1 from the client and store public key PKC
        M1, address = self.sock.recvfrom(1024)
        M1 = M1.decode()
        deviceID = M1.split(",")[0]
        PKCx = M1.split(",")[1]
        PKCy = M1.split(",")[2]
        PKC = (int(PKCx), int(PKCy))
        print("M1 received")

        # 2.2) Verify client's device ID
        if deviceID in self.devices:
            # 2.3) Generate public key PKS and private key SKS
            PKS, SKS = utils.genKeys()
            # 2.4) send M2 = ("HelloC", PKS) to client
            M2 = "HelloC" + "," + str(PKS[0]) + "," + str(PKS[1])
            self.sock.sendto(M2.encode(), address)
            print("M2 sent")

            # Stage 4
            # 4.1) Receive M3 from the client and store its signature
            M3, address = self.sock.recvfrom(1024)
            M3 = M3.decode()
            signCx, signCy = M3.split(",")
            signC = (int(signCx), int(signCy))
            print("M3 received")

            # 4.2) Verify client's signature via verify(H(deviceID, PKC), SIGC).
            hashStringC = deviceID + str(PKCx) + str(PKCy)
            h = utils.genHash(hashStringC)
            if utils.verifyHash(h, signC, PKC):
                # 4.3) Compute shared secret key
                sharedSK = utils.genSharedSK(PKC, SKS)
                # 4.4) Generate signature H(deviceID, PKS) and send it to the client
                M4 = utils.genSigniture(deviceID, PKS, SKS)
                self.sock.sendto(M4.encode(), address)
                print("M4 sent")
                print("Client authenticated!")
                print("Shared key: ", sharedSK)
            else:
                self.sock.sendto("404".encode(), address)
                print("Failed to authenticate client...")

        else:
            error = "Device not defined!"
            print(error)
            self.sock.sendto(error.encode(), address)
        self.sock.close()


if __name__ == "__main__":
    server = CoAPSecureServer()
    try:
        server.listen(5)
    except KeyboardInterrupt:
        server.close()
        print("Server Shutdown")
