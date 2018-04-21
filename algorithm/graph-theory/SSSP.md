# SSSP 单源最短路
## 引入
给定一个带权有向图G=（V,E），其中每条边的权是一个实数。另外，还给定V中的一个顶点，称为源。现在要计算从源到其他所有各顶点的最短路径长度。这里的长度就是指路上各边权之和。这个问题通常称为单源最短路径问题。
## 模板
### Dijkstra（+堆优化）:
```cpp
#include<cstdio>
#include<cstring>
#define iinf 0x3f
#define inf 0x3f3f3f3f
#define MAXN 100000
struct Dijkstra{
	struct Edge{
		int v,c,nxt;
		Edge(){}
		Edge(int _v,int _c,int _nxt):v(_v),c(_c),nxt(_nxt){}
	}e[MAXN+11];
	struct Node{
		int num;
		int key;
		Node(){}
		Node(int _num,int _key):num(_num),key(_key){};
		friend bool operator <(Node a,Node b){
			return a.num>b.num;
		}
	};
	struct MinHeap{
	    Node n[MAXN+11];
		int last;
		inline void swap(Node &a,Node &b){
			Node t=a;a=b;b=t;
		}
		int Top(){
			return n[1].key;
		}
		void Insert(Node x){
			n[++last]=x;
			int now=last;
			while(n[now].num<n[now>>1].num&&now>1){
				swap(n[now],n[now>>1]);now>>=1;
			}
		}
		void Pop(){
			if(last==0) return;
			n[1]=n[last--];
			int now=2;
			while(now<=last){
				if (n[now].num>n[now+1].num) now++;
				if (n[now].num<n[now>>1].num) {
					swap(n[now],n[now>>1]); now<<=1;
				}
				else break;
			}
		}
		bool Empty(){
			return last==0;
		}
	}q;
	int nE,head[MAXN+11],dis[MAXN+11];
	bool vis[MAXN+11];
	void init(){
		nE=0;
		memset(head,-1,sizeof(head));
	}
	void AddEdge(int u,int v,int c){
		e[nE]=Edge(v,c,head[u]);head[u]=nE++;
		e[nE]=Edge(u,c,head[v]);head[v]=nE++;
	}
	void SSSP(int s){
		memset(dis,iinf,sizeof(dis));
		memset(vis,false,sizeof(vis));
		dis[s]=0;
		q.Insert(Node(0,s));
		int u,v;
		while(!q.Empty()){
			u=q.Top();q.Pop();
			if(vis[u]) continue;
			vis[u]=true;
			for(int i=head[u];i!=-1;i=e[i].nxt){
				int v=e[i].v;
				if(dis[v]>dis[u]+e[i].c){
					dis[v]=dis[u]+e[i].c;
					q.Insert(Node(dis[v],v));
				}
			}
		}
	}
}net;
int main(){
	int n,m;
	while(~scanf("%d%d",&n,&m)){
		int s,t;
		net.init();
		for(int i=1,u,v,c;i<=m;i++){
			scanf("%d%d%d",&u,&v,&c);
			net.AddEdge(u,v,c);
		}
		scanf("%d%d",&s,&t);
		net.SSSP(s);
		if(net.dis[t]!=inf)
			printf("%d\n",net.dis[t]);
		else puts("-1");
	}
	return 0;
}
```
### SPFA(不加优化)
```cpp
#include<cstdio>
#include<queue>
#include<cstring>
#define MAXN 10000
struct Edge{
	int from;
	int to;
	int cost;
}e[MAXN*50+1];
int N,M,S,tot;
int nxt[MAXN*50+1],head[MAXN*50+1],dis[MAXN<<1];
bool vis[MAXN+1];
inline void link(int from,int to,int cost){
	e[++tot]={from,to,cost};
	nxt[tot]=head[from];
	head[from]=tot;
}
inline void spfa(int s){
	memset(dis,0x7f,sizeof(dis));
	dis[s]=0;
	std::queue<int>q;
	vis[s]=1;
	q.push(s);
	int now,then;
	while(!q.empty()){
		now=q.front();
		q.pop();
		vis[now]=0;
		for(int i=head[now];i!=0;i=nxt[i]){
			then=e[i].to;
			if(dis[then]>dis[now]+e[i].cost){
				dis[then]=dis[now]+e[i].cost;
				if(!vis[then]){
					vis[then]=1;
					q.push(then);
				}
			}
		}
	}
}
int main(){
	int N,M,S,x,y,z;
	scanf("%d%d%d",&N,&M,&S);
	while(M--){
		scanf("%d%d%d",&x,&y,&z);
		link(x,y,z);
	}
	spfa(S);
	for(int i=1;i<=N;i++){
		printf("%d ",dis[i]);
	}
	return 0;
}
```
## 原理介绍
基本原理：运用三角不等式进行松弛操作 $$dis[v]=\min (dis[u]+e[i].cost)$$