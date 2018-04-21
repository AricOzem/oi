# 二分图

## 定义

就是顶点集V可分割为两个互不相交的子集，并且图中每条边依附的两个顶点都分属于这两个互不相交的子集，两个子集内的顶点不相邻。

## 判断

无向图G为二分图的充分必要条件是，G至少有两个顶点，且其所有回路的长度均为偶数。

实际方法 DFS 染色

```cpp
int color[MAXN+10];
bool dfs(int u,int _fa){
    for(int i=head[u],v=E[i].v;i!=-1;i=E[i].nxt,v=E[i].v)if(v!=_fa){
        if(color!=0) return false;
        color[v]=-color[u];
        if(!dfs(v,u)) return false;
    }
    return true;
}
```

## 应用

### 二分图匹配

#### 解决

**匈牙利算法**

```cpp
namespace BGMM {
    int mark[MAXN<<1|10],vis[MAXN<<1|10];
    void Init() {
        memset(mark,0,sizeof(mark));
    }
    bool TryMatch(int u) {
        for(int i=head[u],v=E[i].v; i!=-1; i=E[i].nxt,v=E[i].v)
            if(!vis[v]) {
                vis[v]=1;
                if(!mark[v]||TryMatch(mark[v])) {
                    mark[v]=u;
                    return true;
                }
            }
        return false;
    }
    bool Match(int n){
        Init();int tot=0;
        for(int i=1;i<=n;i++){
            memset(vis,false,sizeof(vis));
            if(TryMatch(i)) tot++;
        }
        return tot==n; 
    }
}
```

求解最大匹配 不断回溯调整 如果无法调整 则不存在完美匹配

**网络流**

超级源向一个结点集 中的点连容量为1的边，另一个结点集向超级汇连容量为1的边

### 最小点覆盖

在一个二分图中,选取最少的点可以把所有的边覆盖, 点的最少个数就是最小点覆盖

等于最大匹配 

感性理解：即另一边匹配的节点肯定覆盖所有边，左右两边匹配节点一定是相等的

#### 最大独立集

无向图G的一个点数最多点集，使得任两个在该集合中的点在原图中不相邻

等于点数-最大匹配

感性理解：留下的点必然不能匹配，不能匹配的也只有这些点，再加一个点根据匈牙利算法肯定会时匹配数增加

#### 最大团

就是选出一些顶点，这些顶点两两之间都有边，使得选出的这个顶点集合最大。

等于补图的最大独立集

补图边集对于二分图中左边一点x和右边一点y，若x和y之间有边，那么在补图中没有，否则有。

感性理解：因为最大独立集两两不相邻，所以最大独立集的补图两两相邻

