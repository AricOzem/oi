# A. Ryouko's Memory Note  (Div 1)

time limit per test 1 second

memory limit per test 256 megabytes

input standard input

output standard output

Ryouko is an extremely forgetful girl, she could even forget something that has just happened. So in order to remember, she takes a notebook with her, calledRyouko's Memory Note. She writes what she sees and what she hears on the notebook, and the notebook became her memory.

Though Ryouko is forgetful, she is also born with superb analyzing abilities. However, analyzing depends greatly on gathered information, in other words, memory. So she has to shuffle through her notebook whenever she needs to analyze, which is tough work.

Ryouko's notebook consists ofnpages, numbered from 1 ton. To make life \(and this problem\) easier, we consider that to turn from pagexto pagey,\|x - y\|pages should be turned. During analyzing, Ryouko needsmpieces of information, thei-th piece of information is on pageai. Information must be read from the notebook in order, so the total number of pages that Ryouko needs to turn is![](http://espresso.codeforces.com/b19a52472036d57233f58883f6dcf82d27f98e8e.png).

Ryouko wants to decrease the number of pages that need to be turned. In order to achieve this, she can merge two pages of her notebook. If Ryouko merges pagexto pagey, she would copy all the information on pagextoy \(1 ≤ x, y ≤ n\), and consequently, all elements in sequenceathat wasxwould becomey. Note thatxcan be equal toy, in which case no changes take place.

Please tell Ryouko the minimum number of pages that she needs to turn. Note she can apply the described operation at most once before the reading. Note that the answer can exceed 32-bit integers.

## Input

The first line of input contains two integersnandm \(1 ≤ n, m ≤ 105\).

The next line containsmintegers separated by spaces:a1, a2, ..., am\(1 ≤ ai ≤ n\).

## Output

Print a single integer — the minimum number of pages Ryouko needs to turn.

## Examples

### input

```
4 6


1 2 3 4 3 2


```

### output

```
3


```

### input

```
10 5


9 4 3 8 8


```

### output

```
6


```

## Note

In the first sample, the optimal solution is to merge page 4 to 3, after merging sequenceabecomes{1, 2, 3, 3, 3, 2}, so the number of pages Ryouko needs to turn is\|1 - 2\| + \|2 - 3\| + \|3 - 3\| + \|3 - 3\| + \|3 - 2\| = 3.

In the second sample, optimal solution is achieved by merging page 9 to 4.

## Solve

变化量

$$\Delta=\sum{|y-b[i]|}-\sum{x-b[i]}$$

枚举 x 使$$\sum{|y-b[i]|}$$最小

看作数轴上的点到各点距离 y为其中位数时最小

```cpp
#include<cstdio>
#include<vector>
#include<algorithm> 
#define MAXN 100000
typedef long long ll;
template <typename T>
inline T Max(T a,T b){
	if(a>b) return a;
	return b;
}
int n,m;
std::vector<int> b[MAXN+10];
bool vis[MAXN+10];
int a[MAXN+10],maxp,cnt,maxn;
ll before,after,sum=0,delta=0;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d",&a[i]);
		if(i>1) sum+=abs(a[i]-a[i-1]); 
	}
	for(int i=1;i<=m;i++){
		if(i-1>=1&&a[i-1]!=a[i]) b[a[i]].push_back(a[i-1]);
		if(i+1<=m&&a[i+1]!=a[i]) b[a[i]].push_back(a[i+1]);
	}
	for(int i=1,midn;i<=n;i++)if(b[i].size()){
		std::sort(b[i].begin(),b[i].end());
		midn=b[i][b[i].size()>>1];
		before=after=0;
		for(int j=0;j<b[i].size();j++){
			before+=abs(i-b[i][j]);
			after+=abs(midn-b[i][j]);
		}
		delta = Max(delta, before - after);
	}
	printf("%I64d",sum-delta);
	return 0;
} 
```
