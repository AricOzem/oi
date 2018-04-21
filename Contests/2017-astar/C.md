# C Pokémon GO
## Description
众所周知，度度熊最近沉迷于 Pokémon GO。

![](/assets/C777-1003-1.jpg)

今天它决定要抓住所有的精灵球！

为了不让度度熊失望，精灵球已经被事先放置在一个2*N的格子上，每一个格子上都有一个精灵球。度度熊可以选择任意一个格子开始游戏，抓捕格子上的精灵球，然后移动到一个相邻的至少有一个公共点的格子上继续抓捕。例如，(2, 2) 的相邻格子有(1, 1), (2, 1) 和 (1, 2) 等等。

现在度度熊希望知道将所有精灵球都抓到并且步数最少的方案数目。两个方案被认为是不同，当且仅当两个方案至少有一步所在的格子是不同的。
 

##　Input
第一行为T，表示输入数据组数。

每组数据包含一个数N。

●1≤T≤100

●1≤N≤10000
 

## Output
对每组数据输出方案数目，结果对 1 000 000 007 取模。
 

## Sample Input
```
3
1
2
3
```

## Sample Output
```
2
24
96
```
## Solve

找规律

考虑从每个角出发填满所有格子的方案
只有三种情况
1. 最终回到同一列的另一个角
2. 从同列对应格子出跳转到右（或左）侧列的格子（两种情况）将该格当做更短格子的角递归计算（最终到达的格子一定能回来）
3. 通过一些路线经同列对应格子至跳转到右（或左）的第二列格子（四种情况） 将该格当做更短格子的角递归计算（最终到达的格子一定能回来）

考虑从中间格子出发
只有两种情况（必回到同一列对应格子）
1. 往左遍历格子回到同一列的对应格子再向右侧任意选择一个格子（两种情况）将该格当做更短格子的角递归计算
2. 往右遍历格子回到同一列的对应格子再向左侧任意选择一个格子（两种情况）将该格当做更短格子的角递归计算

所以我们只要记录两个量
从角出发填满格子方案数
从某格子出发回到同一格对应格子的方案数 显然为 2^(n-1)
```cpp
#include<cstdio>
#include<cstring>
#define MAXN 100000
#define K 1000000007
typedef long long ll;
ll toOpposite[MAXN+10];//FromAngel
ll fillAll[MAXN+10];
inline void Init(int limit){
    toOpposite[1]=1;
    for(int i=2;i<=limit;i++)
        toOpposite[i]=(toOpposite[i-1]<<1)%K;
    fillAll[1]=1;fillAll[2]=6;
    for(int i=3;i<=limit;i++)
        fillAll[i]=(toOpposite[i]+(fillAll[i-1]<<1)%K+(fillAll[i-2]<<2)%K)%K;
}
inline ll Calc(int len){
    ll sum=0;
    if(len>1) sum=(fillAll[len]<<2)%K;
    else if(len==1) return 2; 
    for(int i=2;i<len;i++)
        sum=(sum+(((toOpposite[i]*fillAll[len-i]<<1)%K+(toOpposite[len-i+1]*fillAll[i-1]<<1)%K)<<1)%K)%K;
    return sum;
}
int main(){
    int q[110],t,T,maxn=-1;
    scanf("%d",&T);
    t=T;
    while(T--){
        scanf("%d",&q[T]);
        if(q[T]>maxn) maxn=q[T];
    }
    Init(maxn);
    while(t--)
        printf("%lld\n",Calc(q[t]));
    return 0;
} 
```