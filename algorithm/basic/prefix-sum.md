# 前缀和

## 引入

$$O(1)$$ 统计区间和

## 解决

### 一维前缀和

没什么好讲的
### 二维前缀和
一张经典图
![](/assets/pre-fix-num.png)
```cpp
int sum[MAXN+10][MAXN+10]
inline void SumInit() {
	for(int i=1; i<=n; i++)//Horizontal
		for(int j=1; j<=m; j++) {
			sum[i][j]=sum[i][j-1]+g[i][j];;
		}
	for(int j=1; j<=m; j++)//Vertical
		for(int i=1; i<=n; i++){
			sumPoint[i][j]+=sumPoint[i-1][j];
		}
}
inline int Query2D(int x1,int y1,int x2,int y2,int table[][MAXN+10]) {
	return table[x2][y2]-table[x2][y1-1]-table[x1-1][y2]+table[x1-1][y1-1];
}
```
水平方向加完，竖直方向的和就已经包含水平方向了，因为右下角只加了一次，所以并不用减去
## 应用

