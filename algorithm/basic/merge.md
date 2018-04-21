# 归并思想

> 用队列单调性避免不必要的空间和时间浪费

先来看一道例题

## [\[Noip2011\] 瑞士轮](https://www.luogu.org/problemnew/show/P1309)

### Description

2\*N 名编号为 1~2N 的选手共进行R 轮比赛。每轮比赛开始前，以及所有比赛结束后，都会按照总分从高到低对选手进行一次排名。选手的总分为第一轮开始前的初始分数加上已参加过的所有比赛的得分和。总分相同的，约定编号较小的选手排名靠前。

每轮比赛的对阵安排与该轮比赛开始前的排名有关：第1 名和第2 名、第 3 名和第 4名、……、第2K – 1 名和第 2K名、…… 、第2N – 1 名和第2N名，各进行一场比赛。每场比赛胜者得1 分，负者得 0 分。也就是说除了首轮以外，其它轮比赛的安排均不能事先确定，而是要取决于选手在之前比赛中的表现。

现给定每个选手的初始分数及其实力值，试计算在R 轮比赛过后，排名第 Q 的选手编号是多少。我们假设选手的实力值两两不同，且每场比赛中实力值较高的总能获胜。

### Data Size

对于30% 的数据，1 ≤ N ≤ 100；

对于50% 的数据，1 ≤ N ≤ 10,000 ；

对于100%的数据，1 ≤ N ≤ 100,000，1 ≤ R ≤ 50，1 ≤ Q ≤ 2N，0 ≤ s1, s2, …, s2N≤10^8，1 ≤w1, w2 , …, w2N≤ 10^8。

### Solve

如果用暴力快排 时间复杂度有 $$O(R(n+nlogn))$$ 显然会TLE  
考虑到赢家得一分，输家不得分，即在赢家和输家中其单调性与上一轮相同，那么就可以考虑用一次归并来排序，从而降低时间复杂度至O\(Rn\)  
核心代码

```cpp
struct Player{
    int id,s,w;
    Player(){}
    Player(int _id,int _s,int _w):id(_id),s(_s),w(_w){};
    friend bool operator < (Player a,Player b){
        if(a.s==b.s) return a.id<b.id;
        return a.s>b.s;
    }
}pl[MAXN+10],winner[MAXN+10],loser[MAXN+10];
void Run(void){
    for(int i=1,p=1;i<2*n;i+=2,p++){
        if(pl[i].w>pl[i+1].w) winner[p]=pl[i],loser[p]=pl[i+1];
        else winner[p]=pl[i+1],loser[p]=pl[i];
        winner[p].s++;
    }
}
void Merga(void){
    int p=0,p1=1,p2=1;
    while(p1<=n&&p2<=n){
        ++p;
        if(winner[p1]<loser[p2]) pl[p]=winner[p1++];
        else pl[p]=loser[p2++];
    }
    while(p1<=n) pl[++p]=winner[p1++];
    while(p2<=n) pl[++p]=loser[p2++];
}
```

我们再看一道例题

## [\[Luogu2085\] 最小函数值](https://www.luogu.org/problemnew/show/P2085)

### Description

有n个函数，分别为F1,F2,...,Fn。定义Fi\(x\)=Ai_x^2+Bi_x+Ci \(x∈N\*\)。给定这些Ai、Bi和Ci，请求出所有函数的所有函数值中最小的m个（如有重复的要输出多个）。

### Data Size

数据规模：n,m&lt;=10000

### Solve

根据二次函数的性质，显然这些函数在$$N^*$$上是单调递增的，我们把每个函数看作一个单调队列，归并起来就可以了  
核心代码

```cpp
struct Func{
    int a,b,c;
    Func(){}
    Func(int _a,int _b,int _c):a(_a),b(_b),c(_c){}
    const int Plot(int _x){
        return a*_x*_x+b*_x+c;
    }
}f[MAXN+10];
struct Val{
    int id,val;
    Val(){};
    Val(int _id,int _val):id(_id),val(_val){}
    friend bool operator < (Val a,Val b){
        return a.val<b.val;
    }
};
int n,m;
Heap<Val> q;
int used[MAXN+10];
int main(void){
    scanf("%d%d",&n,&m);
    for(int i=1,x,y,z;i<=n;i++){
        scanf("%d%d%d",&x,&y,&z);
        f[i]=Func(x,y,z);
    }
    for(int i=1;i<=n;i++) q.Insert(Val(i,f[i].Plot(1)));
    int p=1;
    Val u;
    while(p<=m){
        u=q.Top();q.Pop();
        printf("%d ",u.val);
        q.Insert(Val(u.id,f[u.id].Plot(++used[u.id]+1)));//归并过程
        p++;
    }
    return 0;
}
```

前面两题的单调性都比较明显
再看下面这道例题

## [\[Luogu1631\] 序列合并](https://www.luogu.org/problemnew/show/P1631)

### Description

有两个长度都是N的序列A和B，在A和B中各取一个数相加可以得到N^2个和，求这N^2个和中最小的N个。

### Data Size

对于50%的数据中，满足1<=N<=1000；

对于100%的数据中，满足1<=N<=100000。

### Solve

如果暴力算$$O(N^2+2N^2logN)$$肯定会炸，TLE And MLE.我们可以换一种方式看数列
显然有
$$a[1]+b[1]\leqslant a[1]+b[2] \cdot\cdot\cdot \leqslant a[1]+b[n]$$
$$a[2]+b[1]\leqslant a[2]+b[2] \cdot\cdot\cdot \leqslant a[2]+b[n]$$
$$a[3]+b[1]\leqslant a[3]+b[2] \cdot\cdot\cdot \leqslant a[3]+b[n]$$

然后就可以愉快地归并了
核心代码
```cpp
Heap<Que> q;
int n;
int a[MAXN+10],b[MAXN+10];
int main(){
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++) scanf("%d",a+i);
	for(int i=1,x;i<=n;i++) scanf("%d",b+i);
	for(int i=1;i<=n;i++) q.Insert(Que(i,1,a[i]+b[1]));
	Que u;
	for(int i=1;i<=n;i++){
		u=q.Top();q.Pop();
		printf("%d ",u.val);
		q.Insert(Que(u.i,u.j+1,a[u.i]+b[u.j+1]));
	}
	return 0;
}
```
