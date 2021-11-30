## <center> shell脚本 ##
- #! 每个程序起始都会有这个符号，告知操作系统，执行脚本所需要的解释器名字。
- \#	注释
- 变量名后需要直接跟等于 即a=1 和 a = 1不同
- 特性
  - 获得字符串长度
	```bash
		var= 12345
		echo ${#vsr}
		# printf 5
	```
  - 
	```bash
	echo $SHELL
	# printf /bin/bash	
	if (($UID == 0)); then 
	# [$UID == 0 ]; then
		echo "Run in root"
	else 
		echo "Please run in root"
	fi
	```
- 变量和常量：
	- 在shell中，类似python的弱类型，直接赋值即可。
	- 变量赋值，变量赋值运算符与变量之间不允许有空格
	- 引用变量：
		```bash
		a=12
		b=$((11 + $a))	#算术扩展 + 引用
		```
	- $0 为第一个默认参数
	```bash
	# b.sh
	echo $0

	# ./bash
	# printf ./b.sh
	```
	- $1是第一个参数
		```bash
		a=$1
		echo $a
		# ./a.sh 12
		# printf 12
		```
- 数学计算
  	- let 后直接进行运算，不需要在变量名前添加$<br>
	- 支持自加自减运算，支持+=和-=
	- 操作符[]的使用方式和let一样
	```bash
		#!/bin/bash
		n2=4
		n1=3
		let n=n1+n2
		echo $n
		echo $[n1+n2]
		#printf
		# 7
		# 7
	```
- bc
  - > &emsp;&emsp;bc是一个数学运算的实用高级工具，包含大量选项，可以借助它执行浮点数运算并使用一些高级函数。
	```bash
	echo "4 * 0.56" | bc   
	# printf 2.24
	```
  - 参数
    - scale 小数精度，即小数位数
	```bash
	echo "scale=2;22/7" | bc
	#print 3.14
	```
  - 进制转换
    - ibase用于设置输入数据的进制
	- obase用于输出的数据进制
	```bash
	echo  "obase=10;ibase = 1;10" | bc
	# prinf 2
	```
- 反引号``,单引号''和双引号
	1. 反引号``
	>&emsp;&emsp;反引号是命令替换，将里面的内容暂存，在合适的位置输出
	```bash
	ret=`ls -a`
	echo "12sdfa"
	echo $ret
	#print 12sdfa
	#print . .. 51 51.md 辅助程序 硬件知识 java KST-51-1.pdf linux.txt shell shell.md .vscode
	```
	2. 单引号‘’
	>&emsp;&emsp;被单引号圈起来的指令，被认为纯字符。
	```bash
	n1=12
	echo '$n1'
	# print n1
	```	
	3. 双引号“”
	>&emsp;&emsp;被双引号圈起来的指令，可以有转义字符，就是会有一些特殊功能的字符。
	```bash
	n1=12
	echo '$n1'
	# print 12
	```
	4. 单双引号的相同点
	>&emsp;&emsp; 都可以把空格包含在里面
- 文件描述符
	>&emsp;&emsp;文件描述符是与某个打开的文件或数据流相关联的整数。文件描述符0、1以及2是系统预留的。
  - 0 —— stdin （标准输入）。
  - 1 —— stdout（标准输出）。
    - 使用>将文本保存到文件中
    - 使用>>将文本追加到文件中
    - 使用cat 查看文件内容
  - 2 —— stderr（标准错误）。
	```bash
	ls +
	#print ls: 无法访问 '+': 没有那个文件或目录

	ls + > a.txt
	#也不会任何数据被输入到a.txt中，因为标准错误默认只会提醒能错了，而不会把错误信息输入到该文本中。

	ls + 2> a.txt
	# less a.txt
	#print ls: 无法访问 '+': 没有那个文件或目录
	```