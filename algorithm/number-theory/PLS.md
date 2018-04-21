# 线性筛及其应用
求素数表对求解数论问题有莫大的帮助，线性筛也为我们提供了求解数论函数的一种方式

## 引入
```cpp
//线性筛
#include<cstdio>
#include<cstring>
bool vis[1000001];
int prime[1000001];
inline void getprime(int length) {
	memset(vis,true,sizeof(vis));
	memset(prime,0,sizeof(prime));//初始化数组
	int i,j;
	for(i=2; i<=length; i++) {
		if(vis[i])
			prime[++prime[0]]=i;
		for(j=1;j<=prime[0]&&i*prime[j]<=length;++j) {
			vis[i*prime[j]]=false;//此处prime[j]是合数i*prime[j]的最小素因子
			if (i%prime[j]==0) break;//关键，在此处停止检查，防止重复
		}
	}
}
int main() {
	int m;
	scanf("%d",&m);
	getprime(m);
	for(int i=1;prime[i]!=0; i++) {
		printf("%d ",prime[i]);
	}
	return 0;
}
```
原理:
一个合数(x)与一个质数(y)的乘积可以表示成一个更大的合数(Z)与一个更小的质数(a)的乘积

证明：
i)任何一个合数都可以表示成一个质数和一个数的乘积
ii)假设A是一个合数，且A = x * y，这里x也是一个合数，那么有:
A = x * y(假设y是质数，x合数)
x = a * b(假设a是质数，且a&lt;x→a&lt;y)
→A=a*b*y=a*Z(Z=b*y)

所以对于每一个数只需要检查一次，时间复杂度为O(n)
## 在数论中的应用：
### 欧拉函数：
由于欧拉数是一个积性函数$$\phi(xy)=\phi(x)*\phi(y)$$
而我们注意到$$\phi(p)=p-1$$,(p是质数)所以我们就可以用质因素分解来愉快的求解了

```cpp
//线性筛求解欧拉函数
#include<cstring>
bool vis[1000001];
int prime[1000001],phi[1000001];
inline void getphi(int length) {
	memset(vis,true,sizeof(vis));
	memset(prime,0,sizeof(prime));//初始化数组
	phi[1]=1;
	int i,j;
	for(i=2; i<=length; i++) {
		if(vis[i]){ 
			prime[++prime[0]]=i;
			phi[i]=i-1;
		}
		for(j=1;j<=prime[0]&&i*prime[j]<=length;++j) {
			vis[i*prime[j]]=false;//此处prime[j]是合数i*prime[j]的最小素因子
			if (i%prime[j]==0){
				phi[i*prime[j]]=phi[i]*prime[j];//*见下文注解
			 	break;
			}
			phi[i*prime[j]]=phi[i]*(prime[j]-1);
		}
	}
}
int main() {
	int m;
	scanf("%d",&m);
	getphi(m);
	for(int i=1;prime[i]!=0; i++) {
		printf("%d ",phi[i]);
	}
	return 0;
}
```

*:
当x%p==0时，其中p为质数，且为x的最小质因子，（重要关键点）
phi(x * p) = phi(x) * p
证明：
>首先考虑phi(x)的那些数(t小于p且与p互素)都为gcd(t, x)=1
那么gcd(t + y, x) == 1根据辗转相除法也是成立的
因为gcd(t, x)=1，所以gcd(t, p)=1
所以gcd(t, x * p)=1
所以gcd(t + x, x * p)=1
同理 gcd(t + x, x * p)=gcd(t + 2x, x * p)=gcd(t + 3x, x * p)=....=gcd(t + (p - 1) * x, x * p)=1
相当于证明了对于每一个gcd(t, x)=1,都对应与p个与t*p互质的数,分别为t,t+x,t+2x,....t+(p-1)*x

###　莫比乌斯函数：

定义：
$$\mu(n) = \begin{cases} 1 & n = 1 \\ (-1) ^ N & \prod\limits_{i = 1} ^ {N} k_i = 1 \\ 0 & Otherwise \end{cases}$$

```cpp
void getmu(int length){
	mu[1]=1;
	for(int i=2;i<=length;i++){
		if(!vis[i]) {
			prime[++prime[0]]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=prime[0]&&i*prime[j]<length;j++){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0) {
				mu[i*prime[j]]=0;
				break;
			}
			mu[i*prime[j]]=-mu[i];
		} 
	}
```

说明：
1. 当i为质数时根据定义$$\phi(i)=-1$$
2. 当i设 $$p_1$$为 n 最小质因子， $$n' = \frac{n}{p_1} $$

在线性筛中，n 通过 $$n' \times p_1 $$ 被筛掉。
当 $$n' \mod p_1=0$$，即 $$k_1 \gt 1$$ 时，由定义得$$\mu(n) = 0$$
当 $$n' \mod p_1 \neq 1 $$ ，即  $$k_1 = 1$$ 时， $$n'$$有 $$N - 1$$个质因子，此时我们分情况讨论，若 $$\mu(n') \neq 0 $$，即$$n'$$的所有质因子次数均为1，根据定义有
若 $$\mu(n') = 0$$，说明 $$\prod\limits_{i = 2} ^ {N} k_i \gt 1$$，根据定义显然有
$$\mu(n) = 0$$
此时 $$\mu(n) = -\mu(n')$$仍然成立。