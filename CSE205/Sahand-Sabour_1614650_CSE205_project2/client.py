"""
CSE205_project2
Name ==> Sahand Sabour
Student ID ==> 1614650
"""

from socket import *
import sys
from time import sleep
sleep(1)


# This function compares compare the obtained values from server to own values for dv
def dataAnalyzer(data, current_node,current_dvdict):
    result_dict = current_dvdict
    sections = data.strip().split(' ')
    node = sections[0]
    node_priority = sections[1]
    new_dvdict = {}

    for i in range(2, len(sections), 3):
        key= node+'-'+sections[i]
        new_dvdict[key]= int(sections[i+1])

    for key, value in new_dvdict.items():
        start, dest= key.split('-')
        if(current_node+'-'+dest in current_dvdict.keys()):
            old_value= current_dvdict[current_node+'-'+dest]
            new_value= current_dvdict[current_node+'-'+start]+new_dvdict[start+'-'+dest]
            final_value= min(old_value, new_value)
            result_dict[current_node+'-'+dest]= final_value
        else:

            result_dict[current_node+'-'+dest]=new_dvdict[start+'-'+dest]+current_dvdict[current_node + '-' + start]

    return result_dict

if __name__ == '__main__':
    # initiation part of the client for each node (Except for the last node)
    arguments= sys.argv
    current_node= arguments[1]
    priority=int(arguments[2])
    current_dvdict={}
    priority_dict= {}

    for i in range(3, len(arguments)-1, 3):
        key= current_node+'-'+arguments[i]
        current_dvdict[key]= int(arguments[i+1])
        priority_dict[arguments[i]]=int(arguments[i+2])


    serverName= 'localhost'
    # The response that the client sends to each server that it connects to (Based on the protocol)
    clientResponse=current_node+' '+str(priority)+' '

    for key, value in current_dvdict.items():
        node= key.replace(current_node+'-','')
        clientResponse+= node +' '+str(current_dvdict[key])+' '+str(priority_dict[node])+' '

    # for removing extra spaces (if there are any)
    clientResponse= " ".join(clientResponse.split())


    # To connect to each neighbor node's server
    for key,value in priority_dict.items():
        # As long as they have higher priority that the current node
        # Because the client needs to connect to those servers
        if(value>priority):
            serverPort = 1000 + int(value)
            clientSocket = socket(AF_INET, SOCK_STREAM)
            clientSocket.connect((serverName, serverPort))
            clientSocket.send(clientResponse.encode())
            result = clientSocket.recv(1024).decode()
            current_dvdict = dataAnalyzer(result,current_node, current_dvdict)

    # The response that gets sent to the main program ==> project2.py
    output= current_node+' '+str(priority)+' '
    for key, value in current_dvdict.items():
        node= key.replace(current_node+'-','')
        output+= node +' '+str(current_dvdict[key])+' '

    # by printing, the response is sent to the main process
    print(output)



