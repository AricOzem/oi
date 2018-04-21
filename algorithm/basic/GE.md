# 高斯消元
## 引入
 为了快速解除多元方程组，我们需要使用高斯消元。
## 解决
 对于n个方程，m个未知数的方程组，消元的具体步骤如下：
1. 枚举第i (0 &lt;= i &lt; n) 行，初始化列为col = 0，每次从[i, n)行中找到第col列中元素绝对值最大的行和第i行进行交换(找到最大的行是为了在消元的时候把浮点数的误差降到最小)；
 * 如果第col列的元素全为0，放弃这一列的处理，col+1，i不变，转1)；
 * 否则，对于所有的行j (i &lt; j &lt; n)，如果a[j][col]不为0，则需要进行消元，以期第i行以下的第col列的所有元素都消为0（这一步就是线性代数中所说的初等行变换，具体的步骤就是将第j行的所有元素减去第i行的所有元素乘上一个系数，这个系数即a[j][col] / a[i][col]）。

2. 重复步骤(1) 直到n个方程枚举完毕或者列col == m。

3. 判断解的情况：
 * 如果出现某一行，系数矩阵全为0，增广矩阵不全为0，则无解（即出现[0 0 0 0 0 b]，其中b不等于0的情况）；
 * 如果是严格上三角，则表明有唯一解；
 * 如果增广矩阵有k (k > 0)行全为0，那么表明有k个变量可以任意取值，这几个变量即自由变量；对于这种情况，一般解的范围是给定的，令解的取值有T个，自由变量有V个，那么解的个数就是 $$T^V$$。

** 示例 **
$$\begin{cases} 2x+3y+11z+5w=2 \\ x+y+5z+2w=1\\2x+y+3z+2w=-3 \\x+y+3z+3w=-3  \end{cases}$$

化为矩阵

$$\begin{bmatrix} 2 & 3 & 11 & 5 & 2 \\1 & 1 & 5 & 2 & 1 \\2 & 1 & 3 & 2 & -3\\1 & 1 & 3 & 4 & -3\end{bmatrix}\quad$$ 

将第一行第一列系数化为1

$$\begin{bmatrix} 1 & \frac{3}{2} & \frac{11}{2} & \frac{5}{2} & 1 \\1 & 1 & 5 & 2 & 1 \\2 & 1 & 3 & 2 & -3\\1 & 1 & 3 & 4 & -3\end{bmatrix}\quad$$ 

把下面各行第一列系数消为0，即减去第一行的相应倍数

$$\begin{bmatrix} 1 & \frac{3}{2} & \frac{11}{2} & \frac{5}{2} & 1 \\0 & -\frac{1}{2} & -\frac{1}{2} & -\frac{1}{2} & 0 \\0 & -2 & -8 & -3 & -5\\0 & -\frac{1}{2} & -\frac{5}{2} & \frac{3}{2} & -4 \end{bmatrix}\quad$$

将第二行第二列系数化为1

$$\begin{bmatrix} 1 & \frac{3}{2} & \frac{11}{2} & \frac{5}{2} & 1 \\0 & 1 & 1 & 1 & 0 \\0 & -2 & -8 & -3 & -5\\0 & -\frac{1}{2} & -\frac{5}{2} & \frac{3}{2} & -4 \end{bmatrix}\quad$$

把下面各行第二列系数消为0，即减去第二行的相应倍数

$$\begin{bmatrix} 1 & \frac{3}{2} & \frac{11}{2} & \frac{5}{2} & 1 \\0 & 1 & 1 & 1 & 0 \\0 & 0 & -6 & -1 & -5\\0 & 0 & -2 & 2 & -4\end{bmatrix}\quad$$

同理我们最终得到如下矩阵

$$\begin{bmatrix} 1 & \frac{3}{2} & \frac{11}{2} & \frac{5}{2} & 1 \\0 & 1 & 1 & 1 & 0 \\0 & 0 & 1 & \frac{1}{6} & \frac{5}{6}\\0 & 0 & 0 & 1 & -1\end{bmatrix}\quad$$

然后进行回代，就是把第四行的相应倍数加到第一、第二、第三行上；把第三行的相应倍数加到第一、第二行上

最终得到解

$$\begin{bmatrix} 1 & 0 & 0 & 0 & -2 \\0 & 1 & 0 & 0 & 0 \\0 & 0 & 1 & 0 & 1\\0 & 0 & 0 & 1 & -1\end{bmatrix}\quad$$

## 模板
```cpp
#include<cstdio>
#include<cmath>
double x[101][101];
const double eps=1e-6;
int n;
template <typename T>
inline void Swap(T &a,T &b){
	T t=a;a=b;b=t;
}
inline bool Gauss(){
	for(int i=1,t;i<=n;i++){
		t=i;
		for(int j=i+1;j<=n;j++) if(fabs(x[j][i])>fabs(x[t][i])) t=j;//找出绝对值较大的行交换也是为了保证精度 
		if(t!=i) for(int j=i;j<=n+1;j++)  Swap(x[i][j],x[t][j]);
		for(int j=i+1;j<=n;j++){//实际上首项不一定化为1，保证精度 
			double r=x[j][i]/x[i][i];
			for(int k=i;k<=n+1;k++) x[j][k]-=x[i][k]*r;
		}
		if(fabs(x[i][i])<eps) return false;
	}
	//回代
	for(int i=n;i>=1;i--){ 
		for(int j=i+1;j<=n;j++)//实际上并不需要把前面的系数化为0，只要修改n+1的值可以了
			 x[i][n+1]-=x[j][n+1]*x[i][j];
		x[i][n+1]/=x[i][i];
	} 
	return true;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n+1;j++)
			scanf("%lf",&x[i][j]);
	if(Gauss())
		for(int i=1;i<=n;i++)
			printf("%.2lf\n",x[i][n+1]);
	else puts("No Solution");
	return 0;
}
```
## 应用 
[BZOJ 1013](http://www.lydsy.com/JudgeOnline/problem.php?id=1013) [题解](/BZOJ/p1013.md)