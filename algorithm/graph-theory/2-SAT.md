## 2-SAT

## 引入
现有一个由N个布尔值组成的序列A，给出一些限制关系，比如A[x] AND A[y]=0、A[x] OR A[y] OR A[z]=1等，要确定A[0..N-1]的值，使得其满足所有限制关系。这个称为SAT问题，特别的，若每种限制关系中最多只对两个元素进行限制，则称为2-SAT问题
## 解决
```cpp
namespace TwoSat{
	bool mark[MAXN+10];
	int stack[MAXS],top;
	bool dfs(int u){
		if(mark[u^1]) return false;
		if(mark[u]) return true;
		mark[u]=true;
		stack[++top]=u;
		for(int i=head[u],v=E[i].v;i!=-1;i=E[i].nxt,v=E[i].v)
			if(!dfs(v)) return false;
		return true;
	}
	bool Solve(){
		memset(mark,false,sizeof(mark));
		for(int i=0;i<n*2;i+=2)
			if(!mark[i]&&!mark[i+1]){
				top=0;
				if(!dfs(i)){
					while(top) mark[stack[top--]]=false;
					if(!dfs(i+1)) return false;
				}
			}
		return true;
	}
}
```
## 应用
[HDU 1814 Peaceful Commission](http://acm.split.hdu.edu.cn/showproblem.php?pid=1814)  [题解](HDU/p1814.md)