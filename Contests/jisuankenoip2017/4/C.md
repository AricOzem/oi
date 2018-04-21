# C 小X的佛光
小 X 是远近闻名的学佛，平日里最喜欢做的事就是蒸发学水。

小 X 所在的城市 X 城是一个含有 N 个节点的无向图，同时，由于 X 国是一个发展中国家，为了节约城市建设的经费，X 国首相在建造 X 城时只建造 N – 1 条边，使得城市的各个地点能够相互到达。

小 X 计划蒸发 Q 天的学水，每一天会有一名学水从 A 地走到 B 地，并在沿途各个地点留下一个水塘。此后，小 X 会从 CC 地走到 BB 地，并用佛光蒸发沿途的水塘。由于 X 城是一个学佛横行的城市，学水留下的水塘即使没有被小 X 蒸发，也会在第二天之前被其他学佛蒸发殆尽。

现在，小 X 想要知道，他每一天能够蒸发多少水塘呢?

## 输入格式

第一行三个整数 N,Q,num，分别表示 X 城地点的个数，小 X 蒸发学水的天数，以及测试点编号。注意，测试点编号是为了让选手们更方便的获得部分分，你可能不需要用到这则信息，在下发的样例中，测试点编号的含义是该样例满足某一测试点限制。

接下来 N – 1 行，每行两个整数 X,Y，表示 X 地与 Y 地之间有一条边。

接下来 Q 行，每行三个整数 A,B,C，表示一天中，有一名学水从 A 地走到 B 地，而小 X 会从 C 地走到 B 地。

## 输出格式

输出 Q 行，每行一个整数，表示小 X 能够蒸发的水塘数。

## 数据规模与约定

特殊性质 11：第 i条边连接第 i 和第 i + 1 个地点。

特殊性质 22：A = C。

## 样例输入
```
3 3 1
1 2
2 3
1 2 3
1 1 3
3 1 3
```
## 样例输出
```
1
1
3
```
## Solve
求路径上点的交集
显然答案为(LEN(LCA(A,B))+LEN(LCA(C,B))-LEN(LCA(A,C))/2+1
在线倍增一发
注意要DFS要开栈 否则会RE
```cpp
#pragma comment(linker, "/STACK:102400000,102400000")
#include<cstdio>
#include<cstring>
#define MAXN 500000
#define MAXE 500000
#define MAXLOG 20
template <typename T> inline void Swap(T &a,T &b) {
	T t=a;
	a=b,b=t;
}
template <typename T> inline void Read(T &x) {
	x=0;
	int p=1;
	char c=getchar();
	for(; !('0'<=c&&c<='9'); c=getchar()) if(c=='-') p==-1;
	for(; '0'<=c&&c<='9'; c=getchar()) x=x*10+c-'0';
	x*=p;
}
int n,q,num;
struct Edge {
	int v,nxt;
	Edge() {}
	Edge(int _v,int _nxt):v(_v),nxt(_nxt) {};
} E[MAXE+10];
int nE,head[MAXN+10];
inline void Link(int u,int v) {
	E[nE]=Edge(v,head[u]);
	head[u]=nE++;
	E[nE]=Edge(u,head[v]);
	head[v]=nE++;
}
int pfa[MAXN+10][MAXLOG+1],dep[MAXN+10];
inline void dfs(int u,int _fa) {
	pfa[u][0]=_fa;
	dep[u]=dep[_fa]+1;
	for(int i=head[u],v=E[i].v; i!=-1; i=E[i].nxt,v=E[i].v) if(v!=_fa) dfs(v,u);
}
inline void Init() {
	for(int j=1; j<=MAXLOG; j++)
		for(int i=1; i<=n; i++)
			pfa[i][j]=pfa[pfa[i][j-1]][j-1];
}
inline int lca(int u,int v) {
	if(u==v) return u;
	if(dep[u]<dep[v]) Swap(u,v);
	int d=dep[u]-dep[v];
	for(int i=0; (1<<i)<=d; i++) if((1<<i)&d) u=pfa[u][i];
	if(u==v) return u;
	for(int i=MAXLOG; i>=0; i--)
		if(pfa[u][i]!=pfa[v][i]) u=pfa[u][i],v=pfa[v][i];
	return pfa[u][0];
}
inline int Calc(int u,int v) {
	int t=lca(u,v);
	return dep[u]+dep[v]-(dep[t]<<1);
}
int main() {
	Read(n);
	Read(q);
	Read(num);
	memset(head,-1,sizeof(head));
	for(int i=1,x,y; i<n; i++) {
		Read(x);
		Read(y);
		Link(x,y);
	}
	dfs(1,1);
	//for(int i=1; i<=n; i++) printf("%d ",dep[i]);
	Init();
	for(int i=1,a,b,c; i<=q; i++) {
		Read(a);Read(b);Read(c);
        printf("%d\n",(Calc(a,b)+Calc(c,b)-Calc(a,c))/2+1);
		//printf("%d\n",(s1+s2-s3)/2+1);
	}
	return 0;
}
```