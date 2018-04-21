# 树状数组

## 引入

众所周知，线段树可以求区间上的一些操作，但是常数比较大，而且也比较难写，那么有没有一个常数小，灵活快捷的替代方法呢。于是就有了树状数组。

## 性质

看一看图就差不多知道了

![](/assets/BIT.jpg)

表示的区间跟标号的二进制有关

设节点编号为x，那么这个节点管辖的区间为2^k（其中k为x二进制末尾0的个数）个元素。

因为这个区间最后一个元素必然为Ax。

由于运用了类似前缀和的思想，只支持有逆运算的操作

所以我们再利用前缀和（差分）的限制，还可以让它支持区间修改操作

对于一个前缀和

$$a[]=\{1,5, 9 ,14, 16\}$$

我们差分一下把他恢复原状

$$b[]=\{1,4 ,4 ,5 ,2\}$$

假如我们将前缀和进行区间修改\(给2~4加1\)那么有

$$a[]=\{1,6, 10 ,15, 16\}$$

其差分得到

$$b[]=\{1,5 ,4 ,5 ,1\}$$

只有b2和b5发生了变化

这是很显然的

然后我们用把原来的数字当成前缀和，用树状数组维护一下差分数组就好了（区间修改，单点查询）（模板同上）
如果我们要同时支持两种操作，怎么办呢

设原数组第i位的值为$$a[i]$$,我们对其进行差分设$$d[i]=a[i]-a[i-1]$$
对a的前n位求和，得到式子
$$\sum\limits_{i=1}^{n}=\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}d[i]$$
每个$$d$$的系数是规律的有
$$\sum\limits_{i=1}^{n}=\sum\limits_{i=1}^{n}(n-i+1)d[i]$$
为了便于维护d，我们将它化为
$$\sum\limits_{i=1}^{n}=\sum\limits_{i=1}^{n}(n+1)d[i]-\sum\limits_{i=1}^{n}i*d[i]$$
所以我们可以维护两个树状数组，一个针对$$d[i]$$另一个针对$$i*d[i]$$ 来支持上述操作

## 模板
1.
```cpp
namespace BitTree {
#define lowbit(x) (x&(-x))
	int nA,a[MAXN+10];
	inline void Init(int _nA){
		nA=_nA;
		memset(a,0,sizeof(a));
	}
	inline void Add(int u,int val) {
		for(; u<=nA;u+=lowbit(u)) a[u]+=val;
	}
	inline int Query(int u){
		int ret=0;for(;u;u-=lowbit(u)) ret+=a[u];
		return ret;
	}
#undef lowbit
}
```
2.
```cpp
namespace BitTree {
#define lowbit(x) (x&(-x))
	int nA;ll a1[MAXN+10],a2[MAXN+10];
	inline void Init(int _nA){
		nA=_nA;
		memset(a1,0,sizeof(a1));
		memset(a2,0,sizeof(a2));
	}
	inline void Add(int u,ll val) {
		for(int v=u; v<=nA;v+=lowbit(v)) a1[v]+=val,a2[v]+=u*val;
	}
	inline ll Query(int u){
		ll ret=0;for(int v=u;v;v-=lowbit(v)) ret+=1LL*(u+1)*a1[v]-a2[v];
		return ret;
	}
#undef lowbit
}
```
## 应用

[Luogu 1972 \[SDOI2009\]HH的项链](https://www.luogu.org/problem/show?pid=1972) [题解](/Luogu/p1972.md)

