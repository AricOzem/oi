# 可持久化线段树
## 引入
给定区间求第k大的值，我们可以在线段树上二分
但如果查询区间很多，我们就要建立很多线段树，显然会MLE，怎么办呢。我们有可持久化线段树
## 解决
考虑差分，sum[l~r]可以表示为sum[r]-sum[l-1],sum为前缀和，我们把这种思想运用在建立线段树上面，对于线段树1~i，他的结点数比1~(i-1)多了$$\log_2i$$个，增长速度为log级别的，这是个很好的解决MLE的办法。所以我们依次建树，共同使用相同的节点部分，区间l-r的线段树就是区间1~r的线段树减去区间1~（l-1）的线段树。
## 模板
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define ls(x) node[x].ls
#define rs(x) node[x].rs
#define w(x) node[x].w
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
```
## 应用
[POJ 2104 Kth-Number ](http://poj.org/problem?id=2104) [题解](/POJ/p2104.md)