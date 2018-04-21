# 最长上升子序列

注意二分操作
```cpp
#include<cstdio>
#include<cstring>
#define MAXN 100000
template <typename T>
inline void Read(T &x){
	x=0;int p=1;char c=getchar();
	for(;!('0'<=c&&c<='9');c=getchar()) if(c=='-') p=-1;
	for(;'0'<=c&&c<='9';c=getchar()) x=x*10+c-'0';
	x*=p;
}
int a[MAXN+10],b[MAXN+10],hash[MAXN+10],nH,ans[MAXN+10],nA;
inline int find(int val){
	int l=1,r=nA,mid;
	while(l<r){
		mid=l+r>>1;
		if(ans[mid]<val) l=mid+1;
		else r=mid;
	}
	return l;
}
int n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) Read(a[i]);
	for(int i=1;i<=n;i++) hash[a[i]]=++nH;
	for(int i=1,x;i<=n;i++) {Read(x);b[i]=hash[x];}
	for(int i=1;i<=n;i++){
		if(b[i]>ans[nA]) ans[++nA]=b[i];
		else ans[find(b[i])]=b[i];
	}
	printf("%d",nA);
	return 0;
}
```