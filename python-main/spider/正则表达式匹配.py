import urllib.request,urllib.error
from bs4 import BeautifulSoup as bs
import re

head = {
    "user-agent": "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/94.0.4606.71 Safari/537.36"
}
requestWeb = urllib.request.Request(url="https://cn.bing.com/images/search?q=%E6%A0%A1%E8%8A%B1&qs=n&form=QBILPG&sp=-1&sc=3-0&cvid=0237EAC7A79D480CBD9210D5DE277AB8&first=1&tsc=ImageBasicHover",headers=head)
code = urllib.request.urlopen(requestWeb).read()
# print(code)
code = bs(code,"html.parser",from_encoding='utf-8')
# print(code)
imglist = []
a = 0
for i in code.find_all('img'):
    l = i.attrs
#     # imglist.append(i.attrs)
#     l = i.attrs
    if 'src' in l:
        urllib.request.urlretrieve(str(l['src']),'/home/tmd/Desktop/' + str(a) + '.jpg')
        a = a + 1
    if 'data-src' in l:
        urllib.request.urlretrieve(str(l['data-src']),'/home/tmd/Desktop/' + str(a) + '.jpg')
        a += 1
#     # print(i)

# for i in imglist:
#     print(i)

# urllib.request.urlretrieve("https://tse4-mm.cn.bing.net/th/id/OIP-C.bZLHjeLWrQn49H26TxDmEAHaLA?w=182&h=270&c=7&r=0&o=5&pid=1.7","/home/tmd/Desktop/a.jpeg")
