# A 小X的质数
小 X 是一位热爱数学的男孩子，在茫茫的数字中，他对质数更有一种独特的情感。小 X 认为，质数是一切自然数起源的地方。

在小 X 的认知里，质数是除了本身和 1 以外，没有其他因数的数字。

但由于小 X 对质数的热爱超乎寻常，所以小 X 同样喜欢那些虽然不是质数，但却是由两个质数相乘得来的数。

于是，我们定义，一个数是小 X 喜欢的数，当且仅当其是一个质数，或是两个质数的乘积。

而现在，小 X 想要知道，在 L 到 R 之间，有多少数是他喜欢的数呢？

## 输入格式

第一行输入一个正整数 Q，表示询问的组数。

接下来 Q 行。包含两个正整数 L 和 R。保证 L &lt; R 。

## 输出格式

输出 Q 行，每行一个整数，表示小 X 喜欢的数的个数。

## 数据范围与约定

![](/assets/jisuankenoip20174a.png)

### 样例解释 1

6 以内的质数有 2,3,5 而 4=2∗2,6=2∗3。因此 2,3,4,5,6 都是小 X 喜 欢的数，而 1 不是。

### 样例输入1
```
1
1 6
```
### 样例输出1
```
5
```
### 样例输入2
```
10
282 491
31 178
645 856
227 367
267 487
474 697
219 468
582 792
315 612
249 307
```
### 样例输出2
```
97
78
92
65
102
98
114
90
133
29
```
### 样例输入3
```
10
20513 96703
15236 86198
23185 78205
40687 48854
42390 95450
63915 76000
36793 92543
35347 53901
44188 76922
82177 90900
```
### 样例输出3
```
24413
23001
17784
2669
16785
3833
17712
6028
10442
2734
```
## Solve
签到题，线性筛+枚举水过
```cpp
#include<cstdio>
#include<cstring>
#define MAXN 10000000
#define ROOTMAXN 3163
int prime[MAXN/10];
bool vis[MAXN+1];
int sum[MAXN+1];
template <typename T>
inline void Read(T &x){
    x=0;int p=1;char c=getchar();
    for(;!('0'<=c&&c<='9');c=getchar()) if(c=='-') p=-1;
    for(;'0'<=c&&c<='9';c=getchar()) x=x*10+c-'0';
    x*=p;
}
inline void GetPrime(){
    vis[0]=vis[1]=true;
    for(int i=2;i<=MAXN;i++){
        if(!vis[i]) prime[++prime[0]]=i,sum[i]=1;
        for(int j=1;j<=prime[0]&&i*prime[j]<=MAXN;j++){
            vis[i*prime[j]]=true;
            if(i%prime[j]==0) break;
        }
    }
}
inline void GetSum(){
    for(int i=1;i<=prime[0]&&prime[i]<=ROOTMAXN;i++)
        for(int j=i;j<=prime[0]&&prime[i]*prime[j]<=MAXN;j++)
            sum[prime[i]*prime[j]]=1;
    for(int i=1;i<=MAXN;i++)
        sum[i]+=sum[i-1];
}
int main(){
    int Q,l,r;
    GetPrime();
    GetSum();
    Read(Q);
    while(Q--){
        Read(l);Read(r);
        printf("%d\n",sum[r]-sum[l-1]);
    }
    return 0;
}
```