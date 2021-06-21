## Overall
这里的词法分析.h 以及词法分析函数.h都是将之前写过的词法分析器进行一些改造然后复制过来的，这里不再赘述，主要展示语义分析部分。

## 实验目的
手工编写语义分析程序，其中要实现对算术表达式的类型检查和求值，且使用自底向上的语法制导翻译技术实现对表达式的分析和翻译。

## 环境
Win10 + Visual studio 2015

## 算法思路
1. 在构造完LR分析表和语法制导翻译方案的基础上，只需要再编写分析控制程序、改造分析栈、就可以很简单地完成分析和翻译的过程了。具体地，程序中实现如下
```
// 构造LR分析表
typedef struct act1 {
	char act; //记录S(移进) or L(规约)
	int state; //记录转到的状态 or 用第几个产生式规约
};
struct act1 action[17][9];//LR分析中的Action表
int Goto[17][3];

// 改造分析栈
float state[100][3];//assume stack maxlen = 100 ；3个参数分别表示状态、类型、数值
```
2. 这里我采用之前写过的词法分析器来解析算术表达式并为之后的语法和语义分析提供符号流输入。

```
// 词法分析提供输入记号流
typedef struct r {
	string type;
	float num;
}record;
record opstream[MaxL];

A = new Lexical_Analysis(1);
Clen = A->ScanCode(opstream);
```
把每个记号存为一个record。这里在语义分析的构造函数中创建了一个词法分析器并通过调用词法分析器的方法将记号流读入。(Clen记录了记号流的长度，opstream数组内存记号流)。

## 运行结果

首先在txt文件中输入想要分析和翻译的算术表达式

[![RE0Qbj.png](https://z3.ax1x.com/2021/06/21/RE0Qbj.png)](https://imgtu.com/i/RE0Qbj)

结果为

[![RE085q.png](https://z3.ax1x.com/2021/06/21/RE085q.png)](https://imgtu.com/i/RE085q)
