# Tarjan

## 引入

如何高效求图的环，强连通分量，进行缩地啊，以及求割点和桥

## 方法

求强连通分量\(SSC\),缩点,求割顶和桥
无向图
```cpp
namespace Tarjan {
	int DFN[MAXN+10],LOW[MAXN+10],dfsClock;
	int scc[MAXN+10],sccCnt,sccSize[MAXN+10];
	int inDeg[MAXN+10],outDeg[MAXN+10];
	bool isCut[MAXN+10],isBrige[MAXE+10];
	int cutCnt,brigeCnt;
	int stack[MAXS],top;
	void CutAndBrigedfs(int u,int _fa) {
		DFN[u]=LOW[u]=++dfsClock;
		int child=0;
		for(int i=head[u],v=E[i].v;i!=-1;i=E[i].nxt,v=E[i].v)if(v!=_fa){
			if(!DFN[v]){
				child++;
				Cutdfs(v,u);
				if(LOW[v]<LOW[u]) LOW[u]=LOW[v];
				if(LOW[v]>=DFN[u]) isCut[u]=true,isBrige[i]=true;
			}else if(DFN[v]<DFN[u]){
				if(DFN[v]<LOW[u]) LOW[u]=DFN[v];
			}
		}
		if(_fa<0&&child==1) isCut[u]=false;
	}
	void Sccdfs(int u) {
		DFN[u]=LOW[u]=++dfsClock;
		stack[++top]=u;
		for(int i=head[u],v=E[i].v; i!=-1; i=E[i].nxt,v=E[i].v)
			if(!DFN[v]) {
				fa[v]=u;
				Sccdfs(v);
				if(LOW[u]>LOW[v]) LOW[u]=LOW[v];
			} else if(fa[u]!=v&&!scc[v]) {
				if(LOW[u]>DFN[v]) LOW[u]=DFN[v];
			}
		if(DFN[u]==LOW[u]) {
			sccCnt++;
			while(stack[top]!=u) scc[stack[top--]]=sccCnt,sccSize[sccCnt]++;
			scc[stack[top--]]=sccCnt,sccSize[sccCnt]++;
		}
	}
	inline void GetSCC() {
		dfsClock=sccCnt=0;
		memset(scc,0,sizeof(scc));
		memset(DFN,0,sizeof(DFN));
		memset(sccSize,0,sizeof(sccSize));
		for(int i=1; i<=n; i++) if(!DFN[i]) Sccdfs(i);
	}
	inline void DegCalc() {
		memset(inDeg,0,sizeof(inDeg));
		memset(outDeg,0,sizeof(outDeg));
		for(int u=1; u<=n; u++)
			for(int i=head[u],v=E[i].v; i!=-1; i=E[i].nxt)
				if(scc[u]!=scc[v]) outDeg[scc[u]]++,inDeg[scc[v]]++;
	}

	inline void GetCut(int root) {
		memset(DFN,0,sizeof(DFN));
		memset(isCut,false,sizeof(isCut));
		dfsClock=0;
		cutCnt=brigeCnt=0;
		CutAndBrigedfs(root,-1);
		for(int i=1; i<=n; i++)
			if(isCut[i]) cutCnt++;
	}
}
```

## 应用



