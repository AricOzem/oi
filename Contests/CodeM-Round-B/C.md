# C 送外卖2

## 题目描述

一张$$n$$个点$$m$$条有向边的图上，有$$q$$个配送需求，需求的描述形式为$$(s_i,t_i,l_i,r_i)$$，即需要从点$$s_i$$​​送到$$t_i$$​​， 在时刻$$l_i$$​​之后（包括$$l_i$$​​）可以在$$s_i$$​​领取货物，需要在时刻$$r_i$$​​之前（包括$$r_i$$​）送达$$t_i$$​​，每个任务只需完成一次。

图上的每一条边均有边权，权值代表通过这条边消耗的时间。在时刻$$0$$有一个工作人员在点$$1$$上，求他最多能完成多少个配送任务。

在整个过程中，可以认为领货跟交货都是不消耗时间的，时间只花费在路程上。当然在一个点逗留也是允许的。

## 输入格式

第一行，三个正整数$$n , m , q (2\leq n\leq 20, 1\leq m\leq 400, 1\leq q\leq 10)$$。  
接下来$$m$$行，每行三个正整数 $$u_i , v_i , c_i (1\leq u_i,v_i\leq n, 1\leq c_i\leq 20000)$$，表示有一条从$$u_i$$到$$v_i$$​​耗时为$$c_i$$​​的有向边。  
接下来$$q$$行，每行四个正整数$$s_i , t_i , l_i , r_i (1\leq s_i,t_i\leq n, 1\leq l_i\leq r_i\leq 10^6)$$，描述一个配送任务。

## 输出格式

一个整数，表示最多能完成的任务数量。

## 样例

### 样例输入

```
5 4 3
1 2 1
2 3 1
3 4 1
4 5 1
1 2 3 4
2 3 1 2
3 4 3 4
```

### 样例输出

```
2
```

#### 样例解释

工作人员可以在时刻 1 到达点 2 ，领取第二个货物后在时刻 2 到达点 3 后交货，逗留到时刻 4 ，领取第三个货物，在时刻 4 到达点 4 并交货。

## Solve

$$n=20,q=10$$ 不如爆搜吧。怎么设计状态呢 货物有三种状态 未拿 在运输 运输完毕 考虑三进制表示 一共有$$3^{10}=59049$$状况 是可以承受的 我们贪心希望相同情况下需要时间最短，设计状态$$f[i][j]$$为最后位置为i，达到状态j的最短时间 然而就可以开始大力转移了
```cpp
#include<cstdio>
#include<cstring>
#define IINF 0x3f
#define MAXN 20
#define MAXM 400
#define MAXQ 10
#define MAXS 177150
int n,m,q;
int f[MAXN+10][MAXS];
int dis[MAXN+10][MAXN+10];
int pow3[MAXN+10];
int s[MAXQ+1],t[MAXQ+1],l[MAXQ+1],r[MAXQ+1];
int rlim,ans;
template <typename T>
inline T Max(T a,T b){
	if(a>b) return a;
	return b;
}
inline void Floyd(){
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(dis[i][j]>dis[i][k]+dis[k][j]) 
					dis[i][j]=dis[i][k]+dis[k][j];
}
inline int State(int val,int k){
	for(int i=10;i>k;i--)
		while(val>=pow3[i]) val-=pow3[i];
	if(val>=pow3[k]*2) return 2;
	else if(val>=pow3[k]) return 1;
	else return 0;
}
inline int Amount(int val){
	int cnt=0;
	for(int i=10;i>0;i--){
		if(val>=pow3[i]*2) cnt++;
		while(val>=pow3[i]) val-=pow3[i];
	}
	return cnt;
}
inline void dfs(int u,int status,int time){
	if(time>rlim||ans==q) return ;
	for(int i=1;i<=q;i++)if(l[i]<=time&&time<=r[i]){
		if(u==s[i]&&State(status,i)==0) status+=pow3[i];
		if(u==t[i]&&State(status,i)==1) status+=pow3[i];
	}
	if(f[u][status]<=time) return ;
	f[u][status]=time;
	ans=Max(ans,Amount(status));
	for(int i=1;i<=q;i++)if(time+dis[u][t[i]]<=r[i]){
		if(State(status,i)==0) dfs(s[i],status,Max(time+dis[u][s[i]],l[i]));
		if(State(status,i)==1) dfs(t[i],status,time+dis[u][t[i]]);
	}
}
int main(){
	scanf("%d%d%d",&n,&m,&q);
	memset(dis,IINF,sizeof(dis));for(int i=1;i<=n;i++)dis[i][i]=0;
	memset(f,IINF,sizeof(f));
	pow3[0]=1;for(int i=1;i<=10;i++) pow3[i]=pow3[i-1]*3;
	for(int i=1,x,y,w;i<=m;i++){
		scanf("%d%d%d",&x,&y,&w);
		if(dis[x][y]>w) dis[x][y]=w;
	}
	Floyd();
	for(int i=1;i<=q;i++){
		scanf("%d%d%d%d",s+i,t+i,l+i,r+i);
		if(rlim<r[i]) rlim=r[i];
	}
	dfs(1,0,0);
	printf("%d\n",ans);
	return 0;
}
```