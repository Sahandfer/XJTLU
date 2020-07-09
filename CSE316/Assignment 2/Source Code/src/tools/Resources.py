# Sahand Sabour - 1614650
# A basic implementation of a CoAP index-accessible resource
import json

from coapthon import defines
from coapthon.resources.resource import Resource
from tools.Utils import Utils


class COAPResource(Resource):
    def __init__(self, name="COAPResource", coap_server=None):
        super(COAPResource, self).__init__(
            name, coap_server, visible=True, observable=True, allow_children=False
        )
        # The payload of the request is a json file
        # The file contains randomly generate values that simulate sensor outputs
        self.resource_type = "rt1"
        self.content_type = "application/json"
        self.interface_type = "if1"
        self.payload = (
            defines.Content_types["application/json"],
            json.dumps({"Data": Utils().genRandValues(6)}),
        )

    def render_GET(self, request):  # Resoond to GET request
        return self

    def render_POST(self, request):  # Resoond to POST request
        res = COAPResource()
        res.location_query = request.uri_query
        res.payload = request.payload
        return res

    def render_PUT(self, request):  # Resoond to PUT request
        self.payload = request.payload
        return self

    def render_DELETE(self, request):  # Resoond to DELETE request
        return True
