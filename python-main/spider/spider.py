'''
if you need open some web, and use spider to got someting data,you can use
    import urllib.request
to import package,so you can request this web,and if you want to open some web,you can use this function
    urllib.request.urlopen(path)
we know web is HTML code,it has different encode(编码)，so we need this code encode before we get this code
we can use this function：
    urllib.requset.urlopen(path).decode('utf-8')
to revise this decode,and use 'utf-8' to open this HTML code

we need a brower's request head to let brower think I am a people,not a spider
we can use this function
    urllib.request.urlopen(path).gethearders()
to get the header of your computer normal request header，so the brower think you are a people not a spider
and used map to storage,so you can use function:
    urllib.request.urlopen(path).gethearder(name)
to look value that key that is name

you need push this head in to your request, so you can use this function to implement(实现) this:
    urllib.request.Request(url,headers)
url is you web url, headers is your spider disguise(伪装), you need get normal request head

and use normal function to request:
    urllib.request.urlopen( urllib.request.Request(url,header) )

you used decode("gb2312") wrong, you need let gb2312 to GBK or GB18030
'''
import re
from bs4 import BeautifulSoup as bs  # 网页解析 获取数据
import openpyxl   # 操作excel表
import urllib.request,urllib.error # 制定URL，获取网页数据

def openUrl(url:str) -> str:
    # 爬取源码
    my_url = url
    head = {
        "user-agent": "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/94.0.4606.71 Safari/537.36"
    }
    url_request = urllib.request.Request(url=my_url,headers=head)
    try:
        my_request = urllib.request.urlopen(url_request)
        # return my_request.read().decode("utf-8")
        return my_request.read().decode("gb2312")
    except urllib.error.HTTPError:
        print("HTTP errer")
    except urllib.error.URLError:
        print('URL errer')

def saveInFile(file:str,data:str):
    with open(file,'w') as file:
        file.write(data)

def spider():
    with open("/home/tmd/Desktop/a.html",'rb') as file:
        html_tree = bs(file.read(),'html.parser',from_encoding='utf-8')
    # print(html_tree.a)
    # print(html_tree.a.string)
    # print(html_tree.a.attrs)  # map to have anything value
    # print(html_tree.head.contents[8]) # get all of a in this html_tree
    # 字符串过滤，将所有匹配的全部过滤,必须完全相等后才可以
    # print(html_tree.find_all('a')[20])
    # 正则表达式过滤，标签及其内容中含有a 携带a的均被查找出来,像head，meta等均被包括
    # print(html_tree.find_all(re.compile('a'))[1])
    # # 靠属性进行查询
    # print(html_tree.find_all(id='head'))
    # 按照css形式进行查找
    # print(html_tree.select("a")[4])
    # 复杂查询 a标签下的class的属性值为。。。的标签返回
    # print(html_tree.select("a[class='bir']"))
    # 获得text
    # print(html_tree.select("div > a")[2].get_text())

    #正则表达式的运用
    #正则表达式，用来校验其他的字符串
    # word = re.compile("AA")
    # #验证的字符串
    # print(word.search("AAjflsjfAAfsjfAA")) #第一个匹配的

    # #或者之间进行也可以
    # print(re.search("AA", "ssAAss")) #前面的正则表达式，后面是被匹配的字符串

    # #可以使用其他函数
    # print(re.findall("[A-Z]", "aAfslfdsalFlefFPWLfsljf")) 
    # #查找替换
    # print(re.sub('a','A','afdasflkjflasdadsas')) #从第三个参数中查找第一个参数，然后用第二个参数进行替换
    HTML_a = html_tree.find_all("a")
    # for i in HTML_a:
    #     print(i.get_text())
    HTML_id = html_tree.select('.s-bottom-layer-content > .lh')
    # print(HTML_id[0].get_text())
    for i in HTML_id:
        print(i.get_text())

def test():
    path = "http://www.zuowen.com/e/20190817/5d57705b729ff.shtml"
    head = {
        "User-Agent": "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/94.0.4606.71 Safari/537.36"
    }
    web_request = urllib.request.Request(url=path,headers=head)
    return urllib.request.urlopen(web_request).read().decode("gb2312")

def main():

    # htmlCode = openUrl("http://www.baidu.com")
    # saveInFile("/home/tmd/Desktop/a.html",htmlCode)
    # spider()
    # html = openUrl("http://www.zuowen.com/e/20190817/5d57705b729ff.shtml")
    # # print(html)
    # saveInFile("/home/tmd/Desktop/a.html", html)
    # with open("/home/tmd/Desktop/a.html") as file:
    #     html_tree = bs(file.read(),'html.parser',from_encoding='gb2312')
    # print(HTML)
    # with open ("/home/tmd/Desktop/a.html",'rb') as file:
    #     html = bs(file.read(),"html.parser",from_encoding='gb2312')
    #     # print(html)
    #     print(html.select('.con_content')[0].get_text())
    # head = {
    #     "User-Agent": "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/94.0.4606.71 Safari/537"
    # }
    # web = urllib.request.Request(headers=head,url = "http://www.zuowen.com/")
    # html = urllib.request.urlopen(web).read().decode("GBK")
    url_list = []
    with open("/home/tmd/Desktop/a.html","r") as file:
        code = bs(file.read(),'html.parser')
        # print(code)
        code_list = code.select(".i_con1_m_con > ul > li > a")
        # print(code_list)
        head = {
            "User-Agent": "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/94.0.4606.71 Safari/537.36"
        }
        for point in code_list:
            url_list.append(point.attrs['href'])
        a = 1
        for i in url_list:
            if a % 2 == 0:
                test = ""
                url = urllib.request.Request(url=i,headers=head)
                url_ = urllib.request.urlopen(url)
                code = bs(url_.read(),"html.parser",from_encoding="GBK")
                try:
                    test = "标题：" + code.select('.h_title')[0].get_text() + "\n"
                    passage = code.select(".con_content > p")
                    for j in passage:
                        test += j.get_text()
                    with open("/home/tmd/Desktop/passage.txt",'a') as file:
                        file.write(test)
                        file.write("\n\n\n\n\n\n")
                except IndexError:
                    print("this web was not passage")
            a += 1    
        # file.write(html)
# test()
main()
