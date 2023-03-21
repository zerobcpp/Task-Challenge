import urllib.request as req
import requests
import hashlib

def browers():
    agent = {'User-Agent': '#/8.8'}
    response = requests.get(url='#/browser', headers=agent)
    print(response.json())

def generateString():
    # REFRACTED, THIS IS A SIMPLE MATH PROBLEM
    file = open('7letters.txt', 'r+')
    resFile = open('res.txt', 'w+')
    s = file.read()
    s = s.split('\n')
    n = 0
    for i in s:
        res = 0
        for c in i:
            res += ord(c) - ord('a')
            print(res)

        if res == 42:
            resFile.write(i+'\n')
            print(i)

def sendRequest():
    file = open('res.txt', 'r+')
    s = file.read()
    s = s.split('\n')
    for i in s:
        link = f'#/xception?q={i}'
        response = req.urlopen(link)
        if 'raise' not in response.read().decode('utf-8'):
            print(i)
        print()

def hashQ():
    file = open('hash.txt', 'r+')
    s = file.read()
    s = s.split(':')
    res = s[0]
    salt = s[1]
    strings = open('7letters.txt', 'r+')
    letters = strings.read().split('\n')

    print(res)
    for i in letters:
        flag = i + salt

        m = hashlib.md5(flag.encode('UTF-8'))
        # bug - m.udpate(i) = i + i + i + i
        if i == 'caliber':
            print(flag, i, salt)
            print(m.hexdigest())

        if res == m.hexdigest():
            print('found', flag, i)


def stream():
    link = '#/stream'
    i = 0
    c = {}
    while i < 120:
        response = req.urlopen(link)
        word = response.read().decode('utf-8').strip()
        print(word)
        c[word] = c.get(word, 0) + 1
        i += 1

    print(c)



#generateString()
#browers()
#sendRequest()
hashQ()
#stream()