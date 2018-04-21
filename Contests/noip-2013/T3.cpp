```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define MAXN 10000
#define MAXLOG 20
#define MAXM 50000
#define OFFLINE_JUDGE
const int inf=0x7f7f7f7f;
template <typename T>
inline const T Min(T a,T b){if(a<b) return a;return b;}

template <typename T>
inline void Swap(T &a,T &b){T t=a;a=b;b=t;}

template <typename Num>
inline void Read(Num &x){
    x=0;int p=1;char c=getchar();
    for(;!('0'<=c&&c<='9');c=getchar()) if(c=='-') p=-1;
    for(;'0'<=c&&c<='9';c=getchar()) x=x*10+c-'0';
    x*=p;
}

struct Seg{
    int u,v,w;
    Seg(){}
    Seg(int _u,int _v,int _w):u(_u),v(_v),w(_w){}
}A[MAXM+10];int nA;
inline bool cmp(Seg a,Seg b){return a.w>b.w;}
inline void AddSeg(int u,int v,int w){A[++nA]=Seg(u,v,w);}

struct Edge{
    int v,w,nxt;
    Edge(){}
    Edge(int _v,int _w,int _nxt):v(_v),w(_w),nxt(_nxt){}
}E[MAXM<<1|1];int nE,head[MAXM<<1|1];
inline void EdgeInit(void){nE=0;memset(head,-1,sizeof(head));}
inline void Link(int u,int v,int w){E[nE]=Edge(v,w,head[u]);head[u]=nE++;E[nE]=Edge(u,w,head[v]);head[v]=nE++;}

int n,m,Q;

int st[MAXN+10][MAXLOG],logTwo[MAXN+10];
inline void BuildST(int val[],int _size){
    logTwo[0]=-1;for(int i=1;i<=_size;i++) logTwo[i]=logTwo[i>>1]+1;
    int logSize=logTwo[n];
    for(int i=1;i<=_size;i++) st[i][0]=val[i];
    for(int j=1;j<=logSize;j++)
        for(int i=1;i+(1<<j)-1<=_size;i++)
            st[i][j]=Min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
}
inline int GetRMQ(int l,int r){
    if(l>r) return inf;
    int logLen=logTwo[r-l+1];
    return Min(st[l][logLen],st[r-(1<<logLen)+1][logLen]);
}

int dfsClock,fa[MAXN+10],L[MAXN+10],dep[MAXN+10],size[MAXN+10],son[MAXN+10],chainTop[MAXN+10],cost[MAXN+10];
inline void FindSon(int u,int _fa){
	size[u]=1;fa[u]=_fa;
    for(int i=head[u],v=E[i].v;i!=-1;i=E[i].nxt,v=E[i].v)if(v!=_fa){
        dep[v]=dep[u]+1;cost[v]=E[i].w;
        FindSon(v,u);
        size[u]+=size[v];
        if(size[v]>size[son[u]]) son[u]=v;
    }
}
inline void BuildChain(int u,int tp){
	L[u]=++dfsClock;
    chainTop[u]=tp;
    if(son[u]) BuildChain(son[u],tp);
    for(int i=head[u],v=E[i].v;i!=-1;i=E[i].nxt,v=E[i].v) if(fa[u]!=v&&v!=son[u]) BuildChain(v,v);
}
inline int Calc(int u,int v){
    int ret=inf;
    while(chainTop[u]!=chainTop[v]){
        if(dep[chainTop[u]]<dep[chainTop[v]]) Swap(u,v);
        ret=Min(ret,GetRMQ(L[chainTop[u]],L[u]));
        u=fa[chainTop[u]];
    }
    if(dep[u]<dep[v]) Swap(u,v);
    ret=Min(ret,GetRMQ(L[v]+1,L[u]));
    return ret;
}

int pre[MAXN+10];
inline int Find(int x){
    int t,r;
    for(r=x;r!=pre[r];r=pre[r]);
    for(t=pre[x];x!=pre[x];t=pre[x]) pre[x]=r,x=t;
    return r;
}
inline void Join(int a,int b){
    pre[Find(a)]=Find(b);
}

int rev[MAXN+10];
inline void Init(){
    EdgeInit();
    for(int i=1;i<=n;i++) pre[i]=i;
    std::sort(A+1,A+nA+1,cmp);
    //for(int i=1;i<=nA;i++) printf("%d ",A[i].w);puts("");
    for(int i=1,cnt=0;i<=nA&&cnt<n-1;i++)
        if(Find(A[i].u)!=Find(A[i].v)) {
            //printf("%d %d %d\n",i,A[i].u,A[i].v);
			Join(A[i].u,A[i].v);
            Link(A[i].u,A[i].v,A[i].w);
            cnt++;
        }
    for(int i=1;i<=n;i++) if(!fa[i]) {cost[i]=inf;FindSon(i,i);BuildChain(i,i);}
    for(int i=1;i<=n;i++) rev[L[i]]=cost[i];
    BuildST(rev,n);
}
int main(){
#ifdef OFFLINE_JUDGE
	freopen("truck.in","r",stdin);
	freopen("truck.out","w",stdout);
#endif
    scanf("%d%d",&n,&m);
    for(int i=1,x,y,z;i<=m;i++){
        scanf("%d%d%d",&x,&y,&z);
        AddSeg(x,y,z);
    }
    Init();
    scanf("%d",&Q);
    int x,y,lca;
    while(Q--){
        scanf("%d%d",&x,&y);
        if(Find(x)!=Find(y)) puts("-1");
        else printf("%d\n",Calc(x,y));
    }
    return 0;
}
```