1.
```cpp
namespace Hash {
	const int mod=1E7+9;
	std::vector<ll> a[mod];
	std::vector<ll> count[mod];
	inline int GetKey(ll val) {
		return val%mod;
	}
	inline void Add(ll val) {
		int key=GetKey(val);
		int len=a[key].size(),p=0;
		while(p<len)
			if(a[key][p]==val){
				count[key][p]++;
				return ;
			}
		a[key].push_back(val);
		count[key].push_back(1);
	}
}
```
2.
```
namespace Hash {
	const int mod=1E7+9;
	ll a[MAXH];int count[MAXH];
	inline int GetKey(ll val) {
		return val%mod;
	}
	inline void Add(ll val) {
		int key=GetKey(val);
		for(int i=key;;++i)
			if(!a[i]){a[i]=val,count[i]=1;return;}
			else if(a[i]==val){count[i]++;return;}
	}
}
```


