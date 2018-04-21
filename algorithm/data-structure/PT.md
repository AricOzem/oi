# 主席树（可持久化线段树）
## 引入

## 解决
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define ls(x) node[x].ls
#define rs(x) node[x].rs
#define w(x) node[x].w
#define MAXN 500000
#define MAXM 500000
template <typename T>
inline void Read(T &x){
	x=0;int p=1;char c=getchar();
	for(;!('0'<=c&&c<='9');c=getchar()) if(c=='-') p=-1;
	for(;'0'<=c&&c<='9';c=getchar()) x=x*10+c-'0';
	x*=p; 
}
int n,m;
struct Node{
	int l,r,ls,rs,w;
}node[MAXM*20+1];int tot;
int root[MAXN+10];
void Build(int &u,int l,int r){
	u=++tot;
	node[u].l=l,node[u].r=r;
	if(l==r) return ;
	int mid=l+r>>1;
	Build(ls(u),l,mid);
	Build(rs(u),mid+1,r);
}
void Insert(int &u,int x){
	node[++tot]=node[u];u=tot; w(u)++;
	if(node[u].l==node[u].r) return ;
	int mid=node[u].l+node[u].r>>1;
	if(x<=mid) Insert(ls(u),x);
	else Insert(rs(u),x);
} 
int Query(int i,int j,int k){
	if(node[i].l==node[i].r) {
		if(node[i].w-node[j].w>=k) return node[i].l;
		return 0;
	}
	int t=w(ls(i))-w(ls(j));
	if(t>=k) Query(ls(i),ls(j),k);
	else Query(rs(i),rs(j),k-t); 
}
struct Question{
	int l,r,k;
}Q[MAXN+10];
std::vector<int> bul[MAXN+10];
int ans[MAXN+10];
int main(){
	scanf("%d%d",&n,&m);
	int maxr=-1;
	for(int i=1;i<=n;i++){
		Read(Q[i].l),Read(Q[i].r),Read(Q[i].k);
		if(maxr<Q[i].r) maxr=Q[i].r;
	}
	for(int i=1,x;i<=m;i++){
		Read(x);bul[x].push_back(i);
	}
	Build(root[0],1,n);
	for(int i=1;i<=maxr;i++){
		root[i]=root[i-1];
		for(int j=0;j<bul[i].size();j++) Insert(root[i],bul[i][j]);
	}
	for(int i=1,t;i<=n;i++){
		t=Query(root[Q[i].r],root[Q[i].l-1],Q[i].k);
		ans[t]++;
	}
	for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
	return 0;
} 
```
## 应用