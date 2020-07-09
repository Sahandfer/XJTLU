# Sahand Sabour - 1614650
# A class of functions for the required processes of the proposed method

import time
import random

from tools.ecc.Key import Key
from hashlib import sha256, md5
from tools.ecc.elliptic import mul, add, neg
from tools.ecc.ecdsa import sign, verify
from tools.ecc.curves import get_curve

# Perform the required processes for the protocol
class Utils:
    def __init__(self):
        bits, self.c_n, n, self.c_p, self.c_q, (x, y) = get_curve(256)

    # Generate a random 256 bit secret key
    def genKeys(self):
        keypair = Key.generate(256)
        publicKey = keypair._pub[1]
        secretKey = keypair._priv[1]
        return publicKey, secretKey

    # Generate a random 256 bit signiture based on public and secret keys
    def genSigniture(self, password, pk, sk):
        hashString = password + str(pk[0]) + str(pk[1])
        h = self.genHash(hashString)
        sig = sign(h, (256, int(sk)))
        signature = str(sig[0]) + "," + str(sig[1])
        return signature

    # Generate an ecrypted hash of a given string
    def genHash(self, hashStr):
        md5a = md5()
        md5a.update(hashStr.encode())
        h = md5a.hexdigest()[8:-8]
        h = int(h, 16)
        return h

    # Verify a given signiture by the hash and public and secret keys
    def verifyHash(self, h, sig, pk):
        pkx, pky = pk
        return verify(h, sig, (256, (int(pkx), int(pky))))

    # Identify the shared secret key based on the public and secret keys
    def genSharedSK(self, pk, sk):
        return mul(self.c_p, self.c_q, self.c_n, pk, sk)

    # Generate random values to simulate sensors' incoming data
    def genRandValues(self, num):
        randValues = []
        for i in range(0, num):
            randValues.append(
                {"timeStamp": time.time(), "value": random.randint(1, 65535)}
            )

        return randValues
