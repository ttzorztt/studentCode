from bs4 import BeautifulSoup as bs
import re
import urllib.request

def spiderPassage(indexUrl:str,savePath:str):
    url_list = []
    head = {
        "User-Agent": "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/94.0.4606.71 Safari/537.36"
    }
    request = urllib.request.Request(url=indexUrl,headers=head)
    index = urllib.request.urlopen(request)
    indexCode = bs(index.read(),'html.parser',from_encoding='GBK')
    code_list = indexCode.find_all("a")
    print(code_list)
    try:
        for point in code_list:
            url_list.append(point.attrs['href'])
    except KeyError:
        print("no herf")
    with open("/home/tmd/Desktop/touch aaa.txt") as file:
        file.write(code_list)
    a = 1
    print(len(url_list))
    for i in url_list:
        test = ""
        url = urllib.request.Request(url=i,headers=head)
        url_ = urllib.request.urlopen(url)
        code = bs(url_.read(),"html.parser",from_encoding="GBK")
        try:
            test = "标题：" + code.select('.h_title')[0].get_text() + "\n"
            passage = code.select(".con_content > p")
            for j in passage:
                test += j.get_text()
            with open(savePath,'a') as file:
                file.write(test + '\n')
            print("收录标题 " + code.select('.h_title')[0].get_text())
        except IndexError:
            print("this web not has passage")
spiderPassage("http://www.zuowen.com/", "/home/tmd/Desktop/passage.txt")