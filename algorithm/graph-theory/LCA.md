# LCA 最近公共祖先算法

## 引入

最近公共祖先的概念：

在一棵没有环的树上，每个节点肯定有其父亲节点和祖先节点，而最近公共祖先，就是两个节点在这棵树上深度最大的公共的祖先节点。

换句话说，就是两个点在这棵树上距离最近的公共祖先节点。并且我们定义一个节点也是其自己的后代，因此如果v是u的后代，那么u就是v和u的最近公共祖先。

所以LCA主要是用来处理当两个点仅有唯一一条确定的最短路径时的路径。

LCA的三种算法

| 算法 | 时间 | 空间 | 种类 |
| --- | --- | --- | --- |
| 倍增 | 预处理 O\(n log n\)/每组询问 O\(log n\) | O\(n log n\) | 在线 |
| 树剖 | 预处理 O\(n\)/每组询问 O\(log n\) | O\(n\) | 在线 |
| tarjan | O\(n + q\) | O\(n\) | 离线 |

## 倍增

和ST表和快速幂差不多的思想，先把两个结点调整到同一深度，然后在2幂次式往上跳

### 模板（省去dep计算部分）

```cpp
inline void Init() {//预处理
    for(int j=1; j<=MAXLOG; j++)
        for(int i=1; i<=n; i++)
            pfa[i][j]=pfa[pfa[i][j-1]][j-1];
}
inline int LCA(int u,int v) {
    if(u==v) return u;
    if(dep[u]<dep[v]) Swap(u,v);
    int d=dep[u]-dep[v];
    for(int i=0; (1<<i)<=d; i++) if((1<<i)&d) u=pfa[u][i];
    if(u==v) return u;
    for(int i=MAXLOG; i>=0; i--)
        if(pfa[u][i]!=pfa[v][i]) u=pfa[u][i],v=pfa[v][i];
    return pfa[u][0];
}
```

## 树链剖分

不同于倍增，利用重链快速跳祖先  
![](/assets/HLD-LCA-2.JPG)

例：上图求LCA（A,B）如果 A,B 重链顶端节点不同 重链顶点深度大的再跳到上面一条重链  
如果 A,B 在同一条链上 显然深度小的为公共祖先。

为什么要用重链？ 普通链划分可能并不优秀,如下图

![](/assets/HLD-LCA-1.JPG)

## 核心代码

```cpp
int lca(int u,int v) {
    while(chainTop[u]!=chainTop[v]) {//重链顶端节点不同 重链顶点深度大的再跳到上面一条重链
        if(dep[chainTop[u]]<dep[chainTop[v]]) Swap(u,v);
        u=fa[chainTop[u]];
    }
    if(dep[u]<dep[v]) return u;//在同一条链上 显然深度小的为公共祖先
    return v;
}
```

树链剖分相关内容参见 [图论/树链剖分](/algorithm/graph-theory/HLD.md)

## Tarjan

### 伪代码

```cpp
Tarjan(u)//join和find为并查集合并函数和查找函数
{
    for each(u,v)    //访问所有u子节点v
    {
        Tarjan(v);        //继续往下遍历
        join(v,u);    //合并v到u上(不可调换)
        标记v被访问过;
    }
    for each(u,e)    //访问所有和u有询问关系的e
    {
        如果e被访问过;
        u,e的最近公共祖先为find(e);
    }
}
```

简单提示：  
如果u是v的祖先，那么u就是v的最近公共祖先。所以我们按一定的顺序递归就可以得到结果。同时不记录与询问无关的结果

### 模板:

> N、M、S，分别表示树的结点个数、询问的个数和树根结点的序号  
> N-1行每行包含两个正整数x、y表示x结点和y结点之间有一条直接连接的边  
> M行每行包含两个正整数a、b，表示询问a结点和b结点的最近公共祖先

```cpp
#include<cstdio>
#include<cstring>
#define MAXN 500000
#define MAXM 500000
struct LCA {
    struct Edge {
        int v,nxt;
        Edge() {}
        Edge(int _v,int _nxt):v(_v),nxt(_nxt) {}
    } E[MAXN*4+10];
    int nE,Ehead[MAXN*4+10];
    struct Ans{
        int v,val,nxt;
        Ans():val(0){}
        Ans(int _v,int _nxt):v(_v),nxt(_nxt){}
    }A[MAXM*4+10];
    int nA,Ahead[MAXM*4+10];

    int fa[MAXN+10];
    int vis[MAXN+10];

    void init(){
        nE=0,nA=0;
        memset(Ehead,-1,sizeof(Ehead));
        memset(Ahead,-1,sizeof(Ahead));
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=MAXN;i++) fa[i]=i;
    }

    void addEdge(int u,int v){
        E[nE]=Edge(v,Ehead[u]); Ehead[u]=nE++;
        E[nE]=Edge(u,Ehead[v]); Ehead[v]=nE++;
    }
    void addQuery(int u,int v){
        A[nA]=Ans(v,Ahead[u]); Ahead[u]=nA++;
        A[nA]=Ans(u,Ahead[v]); Ahead[v]=nA++;
    }

    int find(int x){
        int r,t;
        for(r=x;r!=fa[r];r=fa[r]);
        while(x!=fa[x]) t=fa[x],fa[x]=r,x=t; 
        return r;
    }
    void join(int i,int j){
        int p=find(i),q=find(j);
        fa[p]=q;
    }

    void tarjan(int u){
        vis[u]=1;
        for(int i=Ehead[u];i!=-1;i=E[i].nxt)
            if(!vis[E[i].v]){
                tarjan(E[i].v);
                join(E[i].v,u);
            }
        for(int i=Ahead[u];i!=-1;i=A[i].nxt){
            if(vis[A[i].v]==2){
                A[i].val=find(A[i].v);
                if(i&1) A[i-1].val=A[i].val;//奇数 
                else A[i+1].val=A[i].val;//偶数 
            }
        }
        vis[u]=2;
    }
}lca;
int N,M,S;
int main() {
    scanf("%d%d%d",&N,&M,&S);
    lca.init();
    for(int i=1,x,y; i<N; i++) {
        scanf("%d%d",&x,&y);
        lca.addEdge(x,y);
    }
    for(int i=1,a,b;i<=M;i++){
        scanf("%d%d",&a,&b);
        lca.addQuery(a,b);
    }
    lca.tarjan(S);
    for(int i=1;i<=M;i++)
        printf("%d\n",lca.A[i*2-2].val);
    return 0;
}
```



