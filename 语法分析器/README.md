## 基本方法

编写递归调用程序实现自顶向下的分析

实现步骤
1. 修改文法，即消除左递归，变为递归调用预测分析适用的文法
2. 画状态转换图。即对每一个非终结符，画一个状态转换图
3. 化简状态转换图
4. 依据状态转换图写程序

## 运行结果

### 运行结果1

[![REdQSS.png](https://z3.ax1x.com/2021/06/21/REdQSS.png)](https://imgtu.com/i/REdQSS)

### 运行结果2

[![REd3Lj.png](https://z3.ax1x.com/2021/06/21/REd3Lj.png)](https://imgtu.com/i/REd3Lj)

### 运行结果3

[![REdywR.png](https://z3.ax1x.com/2021/06/21/REdywR.png)](https://imgtu.com/i/REdywR)

### 运行结果4

[![REdgFx.png](https://z3.ax1x.com/2021/06/21/REdgFx.png)](https://imgtu.com/i/REdgFx)

## 总结
从一些实验结果来推断：该语法分析器可以正确识别输入记号流并对应输出相应产生式，在输入记号流不属于该文法时可以在出错位置和结束位置报错。缺点在于没有错误处理和恢复的功能。
