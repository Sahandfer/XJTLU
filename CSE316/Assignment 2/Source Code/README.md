# Lightweight Secure COAP in the Internet of Things (IoT)
> This is a project for the CSE316 module's assignment 2 made by Sahand Sabour (Student ID: 1614650).

## Protocol description
1)	Client A generates public key PKC and private key SKC. Then, it sends M1 = (deviceID, PKC) to server.
2)	Server receives and verifies M1 as well as it’s the client’s device ID. Accordingly, it generate public key PKS and private key SKC and sends M2 = (“HelloClient”, PKS) to client.
3)	Client receives and verifies M2. Consequently, it generates signature SIGC = H(deviceID, PKC, SKC) and sends M3 = (SIGC) to server.
4)	Server receives M3. The client signiture SIGC is verified via verify(H(deviceID, PKC), SIGC). Then, it calculates SIGS = H(deviceID, PKS, SKS) and sends M4 = (SIGS) to client. Accordingly, it calculated shared secret key = PKC∙SKS.
5)	Client receives M4 and verifies server’s signture by verify(H(deviceID, PKS), SIGS). Subsequently, it computes shared secret key  ssk= PKS∙SKC and sends request req to the server.
6)	Server receives request req, performs the relative operations and sends corresponding response res to client.
7)	Client receives and decrypts the response.

## Prerequisites
Download the latest version of [CoApthon](https://github.com/Tanganelli/CoAPthon).

## Program usage:
This section provides the required commands for each file respectively.
The server files should be run before the client. 

### server.py
```shell
python src/server.py
```

### client.py
```shell
python src/client.py [request method] [request index] [request payload]
```

### secureServer.py
```shell
python src/secureServer.py
```

### secureClient.py
```shell
python src/secureClient.py [request method] [request index] [request payload]
```