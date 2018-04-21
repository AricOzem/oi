# 二分&三分搜索
## 引入
二分用于查找单调函数中逼近求解某点的值
三分用于凸性或凹形函数时求那个凸点或凹点。
## 解决
### 二分
```cpp
inline int Find(int u) {
	int l=low,r=up,mid,mmid;
	while(l<r-1) {
		mid=(l+r)>>1;
		if(f(mid)>f(u)) r=mid;
		else l=mid;
	}
	if(f(l)>f(r)) return l;
	return r;
}
```
### 三分
以凸为例
![](/assets/Ternary search.PNG)
```cpp
inline int Find(int u) {
	int l=low,r=up,mid,mmid;
	while(l<r-1) {
		mid=(l+r)>>1;
		mmid=(mid+r)>>1;
		if(f(mid)>f(mmid)) r=mmid;
		else l=mid;
	}
	if(f(l)>f(r)) return l;
	return r;
}
```
## 应用