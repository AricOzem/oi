#E Valley Number

## Description
众所周知，度度熊非常喜欢数字。

它最近发明了一种新的数字：Valley Number，像山谷一样的数字。


![](/assets/C777-1005-1.jpg)


当一个数字，从左到右依次看过去数字没有出现先递增接着递减的“山峰”现象，就被称作 Valley Number。它可以递增，也可以递减，还可以先递减再递增。在递增或递减的过程中可以出现相等的情况。

比如，1，10，12，212，32122都是 Valley Number。

121，12331，21212则不是。

度度熊想知道不大于N的Valley Number数有多少。

注意，前导0是不合法的。
 

## Input
第一行为T，表示输入数据组数。

每组数据包含一个数N。

● 1≤T≤200

● 1≤length(N)≤100
 

## Output
对每组数据输出不大于N的Valley Number个数，结果对 1 000 000 007 取模。
 
## Sample Input
```
3
3
14
120
``` 

## Sample Output
```
3
14
119
```

## Solve 

数位dp 记录是否上升过
注意前导零

```cpp
#include<cstdio>
#include<cstring>
#define MAXN 1000
#define K 1000000007
typedef long long ll;
int len;
ll f[MAXN+10][10][2];//pos pre upTimes <2
int a[MAXN+10]; 
ll dfs(int pos,int pre,int upTimes,bool limit){
    if(pos==-1) {if(pre!=-1) return 1;return 0;}
    if(!limit&&pre!=-1&&f[pos][pre][upTimes]!=-1) return f[pos][pre][upTimes];
    int end=limit?a[pos]:9;
    ll ret=0;
    for(int i=0;i<=end;i++){
        if(pre==-1){//前导零
            if(i==0) ret=(ret+dfs(pos-1,-1,upTimes,limit&&i==end))%K;
            else ret=(ret+dfs(pos-1,i,upTimes,limit&&i==end))%K; 
        }else if(upTimes==0) ret=(ret+dfs(pos-1,i,i>pre,limit&&i==end))%K;
              else if(upTimes==1&&i>=pre) ret=(ret+dfs(pos-1,i,upTimes,limit&&i==end))%K;
    }
    if(!limit&&pre!=-1) f[pos][pre][upTimes]=ret;
    return ret;
}
int main(){
    int T;
    char str[500];
    scanf("%d\n",&T);
    memset(f,-1,sizeof(f)); 
    while(T--){
        gets(str+1);
        len=strlen(str+1);
        for(int i=1;i<=len;i++) a[len-i]=str[i]-'0';
        //puts(str+1); 
        printf("%lld\n",dfs(len-1,-1,0,1));
    }
    return 0;
}
```