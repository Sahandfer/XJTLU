"""
CSE205_project2
Name ==> Sahand Sabour
Student ID ==> 1614650
"""


import sys
import subprocess
import multiprocessing


# This function gets the name of the file and returns a dictionary of nodes
def getNodes(filename):
    myfile= open(filename, 'r')
    content= myfile.read()
    nodeDict={}
    nodes=[]
    lines= content.split('\n')
    index=''
    for i in range(len(lines)):
        if('Node' in lines[i]):
            temp= lines[i].replace('Node ','')
            if not (temp in nodes):
                nodes.append(temp)
            index= str(temp)
        else:
            if(lines[i]!=''):
                node, price=lines[i].split('\t')
                nodeDict[index + '-' + node] = int(price)
                nodeDict[node + '-' + index]=int(price)
                if not (node in nodes):
                    nodes.append(node)
    return nodeDict,nodes


# This function returns all the nodes that are connected to the given node
def findConnected(node,nodeDict):
    results=[]
    for key in nodeDict.keys():
        if (node in key):
            result= key.replace(node, '').replace('-','')
            if not (result in results):
                results.append(result)
    return results


# This function finds the minimum price between the starting node and the remaining unused nodes
def findMinPrice(startingNode, dvDict, usednodes):
    price = float('+inf')
    for key, value in dvDict.items():
        if (startingNode+'-' in key):
            if (float(value) <= price) and (key.replace(startingNode+'-','') not in usednodes):
                price= value
    return price


# This function finds the node that currently has the shortest path and hasn't been used
def findShortestPath(startingNode, dvDict, usednodes):
    min_price= findMinPrice(startingNode, dvDict, usednodes)
    result= ''
    for key,value in dvDict.items():
        if (startingNode + '-' in key) and (value == min_price) and  (key.replace(startingNode+'-','') not in usednodes):
            result=key.replace(startingNode+'-','')
    return result


# This function implements the dijkstra's algorithm and finds the solution
def dijkstra(filename, starting_Node):

    nodeDict, nodes = getNodes(filename)
    # in case it is not mentioned in the arguments what the starting node is
    if(starting_Node==''):
        starting_Node= nodes[0]

    usedNodes=[starting_Node]
    paths={}

    # Initialization
    dvDict={}
    for node in nodes:
        if(node!= starting_Node):
            if (starting_Node + '-' + node in nodeDict.keys()):
                dvDict[starting_Node + '-' + node] = nodeDict[starting_Node + '-' + node]
            else:
                dvDict[starting_Node + '-' + node] = float('+inf')
            paths[node]=starting_Node+' --> '+node

    #print(dvDict)

    while set(usedNodes) != set(nodes):
        shortest = findShortestPath(starting_Node, dvDict, usedNodes)
        usedNodes.append(shortest)

        connectedNodes = findConnected(shortest, nodeDict)
        dvDict_new = {}
        # Getting dictionary for new prices
        for node in nodes:
            if (node != shortest) and (node !=starting_Node):
                if (shortest + '-' + node in nodeDict.keys()):
                    dvDict_new[shortest + '-' + node] = nodeDict[shortest + '-' + node]
                else:
                    dvDict_new[shortest + '-' + node] = float('+inf')

                # Update DV for all nodes adjacent to shortest node that are not used
                old_price = dvDict[starting_Node + '-' + node]
                new_price = dvDict[starting_Node + '-' + shortest]+dvDict_new[shortest + '-' + node]
                price= min(old_price, new_price)
                if (price == new_price):
                    paths[node]= paths[shortest]+ ' --> '+node
                dvDict[starting_Node + '-' + node]= price

    #print(dvDict)
    dijkstraFile(dvDict,paths)


# This function outputs the result of the dijkstra's algorithm to a file
def dijkstraFile(dvDict, paths):
    myFile = open('Dijkstras\'s Result.txt', 'w')
    myFile.write('\n'+str.center('<Start>', 80, '=')+'\n\n')
    myFile.write('Source\tDestination\tMinimum cost\tShortest path\n')
    for key, value in dvDict.items():
        start, node = key.split('-')
        starting_Node = start
        price = str(value)
        path = paths[node]
        myFile.write(str.center(start,6,' ')+'\t'+str.center(node, 11,' ')+'\t'+str.center(price, 12,' ')+'\t'+path+'\n')

    myFile.write('\n' + str.ljust('', 80,'-') + '\n')
    starting_Node=' '
    for key, value in dvDict.items():
        start, node= key.split('-')
        starting_Node= start
        price= str(value)
        path= paths[node]
        myFile.write('\nThe shortest path from '+start+ ' to '+node+' costs '+price+'!\n')
        myFile.write('The corresponding path: '+path +'\n\n')

    myFile.write(str.center('<End>', 80, '='))

    myFile.close()
    print('Dijkstra\'s result for starting node '+starting_Node+' written to text file!\n')


# This function gets the dv dict for each node
def getNodedict(node, nodeDict):
    result={}
    result[node + '-' + node] = 0
    for key, value in nodeDict.items():
        if (node+'-' in key):
            result[key]= value
    return result


# This function runs a subprocess and gets the result
def runProcess(script):
    result= subprocess.check_output(sys.executable+' {}'.format(script), shell=True)
    return (result.decode())


# This function produces a list of scripts that needs to be run (necessary sub-processes)
def getScripts(dvDict_dict, nodes, current, priorityDict):
    scripts = []
    # all the nodes
    for node in nodes:
        priority = priorityDict[node]
        dvDict_node = dvDict_dict[node]

        # If it's not the last node
        if (priority != len(priorityDict.keys()) - 1):
            client_script = 'client.py ' + node + ' ' + str(priority) + ' '
            for key, value in dvDict_node.items():
                here, dest = key.split('-')
                node_priority = nodes.index(dest)
                client_script += dest + ' ' + str(value) + ' ' + str(node_priority) + ' '
            client_script = client_script.strip()
            scripts.append(client_script)

        # If it's not the first node
        if (priority != 0):
                server_script = 'server.py ' + node + ' ' + str(priority) + ' '
                for key, value in dvDict_node.items():
                    here, dest = key.split('-')
                    node_priority = nodes.index(dest)
                    server_script += dest + ' ' + str(value) + ' '+str(node_priority)+' '
                server_script= server_script.strip()
                scripts.append(server_script)
    return scripts


# This function compares the old and new values for dv dictionaries and updates them accordingly
def updateDvdicts(dvDict_dict, results, current):
    # new list of current situation for each node
    changed=current
    # new dictionary of dvdict for each node
    dvDict_dict_new={}
    for result in results:
        result= result.replace('\n','')
        sections= result.split(' ')
        current_node= sections[0]
        priority= int(sections[1])-1
        dvDict_old= dvDict_dict[current_node]
        dvDict_new={}
        for i in range(2, len(sections)-1, 2):
            key = current_node + '-' + sections[i]
            dvDict_new[key]= int(sections[i+1])

        # if the dv dict hasn't changed
        if (dvDict_old == dvDict_new):
            if (changed[priority] == False):
                changed[priority] = True

        # if the dv dict has changed
        else:
            if (changed[priority] == True):
                changed[priority] = False


        dvDict_result=dvDict_old
        # updating the dv dict
        for key, value in dvDict_new.items():
            if(key in dvDict_old.keys()):
                if(dvDict_new[key]<dvDict_old[key]):
                    dvDict_result[key]= value
            else:
                dvDict_result[key]= value

        dvDict_dict_new[current_node] = dvDict_result

    return dvDict_dict_new, changed


# This function implements the Bellman-Ford algorithm and finds the solution
def bell_man(filename):
    nodeDict, nodes = getNodes(filename)
    dvDict_dict = {}
    priority_dict={}
    processNum= (len(nodes)*2)-2
    current = []
    for i in range(len(nodes)):
        current.append(False)
    for node in nodes:
        dvDict_dict[node] = getNodedict(node, nodeDict)
        priority_dict[node]= nodes.index(node)
    iterationNum=1
    while (False in current):
        #print('===================================================================================================')
        scripts = getScripts(dvDict_dict, nodes, current, priority_dict)
        pool = multiprocessing.Pool(processNum)
        results = pool.map(runProcess, scripts)
        #print(results)
        dvDict_dict, current = updateDvdicts(dvDict_dict, results, current)
        #print(dvDict_dict)
        #print(current)
        print('iteration '+str(iterationNum)+' has been completed')
        iterationNum+=1
        #print('===================================================================================================')
    print('The dv tables converged after '+str(iterationNum-1)+ ' iterations!')
    bell_manFile(dvDict_dict)


# This function outputs the result of the Bellman-Ford algorithm to the corresponding files
def bell_manFile(dvDict_dict):
    for node, nodedict in dvDict_dict.items():
        myFile = open('Bellman-Ford\'s Result for Node ' + node + '.txt', 'w')
        myFile.write('\n' + str.center('<Start>', 80, '=')+'\n\n')
        myFile.write('Source\tDestination\tMinimum cost\n')
        for key, value in nodedict.items():
            start, node = key.split('-')
            price = str(value)
            myFile.write(str.center(start, 6, ' ') + '\t' + str.center(node, 11, ' ') + '\t' + str.center(price, 12, ' ') + '\n')

        myFile.write('\n' + str.ljust('', 80, '-') + '\n')
        for key, value in nodedict.items():
            start, node = key.split('-')
            price = str(value)
            myFile.write('\nThe shortest path from ' + start + ' to ' + node + ' costs ' + price + '!\n')
            myFile.write('min(' + key + ') ==> ' + price + '\n')

        myFile.write('\n'+str.center('<End>', 82, '='))
        myFile.close()

    print('Bellman-Fords\'results were written to their corresponding text files!')

if __name__ == '__main__':
    print('---Program has started!\n')
    # to get the arguments passed to the program by the command line
    arguments= sys.argv
    # the name of the file used for the program is the second index in the arguments' list
    filename= arguments[1]
    # the node to start the dijkstra's algorithm from can be the third index in the arguments' list (optional)
    if (len(arguments)>2):
        starting_Node= arguments[2]
    # if the starting node is not mentioned, then the first node that is read from the file is the starting node
    else:
        starting_Node = ''

    # This performs the dijkstra's algorithm on the file and outputs the result to a file
    dijkstra(filename, starting_Node)
    # This performs the bellman ford algorithm on the file and outputs the corresponding files
    bell_man(filename)


    print('\nProgram has ended!---')
