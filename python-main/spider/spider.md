| 操作符 | 说明 | 符号|
|---|---|---|
|.|标识单个字符||
|[]|字符集，对单个字符给出范围|[a,b,c]表示a或者b或者c，[a-z]表示a到z的单个字符|
|[^]|非字符集，对单个字符给出排除范围|[^abc]表示任意非a，非b，非c的单个字符|
|*|前一个字符0次或者无限次扩充|abc\* 代表ab或者abcc或者abccc等等|
|+|前一个字符1次或者无限次扩充|abc+ 代表abc或者abcc或者等等|
|?| 前一个字符0次或者1次扩充 |abc?表示abc或者ab|
|\|| 左右表达式任意一个| abc\|def 表示abc或者def|
|{m}| 扩展前一个字符m次|ab{2}c 表示abbc|
|{m,n}| 扩展前一个字符[m,n]次 | ab{1,2}c表示abc或者abbc|
|^| 匹配字符串开头 | ^abc表示abc且在一个字符串开头|
|$|匹配字符串结尾| $abc表示abc且在一个字符串结尾|
|()|分组标记，内部只能使用\|操作符号 |(abc)表示abc，(abc\|def)表示abc，def|
|\d|数字，等价于[0-9]||
|\w | 单词，等价于[A-Za-z0-9_]||