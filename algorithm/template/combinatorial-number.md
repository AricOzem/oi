# 快速求模意义下的组合数

快速求阶乘逆元  
由$$p=k\cdot i+r$$  
得  
$$\begin{aligned} k\cdot r^{-1} + i^{-1} &\equiv& 0 &\pmod p\\ i^{-1} &\equiv& -k\cdot r^{-1} &\pmod p\\ i^{-1} &\equiv& -\left\lfloor\frac{p}{i}\right\rfloor\cdot \left(p\bmod i\right)^{-1} &\pmod p\ \end{aligned}$$

```cpp
inline ll expow(ll a,int x) {
    ll ret=1;
    while(x) {
        if(x&1) ret=ret*a%MOD;
        a=a*a%MOD;
        x>>=1;
    }
    return ret;
}
inline void CInit() {
    fac[0]=iv[0]=fac[1]=iv[1]=1;
    for(int i=2; i<=MAXN; i++) {
        fac[i]=fac[i-1]*i%MOD;
        iv[i]=(ll)(-(MOD/i)*iv[MOD%i]+MOD)%MOD;
    }
    for(int i=2; i<=MAXN; i++) iv[i]=(ll)iv[i]*iv[i-1]%MOD;
}

inline ll C(int _n,int _m) {
    if(_m<_n) return 0;
    return fac[_m]*iv[_n]%MOD*iv[_m-_n]%MOD;
}
```



