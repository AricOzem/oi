# Lucas定理

## 形式

$$C_{m}^{n}\equiv\prod_{i=0}^{k}C_{m_i}^{n_i}\mod p$$

其中$$m=\sum_{i=0}^{k}m_ip^i\,,\,n=\sum_{i=0}^{k}n_ip^i\ \ \ \ \ (n_0=n \mod p ,m_0=m \mod p)$$

## 证明
如果能证明

$$\large\binom{n}{m} \equiv\binom{n \mod p}{m \mod p}*\binom{\lfloor\frac{n}{p}\rfloor}{\lfloor\frac{m}{p}\rfloor} \mod p$$

那么递推下去就可以了 (问题规模不断变小)

根据组合数的定义$$\binom{n}{m}=\dfrac{m!}{n!(m-n)!}$$对于任意质数$$p$$有

$$\binom{n}{p}\equiv 0\mod p,(n\neq 0\text{或}p)$$

根据二项式定理有

$$(x+1)^m=\sum\limits_{i=0}^{m}\binom{i}{p}x^i$$

显然对于任意的m有

$$(x+1)^m=(x+1)^{\lfloor{\frac{m}{p}}\rfloor *p}*(x+1)^{m\mod p}$$

由$$p$$为素数，可知对于$$1\leqslant j\leqslant p-1$$

$$\binom{j}{p}=\dfrac{p!}{j!(p-j)!}=\dfrac{p}{j}\binom{j-1}{p-1}\equiv0\mod p,(n\neq 0\text{或}p)$$

那么根据二项式定理有

$$(x+1)^p=\sum\limits_{i=0}^{p}\binom{i}{p}x^i\equiv 1+x^p \mod p$$

$$(x+1)^m=(x^p+1)^{\lfloor{\frac{m}{p}}\rfloor }*(x+1)^{m\mod p}$$


还是根据二项式定理有

$$\large\sum\limits_{i=0}^{m} \binom{i}{m} x^i=(\sum\limits_{i=0}^{\lfloor{\frac{m}{p}}\rfloor}\binom{i}{\lfloor{m\over p}\rfloor}x^{pi})(\sum\limits_{i=0}^{m\mod p}\binom{i}{m\mod p}x^i)$$

那么等号左边当i=n时，等号右边唯一能组合出来$$x^n$$的就是$$x^{\lfloor\frac{n}{p}\rfloor p}$$和$$x^{n \mod p}$$ 

那么系数乘积也就相等。 

证毕。

## 应用
```cpp
#include<cstdio>
#define MAXN 100000
typedef long long ll;
ll fac[MAXN+10],mod;
inline ll expow(ll a,int x) {
	ll ret=1;
	while(x) {
		if(x&1) ret=(ret*a)%mod;
		a=(a*a)%mod;
		x>>=1;
	}
	return ret;
}
ll C(int n,int m) {
	if(n>m) return 0;
	return (fac[m]*expow((fac[n]*fac[m-n])%mod,mod-2))%mod;/
}
ll Lucas(int n,int m,int p){
	if(n==0) return 1;
	return (Lucas(n/p,m/p,p)*C(n%p,m%p))%p;
}
int main() {
	int T,n,m;
	scanf("%d",&T);
	fac[0]=1;
	while(T--) {
		scanf("%d%d%d",&n,&m,&mod);
		for(int i=1;i<=mod;i++) fac[i]=(fac[i-1]*i)%mod;
		printf("%d\n",Lucas(n,n+m,mod));
	}
	return 0;
}
```
## 扩展

### 形式

### 证明

### 应用



