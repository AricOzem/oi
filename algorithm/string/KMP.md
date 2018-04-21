# KMP算法
## 引入
字符串匹配是计算机的基本任务之一.但朴素算法匹配时间太慢了，如何解决这个问题呢

Knuth，Morris，Pratt共同提出的模式匹配算法：KMP算法就是一个不错的选择

它通过一个预处理，充分利用已匹配的字符串生成next数组（最大相同前后缀长度），告诉程序下一步应该比较的的位置，来大大缩短朴素匹配算法的时间（后者只是无脑+1）。

## 原理
利用最大前缀后缀来使匹配指针第一次跳转到下一个可能匹配的地方。
关于Next的求解可以参考AC自动机的原理
也可以参看此篇博文：[http://www.cnblogs.com/c-cloud/p/3224788.html](http://www.cnblogs.com/c-cloud/p/3224788.html)
## 模板

```cpp
#include<cstdio>
#include<cstring>
inline void MakeNext(char *str,int next[]){
	int len=strlen(str);
	for(int i=1,k=0;i<len;i++){
		while(k>0&&str[i]!=str[k]) k=next[k-1];
		if(str[i]==str[k]) k++;
		next[i]=k;
	}
}
inline int Find(char *str,char *u,int l){
	int strLen=strlen(str),uLen=strlen(u);
	int strP=0,uP=0;
	for(strP=l;strP<strLen;strP++){
		while(uP>0&&str[strP]!=u[uP]) uP=next[uP];
		if(str[strP]==u[uP]) uP++;
		if(uP==uLen) return strP-uLen+1; 
	}
	if(strP==strLen) return -1;
} 
```