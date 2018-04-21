# RMQ 求区间中最值
## 引入
  RMQ (Range Minimum/Maximum Query)问题是指：对于长度为n的数列A，回答若干询问RMQ(A,i,j)(i,j&lt;=n)，返回数列A中下标在i,j里的最小(大）值，也就是说，RMQ问题是指求区间最值的问题。
## 解决

### ST 算法  
核心思想：记忆递归搜索过程 l~r的区间最大值 为l~mid和mid+1~r区间最大值的最大值
#### 离线: $$Init:O(n\log n),Query:O(1)$$
模板：
```cpp
namespace ST{
	struct RMQ{
		int i,v;
		friend bool operator <(RMQ a,RMQ b){
			return a.v<b.v;
		}
		friend bool operator >(RMQ a,RMQ b){
			return a.v>b.v;
		}
		RMQ(int _i,int _v):i(_i),v(_v){}
		RMQ(){};
	}st[MAXN+10][MAXLOG+5];
	int log[MAXN+10];
	inline void MakeST(int *a,int len){
		log[0]=-1;for(int i=1;i<=len;i++) log[i]=log[i>>1]+1;
		for(int i=1;i<=len;i++) st[i][0]=RMQ(i,a[i]);
		for(int j=1;j<=MAXLOG;j++)
			for(int i=1;i+(1<<j)-1<=len;i++)
				st[i][j]=Max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	}
	inline bool getRMQ(int l,int r,RMQ &ret){
		if(l>r) return false;
		int logLen=log[r-l+1];
		ret=Max(st[l][logLen],st[r-(1<<logLen)+1][logLen]);
		return true;
	}
}
```
## 应用
[
NOI 2010 超级钢琴](http://www.lydsy.com/JudgeOnline/problem.php?id=2006) [题解
](/BZOJ/p2006.md)