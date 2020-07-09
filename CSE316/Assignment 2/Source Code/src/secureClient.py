# Sahand Sabour - 1614650
# Basic implementation of the proposed method's client
# 1) Change self.SERVER to IP address of your choosing.
# 2) Run this file via:
#    python src/secureClient.py [Request's Method] [Request's Index] [Payload (optional)]

# NOTE: The secureServer.py file must be intiated beforehand!

import sys
import socket
import time

from tools.Utils import Utils
from coapthon import defines
from coapthon.client.helperclient import HelperClient
from coapthon.messages.request import Request


class COAPSecureClient:
    def __init__(self):
        self.SERVER = "192.168.0.3"  # The server's  IP address
        self.PORT = 5684  # The server's  port for request
        self.SECPORT = 5688  # The server's  port for authentication
        self.deviceID = "SA20200614_A2"  # This device's ID
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.client = HelperClient(server=(self.SERVER, self.PORT))

    def authenticateSelf(self):
        sharedSK = ""  # Shared secret key
        utils = Utils()

        # Stage 1
        # 1.1 ) Generate public key PKC and private key SKC
        PKC, SKC = utils.genKeys()
        # 1.2) send M1 = (DeviceID, PKC) to server
        M1 = self.deviceID + "," + str(PKC[0]) + "," + str(PKC[1])
        self.sock.sendto(M1.encode(), (self.SERVER, self.SECPORT))
        print("M1 sent")

        # Stage 3
        # 3.1) Receive M2 from the server
        M2, address = self.sock.recvfrom(1024)
        M2 = M2.decode()
        # 3.2) Check if the device ID was accepted
        if len(M2.split(",")) != 1:
            # 3.3 ) Store server's public key
            helloC = M2.split(",")[0]
            PKSx = M2.split(",")[1]
            PKSy = M2.split(",")[2]
            PKS = (int(PKSx), int(PKSy))
            print("M2 received")
            # 3.4) Generate signature H(deviceID, PKC) and send it to the server
            M3 = utils.genSigniture(self.deviceID, PKC, SKC)
            self.sock.sendto(M3.encode(), address)
            print("M3 sent")

            # Stage 5
            # 5.1 ) Receive M4 from the server
            M4, address = self.sock.recvfrom(1024)
            M4 = M4.decode()
            # 5.2) Check if the provided signature was validated
            if M4 == "401":
                print("Authentication failed...")
            else:
                # 5.3) Store server's signature
                signSx, signSy = M4.split(",")
                signS = (int(signSx), int(signSy))
                print("M4 received")

                # 5.4) Verify server's signature
                hashStringS = self.deviceID + str(PKSx) + str(PKSy)
                h = utils.genHash(hashStringS)
                if utils.verifyHash(h, signS, PKS):
                    sharedSK = utils.genSharedSK(PKS, SKC)
                    success = True
                    print("Server authenticated!")
                    print("Shared key: ", sharedSK)
                else:
                    print("Failed to authenticate server...")
        else:
            print("Shutdown due to incorrect device id")
        self.sock.close()
        return sharedSK

    def processRequest(self, method, path, payload):
        response = ""  # Server's response
        if method == "GET":
            response = self.client.get(path)
        elif method == "POST":
            response = self.client.post(path, payload)
        elif method == "PUT":
            response = self.client.put(path, payload)
        elif method == "DELETE":
            response = self.client.delete(path)
        else:
            print("Undefined method...")
        if response:
            print(response.pretty_print())
        self.client.close()  # Close the connection upon receiving the response


if __name__ == "__main__":
    try:
        # Get arguments from the user
        args = sys.argv
        method, path = args[1:3]
        payload = args[3] if len(args) > 3 else ""
        client = COAPSecureClient()
        startTime = time.time()
        sharedSK = client.authenticateSelf()
        if sharedSK:
            client.processRequest(method, path, payload)
            endTime = time.time()
            print("\nElapsed Time: %f seconds" % (endTime - startTime))
        else:
            print("Shut down due to authentication failure")

    except KeyboardInterrupt:
        COAPSecureClient.client.stop()
        print("Client Shutdown")
