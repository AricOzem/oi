# B 小X的密室
小 X 正困在一个密室里，他希望尽快逃出密室。

密室中有 N 个房间，初始时，小 X 在 11 号房间，而出口在 N 号房间。

密室的每一个房间中可能有着一些钥匙和一些传送门，一个传送门会单向地创造一条从房间 XX 到房间 YY 的通道。另外，想要通过某个传送门，就必须具备一些种类的钥匙（每种钥匙都要有才能通过）。幸运的是，钥匙在打开传送门的封印后，并不会消失。

然而，通过密室的传送门需要耗费大量的时间，因此，小 X 希望通过尽可能少的传送门到达出口，你能告诉小 X 这个数值吗？

另外，小 X 有可能不能逃出这个密室，如果是这样，请输出 "No Solution"。

## 输入格式

第一行三个整数 N,M,K分别表示房间的数量、传送门的数量以及钥匙的种类数。

接下来 N 行，每行 K 个 0 或 1，若第 i 个数为 1，则表示该房间内有第 i 种钥匙，若第 i 个数为 0，则表示该房间内没有第 i 种钥匙。

接下来 M 行，每行先读入两个整数 X,Y表示该传送门是建立在 X 号房间，通向 Y 号房间的，再读入 K 个 0 或 1，若第 i 个数为 1，则表示通过该传送门需要 i 种钥匙，若第 i 个数为 0，则表示通过该传送门不需要第 i 种钥匙。

## 输出格式

输出一行一个 "No Solution"，或一个整数，表示最少通过的传送门数。

## 数据规模与约定

![](/assets/jisuankenoip20174b.png)
### 样例输入1
```
3 3 2
1 0
0 1
0 0
1 3 1 1
1 2 1 0
2 3 1 1
```
### 样例输出1
```
2
```
### 样例输入2
```
20 40 0
10 18 
18 14 
19 13 
4 14 
13 10 
5 18 
14 1 
13 13 
10 16 
19 11 
11 15 
10 18 
5 8 
12 19 
7 8 
18 6 
14 5 
9 5 
2 17 
13 14 
18 15 
8 18 
7 1 
13 5 
4 6 
17 4 
1 4 
10 10 
13 8 
19 2 
4 9 
3 3 
5 10 
17 5 
12 8 
19 11 
3 16 
17 10 
18 16 
13 13
``` 
### 样例输出2
```
No Solution
```
### 样例输入3
```
20 50 0
8 10 
7 17 
5 11 
14 20 
20 16 
8 19 
12 11 
18 7 
17 5 
4 15 
16 11 
11 8 
10 12 
8 9 
16 8 
3 16 
1 6 
3 20 
6 10 
11 12 
6 8 
18 17 
14 17 
3 11 
4 19 
9 2 
8 6 
13 2 
5 2 
12 19 
8 10 
14 7 
6 12 
6 4 
13 2 
8 7 
13 19 
17 9 
3 14 
18 20 
2 14 
4 17 
20 15 
14 15 
2 15 
7 20 
12 12 
18 10 
15 9 
15 9 
```
### 样例输出3
```
4
```
## Solve
考虑用二进制压缩钥匙信息用按位或来进行获取钥匙和检查是否可以使用传送门。
暴力BFS+剪枝 显然重复到达一个房间的钥匙数应当是递增的，把不符合要求的剪掉即可。
```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#define MAXN 5000
#define MAXM 6000
#define MAXK 10
int n,m,k;
template <typename T>
inline void Read(T &x) {
	x=0;
	int p=1;
	char c=getchar();
	for(; !('0'<=c&&c<='9'); c=getchar()) if(c=='-') p=-1;
	for(; '0'<=c&&c<='9'; c=getchar()) x=x*10+c-'0';
	x*=p;
}
struct Edge {
	int v,needKey,nxt;
	Edge() {}
	Edge(int _v,int _needKey,int _nxt):v(_v),needKey(_needKey),nxt(_nxt) {}
} e[MAXM+10];
int nE,head[MAXN+10];
inline void AddEdge(int u,int v,int needKey) {
	e[nE]=Edge(v,needKey,head[u]);
	head[u]=nE++;
}
struct State {
	int p;
	int key;
	int step;
	State() {}
	State(int _p,int _key,int _step):p(_p),key(_key),step(_step) {}
	inline void print(){
		printf("----\n%d\n",p);
		int tmp=key;
		while(tmp>0) {
			printf("%d ",tmp&1);
			tmp>>=1;
		}
		printf("\n%d\n-----\n",step);
	}
};
int key[MAXN+1];
int last[MAXN+10];
bool vis[MAXN+10];
inline int BFS(int s,int t) {
	std::queue<State> q;
	q.push(State(1,key[1],0));
	State u;
	int tmp;
	while(!q.empty()) {
		u=q.front();
		q.pop();
		//u.print();
		if(u.p==t) return u.step;
		for(int i=head[u.p]; i!=-1; i=e[i].nxt) {
			if((u.key|e[i].needKey)==u.key) {
				tmp=u.key|key[e[i].v];
				if(vis[e[i].v]&&(tmp|last[e[i].v])==last[e[i].v]) continue;
				vis[e[i].v]=true;
				last[e[i].v]=tmp;
				q.push(State(e[i].v,tmp,u.step+1));
			}
		}
	}
	return -1;
}
int main() {
	memset(head,-1,sizeof(head));
	Read(n);
	Read(m);
	Read(k);
	for(int i=1,x; i<=n; i++)
		for(int j=0; j<k; j++) {
			Read(x);
			key[i]|=x<<j;
		}
	for(int i=1,x,y,t,p; i<=m; i++) {
		Read(x);
		Read(y);
		p=0;
		for(int j=0; j<k; j++) {
			Read(t);
			p|=t<<j;
		}
		AddEdge(x,y,p);
	}
	int ans=BFS(1,n);
	if(ans>0) printf("%d\n",ans);
	else puts("No Solution");
	return 0;
}
```