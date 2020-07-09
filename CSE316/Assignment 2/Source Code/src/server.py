# Sahand Sabour - 1614650
# Basic implementation of the CoAP server
# 1) Change self.SERVER to IP address of your choosing.
# 2) Run this file via:
#    python src/server.py


from coapthon.server.coap import CoAP
from tools.Resources import COAPResource


class CoAPServer(CoAP):
    def __init__(self):
        self.SERVER = "192.168.0.3"  # Access IP address
        self.PORT = 5683  # Access port
        # Bind IP and port to the CoAP server
        CoAP.__init__(self, (self.SERVER, self.PORT))
        # Declare the available resources and their indexes
        self.add_resource("index/", COAPResource())
        print("Server listening on %s:%d" % (self.SERVER, self.PORT))


if __name__ == "__main__":
    server = CoAPServer()
    try:
        server.listen(5)

    except KeyboardInterrupt:
        server.close()
        print("Server Shutdown")
