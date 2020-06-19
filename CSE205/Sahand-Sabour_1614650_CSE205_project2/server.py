"""
CSE205_project2
Name ==> Sahand Sabour
Student ID ==> 1614650
"""

from socket import *
import sys


# This function compares the obtained values from client to own values for dv
def dataAnalyzer(data, current_node,current_dvdict):
    result_dict=current_dvdict
    sections= data.strip().split(' ')
    node= sections[0]
    node_priority= sections[1]
    new_dvdict= {}
    for i in range(2, len(sections), 3):
        key= node+'-'+sections[i]
        new_dvdict[key]= int(sections[i+1])

    for key, value in new_dvdict.items():
        start, dest= key.split('-')
        if(current_node+'-'+dest in current_dvdict.keys()):
            old_value= current_dvdict[current_node+'-'+dest]
            new_value= current_dvdict[current_node + '-' + start]+new_dvdict[start+'-'+dest]
            final_value= min(old_value, new_value)
            result_dict[current_node+'-'+dest]= final_value
        else:

            result_dict[current_node+'-'+dest]=new_dvdict[start+'-'+dest]+current_dvdict[current_node + '-' + start]
    return result_dict, node

if __name__ == '__main__':
    # initiation part of the server for each node (Except for the first node)
    arguments= sys.argv
    current_node= arguments[1]
    priority=arguments[2]
    current_dvdict={}
    priority_dict= {}

    for i in range(3, len(arguments)-1, 3):
        key= current_node+'-'+arguments[i]
        current_dvdict[key]= int(arguments[i+1])
        priority_dict[arguments[i]]=int(arguments[i+2])

    # The number of the neighbors that the node has
    neighbors_num= len(priority_dict.keys())

    serverName= 'localhost'
    serverPort= 1000+int(priority)

    # Creating the server socket
    listenerSocket = socket(AF_INET, SOCK_STREAM)
    # to prevent 'Connection closed by peer' error
    listenerSocket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
    listenerSocket.bind((serverName,serverPort))
    # The node has to be open to all neighbors ==> For n neighbors, it listens to n connections!
    listenerSocket.listen(neighbors_num)

    # The response that the server sends to each client (Based on the protocol)
    serverResponse=current_node+' '+priority+' '

    for key, value in current_dvdict.items():
        node= key.replace(current_node+'-','')
        serverResponse+= node +' '+str(current_dvdict[key])+' '+str(priority_dict[node])+' '

    # for removing extra spaces (if there are any)
    serverResponse= " ".join(serverResponse.split())

    # A dictionary to check whether the client has contacted this server or not
    client_responses={}
    for key, value in priority_dict.items():
        # As long as that node has lower priority than the current node
        # Because the server would be contacted by those clients
        if(value<int(priority)):
            client_responses[key]= 'Waiting'


    # While there are clients that haven't contacted the server yet
    while 'Waiting' in client_responses.values():
        conn, addr = listenerSocket.accept()
        data = conn.recv(1024).decode()
        current_dvdict, client_node= dataAnalyzer(data,current_node, current_dvdict)
        conn.send(serverResponse.encode())
        # The data from a client was received and the server no longer waits for that client
        client_responses[client_node]= 'END'
        conn.close()

    # The response that gets sent to the main program ==> project2.py
    output= current_node+' '+priority+' '
    for key, value in current_dvdict.items():
        node= key.replace(current_node+'-','')
        output += node + ' ' + str(current_dvdict[key])+' '

    # by printing, the response is sent to the main process
    print(output)








