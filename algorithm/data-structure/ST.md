# 线段树
## 引入
为了高效解决连续区间的动态查询问题，我们引入线段树
## 性质
线段树的每个节点表示一个区间，子节点则分别表示父节点的左右半区间

例如父亲的区间是[a,b]，那么(c=(a+b)/2)左儿子的区间是[a,c]，右儿子的区间是[c+1,b]

由于二叉结构的特性，它基本能保持每个操作的复杂度为O(logn)。
### 定义节点
```cpp
#include<cstdio>
struct Node {
	int l;
	int r;
	int sum;
	int lazy;
};
```
### 建树
![](/assets/segment-tree-1.png)
```cpp
void Build_Tree(int x,int l,int r){//划分区间递推建树
	node[x].l=l,node[x].r=r;
	if(l==r)
	node[x].sum=vaule[l];
	else{
		int mid=(l+r)/2;
		Build_Tree(l,mid,x<<1);
		Build_Tree(mid+1,r,(x<<1)+1);
		node[x].sum=node[x<<1].sum+node[(x<<1)+1].sum;
	}
	return ;
}
```
### 下传标记
一边查询一边下放修改，既保证正确性也保证了速度
```cpp
void PushDownLazy(int u) {
	if(node[u].lazy) {
		node[u<<1].sum+=(node[u<<1].r-node[u<<1].l+1)*node[u].lazy;
		node[u<<1|1].sum+=(node[u<<1|1].r-node[u<<1|1].l+1)*node[u].lazy;
		node[u<<1].lazy+=node[u].lazy;
		node[u<<1|1].lazy+=node[u].lazy;
		node[u].lazy=0;
	}
}
```
### 区间更新
```cpp
void UpdateSection(int u,int val,int _l,int _r) {
	if(node[u].l>=_l&&node[u].r<=_r) {
		node[u].sum+=(node[u].r-node[x].l+1)*val;
		node[u].lazy+=val;
		PushDownLazy(u);
		return ;
	}
	PushDownLazy(u);
	if(node[u].l!=node[u].r) {
		int mid=(node[u].l+node[u].r)>>1;
		if(mid<_l) {
			Update(_l,_r,val,u<<1|1);
		} else if(mid>=_r) {
			Update(_l,_r,val,u<<1);
		} else {
			Update(_l,_r,val,u<<1);
			Update(_l,_r,val,u<<1|1);
		}
	}
	node[u].sum=node[u<<1].sum+node[u<<1|1].sum;
}
```
单点 _l=_r
### 查询区间和
```cpp
int Querysum(int u,int _l,int _r) {
	if(node[u].l>=_l&&node[u].r<=_r)//全部贡献 
		return node[u].sum;
	PushDownLazy(u);//下传lazy标记 
	int mid=(node[u].l+node[u].r)>>1;
	if(mid<_l) {
		return Querysum(_l,_r,u<<1|1);
	} else if(mid>=_r) {
		return Querysum(_l,_r,u<<1);
	} else return Querysum(_l,_r,u<<1)+Querysum(_l,_r,u<<1|1);
}
```
单点值 _l=_r
## 模板
```cpp
template <typename Num>
struct SegTree{
	Num sum[MAXN<<3|1];
	Num lazy[MAXN<<3|1];
	Num val[MAXN<<3|1];
	void Build(int u,int l,int r){
		if(l==r) {sum[u]=val[l];return ;}
		int mid=l+r>>1;
		Build(u<<1,l,mid);Build(u<<1|1,mid+1,r); 
		sum[u]=sum[u<<1]+sum[u<<1|1];
	}
	void PushDown(int u,int l,int r){
		int mid=l+r>>1;
		sum[u<<1]+=lazy[u]*(mid-l+1),sum[u<<1|1]+=lazy[u]*(r-mid);
		lazy[u<<1]+=lazy[u],lazy[u<<1|1]+=lazy[u];
		lazy[u]=0;
	}
	void Add(int _l,int _r,Num val,int u,int l,int r){
		if(_l<=l&&r<=_r) {
			sum[u]+=(r-l+1)*val;
			lazy[u]+=val;
			PushDown(u,l,r);
			return ;
		}
		if(lazy[u]) PushDown(u,l,r);
		if(l==r) return ;
		int mid=l+r>>1;
		if (_r<=mid) Add(_l,_r,val,u<<1,l,mid);
		else if(_l>mid) Add(_l,_r,val,u<<1|1,mid+1,r);
		else {Add(_l,_r,val,u<<1,l,mid);Add(_l,_r,val,u<<1|1,mid+1,r);}
		sum[u]=sum[u<<1]+sum[u<<1|1];
	}
	const Num Query(int _l,int _r,int u,int l,int r){
		if(_l<=l&&r<=_r) return sum[u];
		if(lazy[u]) PushDown(u,l,r);
		int mid=l+r>>1;
		if(_r<=mid) return Query(_l,_r,u<<1,l,mid);
		else if(_l>mid) return Query(_l,_r,u<<1|1,mid+1,r);
		else return Query(_l,_r,u<<1,l,mid)+Query(_l,_r,u<<1|1,mid+1,r);
	}
};
```
## 应用