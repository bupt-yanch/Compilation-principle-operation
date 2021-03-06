## 实验内容
用c++语言实现对c/c++源程序的词法分析。通过扫描源程序，输出对应记号流的同时对字符表进行管理，在遇到错误时报告错误所在位置并跳过。扫描时记录各类符号的数量并在扫描完成后输出。

## 环境
Win10 + Visual studio 2015

## 主要函数

### 1. double transfer(char \*aim, int len)

传入一个字符串以及其长度，返回字符串对应的无符号数

### 2. void InputBuffer(int i)

传入参数决定更新哪块缓冲区，并因此改变读头，填充时在最后放置EOF


### 3. void ScanCode(void);//扫描源程序

本部分根据课上讲解的自动机改进，使其有识别注释和错误的能力。具体操作如下

每次根据读头（readptr）和偏移从缓冲区读入一个字符，先判断是否为EOF，若是EOF则判断需要更新缓冲区或已读完文件，若读完文件则需要处理最后一个字符后再退出。如果读入字符非EOF，则根据状态和字符属性来进行各种状态转移。

其中重要的是
- 标识符部分，在得到一个标识符后需要先扫描关键字表判断是否是关键字，若不是关键字，再扫描字符表判断该标识符是否需要被记录。本程序中关键字数量仅3个也是为了方便，若要增加关键字仅需要修改宏定义以及构造函数即可。
- 无符号数部分，在得到一个确定的表示一个无符号数的字符串后，调用transfer函数将其变为double类型。关键在于如何确定这个字符串，由于该字符串中可能含有“.”,”E”等字符，为了确定它我使用了一系列状态。
- 错误处理，当自动机判断出错且进入到错误状态时，错误位置被记录且立刻进入到下一个状态SKIP，在SKIP状态下，读入任何字符都会被跳过，直到读入空格或回车，状态才会被恢复到初始状态。


## 运行结果
```
为了方便调试，我将标识符记号的二元组 <ID, 指向存储单元的指针> 
改成了三元组 <ID,	真实标识符, 指针>
```

### 1. 先进行一段简单的小代码

打开的文件是桌面的一个文本文件，其中源代码如下

[![REtCuR.png](https://z3.ax1x.com/2021/06/21/REtCuR.png)](https://imgtu.com/i/REtCuR)

运行结果如下

[![REt5a6.png](https://z3.ax1x.com/2021/06/21/REt5a6.png)](https://imgtu.com/i/REt5a6)

### 2. 将本程序的一段带有注释的代码做测试

代码如下

[![REtOsA.md.png](https://z3.ax1x.com/2021/06/21/REtOsA.md.png)](https://imgtu.com/i/REtOsA)

运行结果如下。
输出的记号过多，我们只关心最后的统计数据

[![RENniT.md.png](https://z3.ax1x.com/2021/06/21/RENniT.md.png)](https://imgtu.com/i/RENniT)

### 3. 写一段错误程序测试

[![RENYo6.png](https://z3.ax1x.com/2021/06/21/RENYo6.png)](https://imgtu.com/i/RENYo6)

运行结果如下

[![RENwSe.md.png](https://z3.ax1x.com/2021/06/21/RENwSe.md.png)](https://imgtu.com/i/RENwSe)


## 总结

### 1. 根据上面程序的运行结果我进行了检查，发现一切运行正确，报错误的两个范例的检查结果如下

1. 如上面运行示例2是因为字符“！”和“=”没有在此词法分析器内定义，反映出该词法分析器对于未知	字符的反应良好。
2. 示例三中特意加入了一些错误，可看出其对于无符号数的一些错误反应良好，且对于注释的处理也正确。
3. 之所以赋值号个数一直为0是因为”:=”没有出现。。

### 2. 该词法分析器也有一些应该改进的地方如下
（1）收录的关键字少、标点符号少。

（2）标识符中应该可以包含下划线。

（3）存在这样的问题 读入字符串9F时 按照一般规则是应该报错的，但上课讲的自动机案例忽略了这一点，它会识别为两个记号<num,9> 和 <ID,--> 在写完后才发现本词法分析器也存在这个问题。。

（4）对于真正编译词法分析的时候，扫描到#include的时候应该将该行跳过并替换为相应库代码，而本词法分析器避开了这个问题，在测试的时候也没使用包含#include部分的源代码。


