# C - Nuske vs Phantom Thnook
Time limit : 4sec / Memory limit : 256MB

Score : 700 points

## Problem Statement

Nuske has a grid with N rows and M columns of squares. The rows are numbered 1 through N from top to bottom, and the columns are numbered 1 through M from left to right. Each square in the grid is painted in either blue or white. If Si,j is 1, the square at the i-th row and j-th column is blue; if Si,j is 0, the square is white. For every pair of two blue square a and b, there is at most one path that starts from a, repeatedly proceeds to an adjacent (side by side) blue square and finally reaches b, without traversing the same square more than once.

Phantom Thnook, Nuske's eternal rival, gives Q queries to Nuske. The i-th query consists of four integers xi,1, yi,1, xi,2 and yi,2 and asks him the following: when the rectangular region of the grid bounded by (and including) the xi,1-th row, xi,2-th row, yi,1-th column and yi,2-th column is cut out, how many connected components consisting of blue squares there are in the region?

Process all the queries.

## Constraints
1≤N,M≤2000
1≤Q≤200000
Si,j is either 0 or 1.
Si,j satisfies the condition explained in the statement.
1≤xi,1≤xi,2≤N(1≤i≤Q)
1≤yi,1≤yi,2≤M(1≤i≤Q)
## Input
The input is given from Standard Input in the following format:
```
N M Q
S1,1..S1,M
:
SN,1..SN,M
x1,1 yi,1 xi,2 yi,2
:
xQ,1 yQ,1 xQ,2 yQ,2
```
## Output
For each query, print the number of the connected components consisting of blue squares in the region.

### Sample Input 1
```
3 4 4
1101
0110
1101
1 1 3 4
1 1 3 1
2 2 3 4
1 2 2 4
```
### Sample Output 1
```
3
2
2
2
```

In the first query, the whole grid is specified. There are three components consisting of blue squares, and thus 3 should be printed.

In the second query, the region within the red frame is specified. There are two components consisting of blue squares, and thus 2 should be printed. Note that squares that belong to the same component in the original grid may belong to different components.

### Sample Input 2

```
5 5 6
11010
01110
10101
11101
01010
1 1 5 5
1 2 4 5
2 3 3 4
3 3 3 3
3 1 3 5
1 1 3 4
```
### Sample Output 2

```
3
2
1
1
3
2
```
## Solve

一开始想直接前缀和答案，显然是不行的，但是由于图中不存在环，显然每个子矩阵的联通块是一些链，然后就有联通块个数=点数-边数
然后把这两个前缀和一下就好了
细节：
因为要减去和外面相连的边
所以多加了两个一维前缀和维护行和列
```cpp
#include<cstdio>
#include<cstring>
#define MAXN 2000
int sumEdge[MAXN+10][MAXN+10],sumEdgeRow[MAXN+10][MAXN+10],sumEdgeCol[MAXN+10][MAXN+10];
int sumPoint[MAXN+10][MAXN+10];
bool g[MAXN+10][MAXN+10];
int n,m,Q;
inline void SumInit() {
	for(int i=1; i<=n; i++)//Horizontal
		for(int j=1; j<=m; j++) {
			sumPoint[i][j]=sumPoint[i][j-1]+g[i][j];
			sumEdge[i][j]=sumEdge[i][j-1];
			if(g[i][j]&&g[i][j-1]) sumEdge[i][j]++;
			sumEdgeCol[i][j]=sumEdge[i][j];
		}
	for(int j=1; j<=m; j++)//Vertical
		for(int i=1; i<=n; i++){
			sumPoint[i][j]+=sumPoint[i-1][j];
			sumEdgeRow[j][i]=sumEdgeRow[j][i-1];
			if(g[i][j]&&g[i-1][j]) sumEdgeRow[j][i]++;
		}
	for(int i=1,tmp; i<=n; i++){//Vertical
		tmp=0;
		for(int j=1; j<=m; j++){
			if(g[i][j]&&g[i-1][j]) tmp++;
			sumEdge[i][j]+=sumEdge[i-1][j]+tmp;
		}
	}
}
inline int Query1D(int l,int r,int table[]) {
	return table[r]-table[l-1];
}
inline int Query2D(int x1,int y1,int x2,int y2,int table[][MAXN+10]) {
	return table[x2][y2]-table[x2][y1-1]-table[x1-1][y2]+table[x1-1][y1-1];
}
int main() {
	scanf("%d%d%d\n",&n,&m,&Q);
	char c;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++) {
			c=getchar();
			if(c=='1') g[i][j]=true;else g[i][j]=false;
		}
		c=getchar();
	}
	SumInit();
	int x1,y1,x2,y2;
	while(Q--){
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		//printf("%d %d %d %d\n",Query2D(x1,y1,x2,y2,sumPoint),Query2D(x1+1,y1+1,x2,y2,sumEdge),Query1D(x1+1,x2,sumEdgeRow[y1]),Query1D(y1+1,y2,sumEdgeCol[x1]));
		printf("%d\n",Query2D(x1,y1,x2,y2,sumPoint)-Query2D(x1+1,y1+1,x2,y2,sumEdge)-Query1D(x1+1,x2,sumEdgeRow[y1])-Query1D(y1+1,y2,sumEdgeCol[x1]));
	}
	return 0;
}
```