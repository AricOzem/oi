# 中国剩余定理

## 引入

一元线性同余方程组问题最早可见于中国南北朝时期（公元5世纪）的数学著作《孙子算经》卷下第二十六题，叫做“物不知  
数”问题，原文如下：

> 有物不知其数，三三数之剩二，五五数之剩三，七七数之剩二。问物几何？

即，一个整数除以三余二，除以五余三，除以七余二，求这个整数。《孙子算经》中首次提到了同余方程组问题，以及以上具体问题的解法，因此在中文数学文献中也会将中国剩余定理称为孙子定理

那么我们怎么编程解决这个问题呢?

## 模板

```cpp
#include<cstdio>
#define MAXN 100000
int a[MAXN+1],m[MAXN+1],M=1;
// ax = 1 (mod b)
inline void exgcd(int a,int b,int &x,int &y){
    if(b==0){x=1;y=0;return ;}
    exgcd(b,a%b,x,y);
    int t=y;y=x-a/b*y;x=t;
}
inline int CRT(const int _a[],const int _m[],const int _n){
    int M=1,res=0;
    for(int i=1;i<=_n;i++) M*=_m[i];
    for(int i=1,t,k;i<=_n;i++){
        exgcd(M/_m[i],_m[i],t,k);
        res=(res+(M/_m[i])*t*_a[i])%M;
    }
    if(res<0) res+=M;
    return res;
}
int main(){
    int n,t,k,ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&m[i]);
    ans=CRT(a,m,n);
    printf("%d\n",ans);
    return 0;
}
```

## 原理解释

从上面代码我们可以看出 对于 $$x\equiv a_j (\mod m_j), 1\leqslant j \leqslant k$$

必有解$$c=M_1M_1^{-1}a_1+\cdot\cdot\cdot+M_kM_k^{-1}a_k$$

且该同余方程组的所有解满足，$$x \equiv c(\mod m)$$

$$m=m_1m_2\cdot\cdot\cdot m_k$$

我们可以用叠加法来证明

若有$$x_0$$满足同余方程组 $$x_0'$$满足下面的同余方程组

$$x\equiv a_j'(\mod m_j), 1\leqslant j \leqslant k$$

那么,$$x_0+x_0'$$一定是同余方程组

$$x\equiv a_j+a_j'(\mod m_j), 1\leqslant j \leqslant k$$的解

因此,我们可以用如下的叠加方法来求该同余方程组的解。设

$$a_j^{(i)} = \begin{cases} a_j & i=j \\ 0 & i \neq j \end{cases}$$

对于每个固定的$$i(1\leqslant i \leqslant k)$$考虑同余方程组

$$x\equiv a_j^{(i)}(\mod m_j), 1\leqslant j \leqslant k$$

我们知道当 $$j \neq i$$时 $$x\equiv 0 (\mod m_j)$$

所以有$$x\equiv 0 (\mod M_i)$$ 这里的$$M_i=m/m_i$$

即$$x=M_iy$$带入第i的方程得到

$$M_iy \equiv a_i (\mod m_i)$$

可化为 $$y \equiv M_i^{-1}a_i (\mod m_i)$$

可化为 $$M_iy \equiv M_iM_i^{-1}a_i (\mod m_i*M_i)$$

即 $$x \equiv M_iM_i^{-1}a_i (\mod m)$$

注意到 $$a_j^{(1)}+a_j^{(2)}+\cdot\cdot\cdot+a_j^{(k)}=a_j$$

根据前面提到的原理我们就可以得出原同余方程的解为

$$M_1M_1^{-1}a_1+\cdot\cdot\cdot+M_kM_k^{-1}a_k$$

证毕

关于乘法逆元我们可以使用[扩展欧几里得算法](//algorithm/number-theory/CRT.md)求解

总复杂度为O\(nlogn\)

## 应用

[POJ 1006](http://poj.org/problem?id=1006) [题解](/POJ/p1006.md)

