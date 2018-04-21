# 网络流相关模板

## Dinic

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#define MAXN 200000
const int inf=0x3f3f3f3f;
template <typename T>
inline const T Min(T a,T b) {
	if(a<b) return a;
	return b;
}
template <typename T>
inline void Read(T &x) {
	x=0;
	int p=1;
	char c=getchar();
	for(; !('0'<=c&&c<='9'); c=getchar()) if(c=='-') p=-1;
	for(; '0'<=c&&c<='9'; c=getchar()) x=x*10+c-'0';
	x*=p;
}

namespace Dicnic {
	struct Edge {
		int u,v,cap,nxt;
		Edge() {}
		Edge(int _u,int _v,int _cap,int _nxt):u(_u),v(_v),cap(_cap),nxt(_nxt) {}
	} E[MAXN*10+1];
	int nE,head[MAXN+1];
	int dis[MAXN+1],cur[MAXN+1];
	void Init() {
		nE=0;
		memset(head,-1,sizeof(head));
		memset(cur,-1,sizeof(cur));
	}
	void AddEdge(int u,int v,int c) {
		E[nE]=Edge(u,v,c,head[u]),head[u]=nE++;
		E[nE]=Edge(v,u,0,head[v]),head[v]=nE++;
	}
	void BFS(int s) {
		memset(dis,-1,sizeof(dis));
		std::queue<int> q;
		dis[s]=0;
		q.push(s);
		while(!q.empty()) {
			int v=q.front();
			q.pop();
			for(int i=head[v]; i!=-1; i=E[i].nxt) {
				Edge e=E[i];
				if(e.cap>0&&dis[e.v]==-1) {
					dis[e.v]=dis[v]+1;
					q.push(e.v);
				}
			}
		}
	}
	int DFS(int v,int t,int low) {
		if(v==t) return low;
		for(int &i=cur[v]; i!=-1; i=E[i].nxt) {
			Edge &e=E[i],&reve=E[i^1];
			if(e.cap>0&&dis[e.v]>dis[v]) {
				int d=DFS(e.v,t,Min(low,e.cap));
				if(d>0) {
					e.cap-=d;
					reve.cap+=d;
					return d;
				}
			}
		}
		return 0;
	}
	int MaxFlow(int s,int t) {
		int flow=0,f=0;
		while(1) {
			BFS(s);
			if(dis[t]==-1) return flow;
			memcpy(cur,head,sizeof(cur));
			while((f=DFS(s,t,inf))>0) flow+=f;
		}
	}
}
```



