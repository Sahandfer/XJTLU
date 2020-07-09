# Sahand Sabour - 1614650
# Basic implementation of the CoAP client
# 1) Change self.SERVER to IP address of your choosing.
# 2) Run this file via:
#    python src/client.py [Request's Method] [Request's Index] [Payload (optional)]

# NOTE: The server.py file must be intiated beforehand!

import sys
import socket
import time

from coapthon.client.helperclient import HelperClient


class COAPClient:
    def __init__(self):
        self.SERVER = "192.168.0.3"  # The server's IP address
        self.PORT = 5683  # The server's port
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # UDP socket
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.client = HelperClient(
            server=(self.SERVER, self.PORT), sock=self.sock
        )  # CoAP client

    # Processes the user's input method and parameters and sends the corresponding request to the server
    def processMethod(self, method, path, payload):
        startTime = time.time()
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
        endTime = time.time()
        print("\nElapsed Time: %f seconds" % (endTime - startTime))


if __name__ == "__main__":
    try:
        # Get arguments from the user
        args = sys.argv
        method, path = args[1:3]
        payload = args[3] if len(args) > 3 else ""
        client = COAPClient()
        client.processMethod(method, path, payload)
    except KeyboardInterrupt:
        COAPClient.client.stop()
        print("Client Shutdown")
