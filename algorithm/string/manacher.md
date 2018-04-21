# Manacher 算法
## 引入
最长回文子串问题：给定一个字符串，求它的最长回文子串长度
如果暴力枚举所有子串时间复杂度为$$O(n^3)$$
考虑回文串的性质
## 解决

## 模板
```cpp
#include<cstdio>
#include<cstring>
#define MAXN 110000
inline int Min(int a,int b){
	if(a<b) return a;
	return b;
}
char s[MAXN+10],str[MAXN<<1|1];
int r[MAXN<<1|1];
inline int Manacher(){
	int maxRight=0,maxPos=0,ret=0;
	int len=strlen(s);
	for(int i=1;i<=len;i++) str[i*2-1]=s[i-1],str[i*2]='#';
	str[0]='#';
	//printf("%s\n",str);
	len=strlen(str);
	for(int i=0;i<len;i++){
		if(i<maxRight){
			r[i]=Min(r[2*maxPos-i],maxRight-i);
		}else r[i]=1;
		while(i-r[i]>=0&&i+r[i]<len&&str[i-r[i]]==str[i+r[i]]) r[i]++; 
		if(i+r[i]>maxRight)
			maxRight=i+r[i],maxPos=i;
		if(ret<r[i]) ret=r[i];
	}
	return ret-1;
}
int main(){
	while(~scanf("%s",s))
		printf("%d\n",Manacher());
	return 0;
}
```
## 应用