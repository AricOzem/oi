# 树链剖分

## 引入

如何高效维护树上权值变化? 快速修改子树权值和路径权值？

## 解决



把树通过树链剖分“映射”线段树上（DFS的性质，一条链的时间戳是连续的）$$L[u]=L[chainTop[u]]$$为连续的一段区间供查询和修改  


每次询问两个点对（x，y）时，若x和y在同一链中，直接询问线段树中的u和v（因为同一条链中下标是连续的）u，v是x，y对应的线段树中的点。否则的话，我们从深度大的点上一点一点向上爬，每次记录该点所在的链上的情况，直到x，y在同一条链上。

```cpp
int dfsClock,dep[MAXN+10],fa[MAXN+10],chainTop[MAXN+10],L[MAXN+10];

void dfs(int u) {
    size[u]=1;
    node[++nodeIndex]=u;
    for(int i=head[u],v=E[i].v; i!=-1; i=E[i].nxt,v=E[i].v) if(fa[u]!=v) {
            fa[v]=u;
            dep[v]=dep[u]+1;
            dfs(v);
            size[u]+=size[v];
        }
}

void BuildChain(int u) {
    int maxs=0;L[u]=++dfsClock;
    if(!chainTop[u]) chainTop[u]=u;
    for(int i=head[u],v=E[i].v; i!=-1; i=E[i].nxt,v=E[i].v)if(fa[u]!=v&&size[v]>size[maxs]) maxs=v;
    if(maxs) {
        chainTop[maxs]=chainTop[u];
        BuildChain(maxs);
    }
    for(int i=head[u],v=E[i].v; i!=-1; i=E[i].nxt,v=E[i].v)if(fa[u]!=v&&v!=maxs) BuildChain(v);
}
```

## 应用

1. [LCA ](algorithm/graph-theory/LCA.md)

2. 线段树优化  
   以[Luogu 3384](https://www.luogu.org/problemnew/show/3384)为例

```cpp
#include<cstdio>
#include<cstring>
#define MAXN 100000
#define MAXE 200000
typedef long long ll;
int n,m,r,p; 
template <typename T>
inline void Swap(T &a, T &b){
    T t=a;a=b;b=t;
}
template <typename Num>
inline void Read(Num &x){
    x=0;int p=1;char c=getchar();
    for(;!('0'<=c&&c<='9');c=getchar()) if(c=='-') p=-1;
    for(;'0'<=c&&c<='9';c=getchar()) x=x*10+c-'0';
    x*=p;
}
template <typename Num>
struct SegTree{
    Num sum[MAXN<<3|1];
    Num lazy[MAXN<<3|1];
    Num val[MAXN<<3|1];
    void Build(int u,int l,int r){
        if(l==r) {sum[u]=val[l]%p;return ;}
        int mid=l+r>>1;
        Build(u<<1,l,mid);Build(u<<1|1,mid+1,r); 
        sum[u]=(sum[u<<1]+sum[u<<1|1])%p;
    }
    void PushDown(int u,int l,int r){
        int mid=l+r>>1;
        sum[u<<1]=(sum[u<<1]+lazy[u]*(mid-l+1))%p,sum[u<<1|1]=(sum[u<<1|1]+lazy[u]*(r-mid))%p;
        lazy[u<<1]=(lazy[u<<1]+lazy[u])%p,lazy[u<<1|1]=(lazy[u<<1|1]+lazy[u])%p;
        lazy[u]=0;
    }
    void Add(int _l,int _r,Num val,int u,int l,int r){
        if(_l<=l&&r<=_r) {
            sum[u]=(sum[u]+(r-l+1)*val)%p;
            lazy[u]=(lazy[u]+val)%p;
            PushDown(u,l,r);
            return ;
        }
        if(l==r) return ;
        if(lazy[u]) PushDown(u,l,r);
        int mid=l+r>>1;
        if (_r<=mid) Add(_l,_r,val,u<<1,l,mid);
        else if(_l>mid) Add(_l,_r,val,u<<1|1,mid+1,r);
        else {Add(_l,_r,val,u<<1,l,mid);Add(_l,_r,val,u<<1|1,mid+1,r);}
        sum[u]=(sum[u<<1]+sum[u<<1|1])%p;
    }
    const Num Query(int _l,int _r,int u,int l,int r){
        if(_l<=l&&r<=_r) return sum[u];
        if(lazy[u]&&l!=r) PushDown(u,l,r);
        int mid=l+r>>1;
        if(_r<=mid) return Query(_l,_r,u<<1,l,mid)%p;
        else if(_l>mid) return Query(_l,_r,u<<1|1,mid+1,r)%p;
        else return (Query(_l,_r,u<<1,l,mid)+Query(_l,_r,u<<1|1,mid+1,r))%p;
    }
};

SegTree<ll> T;

struct Edge{
    int v,nxt;
    Edge(){}
    Edge(int _v,int _nxt):v(_v),nxt(_nxt){}
}E[MAXE+10];int nE,head[MAXE+10];
inline void EdgeInit(){
    nE=0;memset(head,-1,sizeof(head));
}
inline void Link(int u,int v){
    E[nE]=Edge(v,head[u]);head[u]=nE++;
    E[nE]=Edge(u,head[v]);head[v]=nE++;
}

int val[MAXN+10];
int fa[MAXN+10],dep[MAXN+10],size[MAXN+10],chainTop[MAXN+10],son[MAXN+10];
int L[MAXN+10],R[MAXN+10],rev[MAXN+10],dfsClock;
void dfs(int u,int _fa)
{
    fa[u]=_fa;size[u]=1;
    for(int i=head[u],v=E[i].v;i!=-1;i=E[i].nxt,v=E[i].v)if(v!=_fa){ 
        dep[v]=dep[u]+1;
        dfs(v,u);
        if (size[v]>size[son[u]]) son[u]=v;
        size[u]+=size[v];
    }
}
void BuildChain(int u,int top)
{
    L[u]=++dfsClock;
    rev[dfsClock]=u;
    chainTop[u]=top;
    if (son[u]) BuildChain(son[u],top);
    for(int i=head[u],v=E[i].v;i!=-1;i=E[i].nxt,v=E[i].v) if(fa[u]!=v&&v!=son[u]) BuildChain(v,v);
    R[u]=dfsClock;
}
inline ll QueryAcc(int l,int r){
    ll ret=0;
    while(chainTop[l]!=chainTop[r]){
        if(dep[chainTop[l]]<dep[chainTop[r]]) Swap(l,r);
        ret=(ret+T.Query(L[chainTop[l]],L[l],1,1,n))%p;
        l=fa[chainTop[l]];
    }
    if(dep[l]>dep[r]) Swap(l,r);
    ret=(ret+T.Query(L[l],L[r],1,1,dfsClock))%p;
    return ret;
}
inline void AddAcc(int l,int r,int val){
    while(chainTop[l]!=chainTop[r]){
        if(dep[chainTop[l]]<dep[chainTop[r]]) Swap(l,r);
        T.Add(L[chainTop[l]],L[l],val,1,1,n);
        l=fa[chainTop[l]];
    }
    if(dep[l]>dep[r]) Swap(l,r);
    T.Add(L[l],L[r],val,1,1,dfsClock);
}
int main(){
    Read(n);Read(m);Read(r);Read(p);
    for(int i=1;i<=n;i++) Read(val[i]);
    EdgeInit();
    for(int i=1,x,y;i<n;i++){
        Read(x);Read(y);
        Link(x,y);
    }
    dfs(r,0);BuildChain(r,r);
    for(int i=1;i<=n;i++) T.val[i]=val[rev[i]];
    T.Build(1,1,dfsClock);
    for(int i=1,c,x,y,z;i<=m;i++){
        Read(c);
        switch(c){
            case 1:
                Read(x);Read(y);Read(z);
                AddAcc(x,y,z);
                break;
            case 2:
                Read(x);Read(y);
                printf("%lld\n",QueryAcc(x,y));
                break;
            case 3:
                Read(x);Read(y);
                T.Add(L[x],R[x],y,1,1,dfsClock);
                break;
            case 4:
                Read(x);
                printf("%lld\n",T.Query(L[x],R[x],1,1,dfsClock));
                break;
        } 
    }
    return 0;
}
```

### 一些例题

NOIP2013

