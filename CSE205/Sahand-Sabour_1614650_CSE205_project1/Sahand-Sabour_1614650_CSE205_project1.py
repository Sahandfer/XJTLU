from socket import *
import re
import os
import ssl
import threading

print('<-------------------Program started------------------->')
# As a user, you can change your desired URL and depth from here
# Make sure to include either http:// or https:// at the beginning of the entered URL.
# Also, there are no spaces in a valid URL

userUrl='http://csse.xjtlu.edu.cn/classes/CSE205/'

# The following URLs were additional test cases for this program
# userUrl='localhost/CSE205/'
# userUrl='https://sahandfer.github.io/assignment/'

userDepth= int(input("Please input the desired depth: "))
if(userDepth==''):
    userDepth=5



port = 80
# A list for the hosts that can be accessed via http requests
hosts_http=[]
# A list for the hosts that can be accessed via http requests
hosts_https=[]


host=''
sub=''

if ('http://' in userUrl):
    userUrl= userUrl.replace('http://','')
    port= 80
elif ('https://' in userUrl):
    userUrl = userUrl.replace('https://', '')
    port = 443

if('/'in userUrl):
    sections= userUrl.split('/')
    host= sections[0]
    for i in range(1,len(sections)):
        sub+=sections[i]
        if(i!=len(sections)-1 ):
            if(sections[i+1]!=''):
                sub+='/'

if(port==80):
    hosts_http.append(host)
else:
    hosts_https.append(host)

# A dictionary for showing the levels of the given URL
depthDict = {}
# A list to store all the already visited links
used = [host+'/'+sub+'/']
depthDict[0] = [host+'/'+sub+'/']


# For creating a list for each level of the depth that stores the links on that depth
for i in range(1, userDepth+2):
    depthDict[i] = []


# This function returns the response (could be HTML, image, etc.)
def getContent(new_host, sub):
    print('=========================================================================')
    print('Host ==> ' + new_host)
    clientSocket = socket(AF_INET, SOCK_STREAM)
    if (sub != ''):
        print('Path ==> ' + sub)
    if (new_host in hosts_http):
        clientSocket = socket(AF_INET, SOCK_STREAM)
        clientSocket.connect((new_host, 80))
    elif (new_host in hosts_https):
        temp_socket= socket(AF_INET, SOCK_STREAM)
        clientSocket= ssl.wrap_socket(temp_socket)
        clientSocket.connect((new_host, 443))

    result = b''

    getUrl = 'GET /' + sub + ' HTTP/1.1\r\nHost: ' + new_host + ' \r\nConnection: close\r\n\r\n'
    getUrl = getUrl.encode()
    clientSocket.send(getUrl)

    while True:
        receive= clientSocket.recv(1024)
        result += receive
        if not (receive): break

    header, content= result.split(b'\r\n\r\n')
    clientSocket.close()

    #print('Response ==> Collected')
    print('=========================================================================')
    return (header.decode(), content)

# This function finds all of the images on a given link (Using Regex) and returns them collectively as a list
def findImages(link):
    # when the host is the main page
    if not ('/' in link):
        this_host= link
        this_path =''

    else:
        sections = link.split('/')
        this_host = sections[0]
        this_path = ''
        for i in range(1, len(sections)):
            this_path+=sections[i]+'/'

        if('//' in this_path):
            this_path= this_path.replace('//','/')

    header, content = getContent(this_host, this_path)
    content= content.decode()
    imagePattern = "<img\s[^>]*?src\s*=\s*['\"]([^'\"]*?)['\"][^>]*?>"
    imageList= re.findall(imagePattern, content)
    return imageList


# This function is for separating the image name from its path, and it returns the name for the image file
def getImgName(path):
    if('/' in path):
        imgName= path.split('/')
        imgName= imgName[-1]
    else:
        imgName= path
    return imgName


# This function downloads and saves all the images on a given link
def downloadImages(link):
    if (link[-1] != '/'):
        link += '/'

    imageList = findImages(link)
    for image in imageList:
        current_host, current_sub = separator(link)

        # in different directory
        if (image[0] == '/'):

            img_header, img_content = getContent(current_host, image)
            img_path = current_host + '/' + current_sub + getImgName(image)
        # in another host
        elif ('http' in image):


            if(('http://' in image)):
                image = image.replace('http://', '')
                new_host, new_sub = separator(image)
                if not (new_host in hosts_http):
                    hosts_http.append(new_host)
            elif(('https://' in image)):
                image = image.replace('https://', '')
                new_host, new_sub = separator(image)
                if not (new_host in hosts_https):
                    hosts_https.append(new_host)


            img_header, img_content = getContent(new_host, new_sub[:-1])
            img_path = current_host + '/' + current_sub + getImgName(image)
        # in the same directory
        else:
            img_header, img_content = getContent(current_host, current_sub + image)
            img_path = current_host + '/' + current_sub + getImgName(image)

        if ('HTTP/1.1 200 OK' in img_header):
            myFile = open(img_path, 'wb')
            myFile.write(img_content)
            myFile.close()


# This function separates the host and the path(sub) from one another.
# This is extremely useful for the way the algorithm works
def separator(href):
    sections = href.split('/')
    this_host = sections[0]
    this_sub = ''
    for i in range(1, len(sections)):
        this_sub += sections[i] + '/'
    if ('//' in this_sub):
        this_sub = this_sub.replace('//', '/')
    result=[this_host,this_sub]
    return result


# This function gets all the hyperlinks in a given link and returns them collectively as a list
def getLinks(href):
    result= separator(href)
    header, content= getContent(result[0], result[1])
    content= content.decode()
    hrefPattern = "<a\s[^>]*?href\s*=\s*['\"]([^'\"]*?)['\"][^>]*?>"
    hrefList = re.findall(hrefPattern, content)
    return hrefList


# for each level in the deepness scale, we go through each link and analyze it for hyperlinks and images
for depth in range(1, userDepth+2):

    # a list of hyperlinks in the previous depth level
    prev_hrefs = depthDict[depth - 1]

    # for each hyperlink in the previous depth
    for prev_href in prev_hrefs:

        # Firstly, create the required directory is it doesn't already exists
        if not (os.path.isdir(prev_href)):
            print('Creating directory: ' + prev_href)
            os.makedirs(prev_href)

        new_host, new_sub = separator(prev_href)

        # This part was used for testing the application threading but was not successful
        # Therefore it was commented out from the application
        # thread= threading.Thread(target=downloadImages, args=(prev_href,))
        # thread.start()

        downloadImages(prev_href)

        # Hyperlinks in the new depth
        new_hrefs = getLinks(prev_href)

        # For each hyperlink in the current depth level
        for new_href in new_hrefs:

            # If it starts with a slash
            if (new_href[0] == '/'):
                href = new_host + new_href
                if (href[-1] != '/'):
                    href += '/'
                if not (href in used):
                    used.append(href)
                    depthDict[depth].append(href)

            # if it links to another website
            elif ('http' in new_href):
                if('http://' in new_href):
                    href = new_href.replace('http://', '')
                    if not (new_host in hosts_http):
                        hosts_http.append(new_host)
                elif('https://' in new_href):
                    ref = new_href.replace('https://', '')
                    if not (new_host in hosts_https):
                        hosts_https.append(new_host)
                if not (href in used):
                    used.append(href)
                    depthDict[depth].append(href)

            # if it has no slash and no http
            else:
                href = prev_href + new_href
                if (href[-1] != '/'):
                    href += '/'
                if not (href in used):
                    used.append(href)
                    depthDict[depth].append(href)


visited_depth=0
# for printing out each depth level with its corresponding links
for i in range(len(depthDict)):
    if(depthDict[i]) and i!=userDepth+1:
        print('------------------------------------------------')
        print('Depth:' + str(i))
        for item in depthDict[i]:
            print(item)
        print('------------------------------------------------')
        visited_depth+=1

# In case the user specifies a depth level which is more (deeper) than the deepest possible level
if(visited_depth<=userDepth):
    print('+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++')
    print('Note ==> The requested depth could not be reached! The given URL was not deep enough')
    print('+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++')

print('<-------------------End of program------------------->')