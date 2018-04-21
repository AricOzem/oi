# 欧拉路径与回路

# 引入

若图G中存在这样一条路径，使得它恰通过G中每条边一次,则称该路径为欧拉路径。若该路径是一个圈，则称为欧拉\(Euler\)回路。

# 判定

判断欧拉路径是否存在的方法

有向图：图连通，有一个顶点出度大入度1，有一个顶点入度大出度1，其余都是出度=入度。

无向图：图连通，只有两个顶点是奇数度，其余都是偶数度的。

判断欧拉回路是否存在的方法

有向图：图连通，所有的顶点出度=入度。

无向图：图连通，所有顶点都是偶数度。

# 解决

### 欧拉回路

以[UOJ \#117 欧拉回路](http://uoj.ac/problem/117)为例

```cpp
#include<cstdio>
#include<cstring>
#define MAXN 200000
#define MAXE 400000
struct Edge{
	int v,nxt;
	Edge(){}
	Edge(int _v,int _nxt):v(_v),nxt(_nxt){}
}E[MAXE+10];int nE,head[MAXE+10];bool used[MAXE+10];//used标记已经使用过的边 就是为了删边
inline void EdgeInit(){
	nE=0;
	memset(head,-1,sizeof(head));
	memset(used,false,sizeof(used));
}
inline void AddEdge(int u,int v){
	E[nE]=Edge(v,head[u]);head[u]=nE++;
}

int deg[MAXN+10],tour[MAXE+10],tourIndex;
namespace DirectGraph{
	int n,m;
	void dfs(int u){
		/*for(int &i=head[u],v=E[i].v,id=i+1;i!=-1;i=E[i].nxt,v=E[i].v,id=i+1)//如果这样i地址引用总会发生一些意想不到的变量赋值问题 所以还是采用下面的while形式
		if(!used[i]){
			used[i]=true;
			dfs(v);
			tour[++tourIndex]=id;
		}*/
		int &e=head[u],id;//地址引用是为了方便删边
		while(e!=-1){
			if(used[e]) e=E[e].nxt;
			else {
				used[e]=true;id=e+1;
				dfs(E[e].v);
				tour[++tourIndex]=id;
			}
		}
	}
	inline bool Solve(){
		tourIndex=0;
		EdgeInit();
		scanf("%d%d",&n,&m);
		for(int i=1,x,y;i<=m;i++){
			scanf("%d%d",&x,&y);
			AddEdge(x,y);
			deg[x]--;deg[y]++;
		}
		for(int i=1;i<=n;i++) if(deg[i]!=0) return false;//所有点入度等于出度
		int u=1; while(head[u]==-1&&u<=n) u++; dfs(u);
		for(int i=1;i<=n;i++) if(head[i]!=-1) return false;  
		return true;
	}
}
namespace UndirectGraph{
	int n,m;
	inline int EdgeId(int i){
		int id=i+2>>1;
		if(i&1) return -id;return id;
	}
	void dfs(int u){
		int &e=head[u],id;
		while(e!=-1){
			if(used[e]) e=E[e].nxt;
			else {
				used[e]=used[e^1]=true;id=EdgeId(e);
				dfs(E[e].v);
				tour[++tourIndex]=id;
			}
		}
	}
	inline bool Solve(){
		tourIndex=0;
		EdgeInit();
		scanf("%d%d",&n,&m);
		for(int i=1,x,y;i<=m;i++){
			scanf("%d%d",&x,&y);
			AddEdge(x,y);AddEdge(y,x);
			deg[x]++;deg[y]++;
		}
		for(int i=1;i<=n;i++) if(deg[i]&1) return false;//所有点度数为偶数
		int u=1; while(head[u]==-1&&u<=n) u++; dfs(u);
		for(int i=1;i<=n;i++) if(head[i]!=-1) return false;
		return true;
	}
}
int main(){
	int t;
	scanf("%d",&t);
	if(t==1){
		if(UndirectGraph::Solve()){
			puts("YES");
			for(int i=tourIndex;i>0;i--) printf("%d ",tour[i]);
		}else puts("NO");
	} else {
		if(DirectGraph::Solve()) {
			puts("YES");
			for(int i=tourIndex;i>0;i--) printf("%d ",tour[i]);
		}else puts("NO");
	}
	return 0;
}
```

### 欧拉路径
同上，只是修改判定条件





