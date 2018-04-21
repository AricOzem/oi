# Treap
## 引入
解决二叉搜索树可能深度过大的另一种数据结构
## 性质
Treap=Tree+Heap。Treap本身是一棵二叉搜索树，它的左子树和右子树也分别是一个Treap，和一般的二叉搜索树不同的是，Treap纪录一个额外的数据，就是优先级。Treap在以关键码构成二叉搜索树的同时，还满足堆的性质。这些优先级是是在结点插入时，随机赋予的，Treap根据这些优先级满足堆的性质。这样的话，Treap是有一个随机附加域满足堆的性质的二叉搜索树，其结构相当于以随机数据插入的二叉搜索树。其基本操作的期望时间复杂度为O(logn)。相对于其他的平衡二叉搜索树，Treap的特点是实现简单，且能基本实现随机平衡的结构。
Treap维护堆性质的方法只用到了旋转，只需要两种旋转，因此编程复杂度比Splay要小一些。
```cpp
struct Node{
	Node *ls,*rs;
	int key,fix; 
}; 
```
### 旋转操作
![](/assets/Treap-1.jpg)
```cpp
void LRotate(Node *&x){
	Node *y=x->rs;
	x->rs=y->ls;
	y->ls=x;
	x=y;
}
void RRotate(Node *&x){
	Node *y=x->ls;
	x->ls=y->rs;
	y->rs=x;
	x=y;
}  
```
### 插入操作
给节点随机分配一个优先级，先和二叉搜索树的插入一样，先把要插入的点插入到一个叶子上，然后跟维护堆一样，如果当前节点的优先级比根大就旋转，如果当前节点是根的左儿子就右旋，如果当前节点是根的右儿子就左旋。

![](/assets/Treap-2.jpg)

```cpp
void Insert(Node *&p,int key){
	if(!p){
		p=new Node;
		p->key=key;
		p->fix=rand();
	}else if(key<=p->key){
		Insert(p->ls,key);
		if(p->fix>p->ls->fix) RRotate(p);
	}else {
		Insert(p->ls,key);
		if(p->fix>p->rs->fix) LRotate(P);
	}
}
```
### 删除操作
![](/assets/Treap-3.jpg)

与BST 一样，在Treap 中删除元素要考虑多种情况。我们可以按照在BST 中删除元素同样的方法来删除Treap 中的元素，即用它的后继(或前驱)节点的值代替它，然后删除它的后继(或前驱)节点。
上述方法期望时间复杂度为O(logN)，但是这种方法并没有充分利用Treap 已有的随机性质，而是重新得随机选取代替节点。我们给出一种更为通用的删除方法，这种方法是基于旋转调整的。首先要在Treap 树中找到待删除节点的位置，然后分情况讨论：
情况一，该节点为叶节点或链节点，则该节点是可以直接删除的节点。若该节点有非空子节点，用非空子节点代替该节点的，否则用空节点代替该节点，然后删除该节点。
情况二，该节点有两个非空子节点。我们的策略是通过旋转，使该节点变为可以直接删除的节点。如果该节点的左子节点的优先级小于右子节点的优先级，右旋该节点，使该节点降为右子树的根节点，然后访问右子树的根节点，继续讨论；反之，左旋该节点，使该节点降为左子树的根节点，然后访问左子树的根节点，这样继续下去，直到变成可以直接删除的节点。
```cpp
void Delete(Node *&u,int key) {
	if(key==u->key) {
		if(!u->ls||!u->rs) {
			Node *t=u;
			if(!u->rs) u=u->rs;
			else u=u->ls;
			delete t;
		} else {
			if (P->left->fix < P->right->fix) //左子节点修正值较小，右旋
			{
				RRotate(P);
				Delete(P->right,key);
			}
			else //左子节点修正值较小，左旋
			{
				LRotate(P);
				Delete(P->left,key);
			}
		}
	}else if(key<u->key) Delete(u->ls,key);
	else Delete(u->rs,key);
}
```
## 模板 
以Tyvj 1728 普通平衡树为例
```cpp
#include<cstdio>
#include<cstdlib>
#define INF 0x7f7f7f7f 
struct Treap{
	struct Node{
		Node *ls,*rs;
		int key,fix;
		int size,cnt;
		Node():ls(NULL),rs(NULL),key(0),fix(rand()),size(1),cnt(1){}
		inline int lsize(){//Using as var 
			if(ls!=NULL) return ls->size;
			return 0;
		}
		inline int rsize(){
			if(rs!=NULL) return rs->size;
			return 0;
		}
		inline void print(){
			printf("----\n%d %d\n",key,fix);
			if(ls!=NULL) printf("%d ",ls->key); else printf("NULL ");
			if(rs!=NULL) printf("%d ",rs->key); else printf("NULL ");
			printf("cnt:%d size:%d\n-----\n",cnt,size); 
		}
	};
	Node *root;
	inline void Init(int seed){
		root=NULL;
		srand(seed);
	}
	inline void Release(Node *&x){
		if(x->ls) Release(x->ls);
		if(x->rs) Release(x->rs);
		free(x);
	}
	inline void Update(Node *&u){
		u->size=u->cnt+u->lsize()+u->rsize();
		//u->print();
	}
	inline void LRotate(Node *&x){
		Node *y=x->rs;
		x->rs=y->ls;
		y->ls=x;
		Update(x);Update(y);
		x=y;
	}
	inline void RRotate(Node *&x){
		Node *y=x->ls;
		x->ls=y->rs;
		y->rs=x;
		Update(x);Update(y); 
		x=y;
	}
	inline void Insert(Node *&u,int key){
		if(!u){
			u=new Node;
			u->key=key;
		}else if(key==u->key){
			u->size++,u->cnt++;
		}else if(key<u->key){//键值小 
			Insert(u->ls,key);
			if(u->ls->fix>u->fix) RRotate(u);//左儿子大 右旋提升 
			Update(u);
		}else{
			Insert(u->rs,key);
			if(u->rs->fix>u->fix) LRotate(u);
			Update(u);
		}
	}
	inline void Delete(Node *&u,int key){
		if(u->key==key){
			if(u->cnt>1){
				u->cnt--,u->size--;
			}else if(u->ls==NULL){
				Node *tmp=u;
				u=u->rs;
				delete tmp;
			}else if(u->rs==NULL){
				Node *tmp=u;
				u=u->ls;
				delete tmp;
			}else{//维护优先级 
				if(u->ls->fix>u->rs->fix) {
					RRotate(u);
					Delete(u->rs,key);
				}else{
					LRotate(u);
					Delete(u->ls,key);
				}
			}
		}else if(key<u->key){
			Delete(u->ls,key);
		}else Delete(u->rs,key);
		if(u!=NULL) Update(u);
	}
	inline int QueryRank(Node *&u,int key){
		if(key==u->key) return (u->lsize()+1);
		if(key<u->key)  return (QueryRank(u->ls,key));
		return (u->lsize()+u->cnt+QueryRank(u->rs,key));
	}
	inline int QueryNum(Node *&u,int rank){
		if(u->lsize()<rank&&rank<=u->lsize()+u->cnt) return u->key;
		if(rank<=u->lsize()) return QueryNum(u->ls,rank);
		return QueryNum(u->rs,rank-u->lsize()-u->cnt); 
	}
	inline int QueryPre(Node *u,int key){
		int ret=-INF;
		while(u){
			if(u->key<key){
				if(ret<u->key) ret=u->key;
				u=u->rs; 
			}else u=u->ls;
		}
		return ret;
	}
	inline int QuerySuf(Node *u,int key){
		int ret=INF;
		while(u){
			if(u->key>key){
				if(ret>u->key) ret=u->key;
				u=u->ls; 
			}else u=u->rs;
		}
		return ret;
	}
}treap;
```
## 应用
[Tyvj 1728 普通平衡树](http://www.tyvj.cn/p/1728) [题解](/BZOJ/p3224.md)