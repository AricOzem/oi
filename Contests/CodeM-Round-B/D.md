## C 景区路线规划

## 题目描述

游乐园被描述成一张$$n$$个点，$$m$$条边的无向图（无重边，无自环）。每个点代表一个娱乐项目，第$$i$$个娱乐项目需要耗费$$c_i$$​​分钟的时间，会让小 y 和妹子的开心度分别增加$$h1_i$$​​,$$h2_i$$​​，他们俩初始的开心度都是$$0$$。每条边代表一条路，第$$i$$条边连接编号为$$x_i$$,$$y_i$$​​的两个娱乐项目，从$$x_i$$​​走到$$y_i$$​​或者从$$y_i$$​​走到$$x_i$$​​耗费的时间都是$$t_i$$​​分钟。小 y 和妹子预计在游乐园里玩$$k$$分钟。最开始的时候，小 y 和妹子会等概率的随机选择一个娱乐项目开始玩，每玩完一个项目后，小 y 和妹子会等概率的随机选择一个可以从当前项目直达的且来得及玩的项目作为下一个项目。如果玩完一个项目后周围没有可以直达的且来得及玩的项目，小 y 和妹子就会提前结束游玩。 请你分别计算小 y 和妹子在游玩结束后开心度的期望。

## 输入格式

第一行给出三个空格隔开的整数，分别表示$$n,m,k$$  
接下来的$$n$$行，每行三个空格隔开的整数，分别表示$$c_i,h1_i,h2_i$$  
接下来的$$m$$行，每行三个空格隔开的整数，分别表示$$x_i,y_i,t_i$$

## 输出格式

两个用空格隔开的实数，分表表示小 y 和妹子开心度的期望，精确到小数点后$$5$$位。

## 样例

### 样例输入

```
5 4 60
25 12 83
30 38 90
16 13 70
22 15 63
50 72 18
2 1 7
3 1 7
4 3 1
5 3 10
```

### 样例输出

```
39.20000 114.40000
```

## 数据范围与提示

* $$n \leq 100, 1 \times 60 \leq k \leq 8 \times 60$$
* $$10 \leq c_i \leq 60, 0 < h1_i, h2_i \leq 100$$
* $$0 \lt t_i \leq 15$$

## Solve

暴力记忆化搜索

```cpp
#include<cstdio>
#include<cstring>
#define MAXN 200
#define MAXE 3000
#define MAXK 800
int n,m,k;
int c[MAXN+10],h1[MAXN+10],h2[MAXN+10];
struct Edge{
	int v,w,nxt;
	Edge(){}
	Edge(int _v,int _w,int _nxt):v(_v),w(_w),nxt(_nxt){}
}E[MAXE+10];int nE,head[MAXE+10];
inline void EdgeInit(){
	nE=0;
	memset(head,-1,sizeof(head));
}
inline void AddEdge(int u,int v,int w){
	E[nE]=Edge(v,w,head[u]);head[u]=nE++;
}
struct State{
	double a1,a2;
	State():a1(0),a2(0){}
	State(double _a1,double _a2):a1(_a1),a2(_a2){}
	friend State operator +(State a,State b){
		return State(a.a1+b.a1,a.a2+b.a2);
	}
	const State operator / (const int b){
		return State(a1/b,a2/b);
	}
}rem[MAXN+10][MAXK+10];
bool vis[MAXN+10][MAXK+10];
State dfs(int u,int t){
	State ret=State(h1[u],h2[u]);int cnt=0;
	State d;
	if(vis[u][t]) return  rem[u][t];
	for(int i=head[u],v=E[i].v;i!=-1;i=E[i].nxt,v=E[i].v)
		if(t>=E[i].w+c[v]){
			d=d+dfs(v,t-E[i].w-c[v]);
			cnt++;
		}
	if(cnt>0) d=d/cnt;
	rem[u][t]=ret+d;vis[u][t]=true;
	return ret+d;
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
		scanf("%d%d%d",c+i,h1+i,h2+i);
	EdgeInit();
	for(int i=1,x,y,w;i<=m;i++){
		scanf("%d%d%d",&x,&y,&w);AddEdge(x,y,w);AddEdge(y,x,w);
	}
	for(int i=1;i<=n;i++) AddEdge(0,i,0);
	memset(vis,false,sizeof(vis));
	State ans=dfs(0,k);
	printf("%.5lf %.5lf \n",ans.a1,ans.a2);
	return 0;
}
```



