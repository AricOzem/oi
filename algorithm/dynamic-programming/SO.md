# 斜率优化

## 引入

在[BZOJ 1010 玩具装箱](http://www.lydsy.com/JudgeOnline/problem.php?id=1010)一题中 我们得到如下动态规划方程

$$f[i]=\min\{f[j]+(sump[i]-sump[j]-L-1)^2\}$$

$$O(n)$$的状态 $$O(n)$$的转移开销 总时间复杂度为$$O(n^2)$$

但原题的数据范围$$n\leqslant 5000$$ 显然会TLE，如何优化呢

## 解决

对于某一类型的dp方程

$$f[i]=min\{a[i]\times b[j]+c[j]+d[i]\}$$

其中$$a[x],b[x],c[x],d[x]$$是关于$$x$$的函数，且$$b$$单增。$$-------(1)$$

按照套路，**先**数学归纳法**证明决策单调性**。

1.归纳假设：

$$\text{假设有i前两个决策点}j,k(j\lt k)$$，且$$k$$的决策要比$$j$$好，(存在决策单调性)即

$$a[i]\times b[j]+c[j]+d[i]\leqslant a[i]\times b[k]+c[k]+d[i],j\leqslant k----(2)$$

2.归纳推理：

此时后面有状态$$i+1$$，这里我们为了简单起见，不妨设$$a[i+1]=a[i] - v,\  v \gt 0$$，也就是a单调递减\(单调递增同理\)。

即证：

$$a[i+1]\times b[j]+c[j]+d[i+1]\geqslant a[i+1]\times b[k]+c[k]+d[i+1]$$

$$(a[i] - v) \times b[j]+c[j]+d[i+1]\geqslant (a[i] - v)\times b[k]+c[k]+d[i+1]$$

化简得：

$$a[i]\times b[j]+v\times b[k]+c[j]\geqslant a[i]\times b[k]+v\times b[j]+c[k]$$

$$\because$$

由\(2\)得：$$a[i]\times b[j]+c[j]\geqslant a[i]\times b[k]+c[k]$$

由\(1\)得：$$b[k]\gt b[j]$$

又$$\because v \gt 0$$

$$\therefore v\times b[k] \gt v\times b[j] $$

假设得证

证明了单调性后 我们将由决策单调性得出的式子展开，化成斜率式：

$$a[i]\times b[j]+c[j]+d[i]\geqslant a[i]\times b[k]+c[k]+d[i] \ ,\ j \lt k$$

$$-a[i]\geqslant \large\frac{c[j]-c[k]}{b[j]-b[k]}$$

记斜率$$slope(j,k)=\large\frac{c[j]-c[k]}{b[j]-b[k]}$$  
那么当  
$$slope(j,k)\leqslant -a[i]$$ 时 决策k比决策j优 决策j可以被直接抛弃从而优化时间复杂度到$$O(n)$$

我们使用队列来优化

1. 对于队头的两个元素，假如有$$slope(q[l],q[l+1])\leqslant -a[i]$$则说明队列中第二个元素比第一个优，队头出队.  
2. 此时可以确保队头元素是最优解，用队头元素计算出f\[i\]的数值  
3. 在有了$$f[i]$$的值的情况下，就可以在队尾进行维护了.对于队尾的两个元素$$r-1$$,$$r$$,假如有$$slope(r-1,r)\lt slope(i,r)$$则说明x是无用的，可以出队.
   具体证明如下：  
   i. 假如 $$slope(r-1,r)\lt slope(i,r)\leqslant -a[i]$$，则虽然有$$r$$比$$i$$优，但又有$$r-1$$比$$r$$优，因此r可出队；  
   ii. 假如$$slope(r-1,r)\lt slope(i,r)\gt -a[i]$$，则有$$i$$比$$r$$优，$$r$$还是可以出队.  
4. 将$$i$$加入队尾

## 应用

[BZOJ 1010 玩具装箱](http://www.lydsy.com/JudgeOnline/problem.php?id=1010) [题解](/BZOJ/p1010.md)

## 参考资料

斜率优化学习笔记（MashiroSky）：[http://www.cnblogs.com/MashiroSky/p/6009685.html](http://www.cnblogs.com/MashiroSky/p/6009685.html)

