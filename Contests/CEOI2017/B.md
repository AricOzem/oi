# B Sure Bet
Time Limit: 2 s Memory Limit: 128 MB

Luck is a fundamental part of betting. Some people improve their chances and earnings by having good knowledge of what they are betting on. We will take a different approach.

Various bookmakers offer different odds or quotas for the same outcome. (An odds of x means that if you bet 1 euro and predict the outcome correctly, you get x euros back.If you predict the outcome incorrectly, you of course get nothing back. Note that you pay 1 euro regardless of the outcome.) What if you could be certain of making a profit by cleverly placing several bets? You would want to make this guaranteed profit as large as possible.

The event we want to bet on has two possible outcomes. There are n bookmakers that offer different odds. Let us denote the odds offered by the i-th bookmaker for the first outcome with ai, and the odds offered for the second outcome with bi. You can place a bet on any subset of the offered odds. You can even bet on both outcomes at the same bookmaker. However, all bets have to be exactly 1 euro and you cannot bet on the same outcome with the same bookmaker multiple times.

In case of the first outcome, you will receive ai euros from every bookmaker i with whom you placed a bet on the first outcome. Similarly, in case of the second outcome,you will receive bi euros from all eligible bookmakers. Of course in both cases, you already paid 1 euro for every bet you placed.What is the largest guaranteed profit (i.e. regardless of the outcome) if you place your bets optimally?
## Input
The first line contains the number of bookmakers, n. The following n lines describe the
odds offered by each bookmaker with two space-separated real numbers ai and bi - the
odds for the first and second outcome offered by the i-th bookmaker. The odds will be
given to at most 4 decimal places.
## Constraints
```
• 1.0 ≤ ai, bi ≤ 1000.0
• 1 ≤ n ≤ 100 000
Subtask 1 (20 points)
• n ≤ 10
Subtask 2 (40 points)
• n ≤ 1 000
Subtask 3 (40 points)
• no additional constraints
```
## Output
Output the maximum guaranteed profit rounded to exactly 4 decimal places.
Here are the commands to print the floating point numbers in various languages:
* C and C++: printf("%.4lf",(double)x);
* Java: System.out.printf("%.4lf",x);
* Pascal: writeln(x:0:4);
* Python 3: print("%.4lf"%x)
* C#: Console.WriteLine(String.Format("0:0.0000",x));
## Example
### Input
```
4
1.4 3.7
1.2 2
1.6 1.4
1.9 1.5
```
### Output
```
0.5000
```
## Comment
The optimal betting strategy consists of betting on the second outcome with the first bookmaker and on the first outcome with the third and fourth bookmaker. In case of the first outcome, we will earn 1.6 + 1.9 − 3 = 0.5 and in case of the second outcome 3.7 − 3 = 0.7. So we’re guaranteed 0.5 euros regardless of the outcome.

## Solve
题目大意：给定两组不同情况下的收益，每次下注需要1成本，求不论是最终是情况1还是情况2所能得到的最大净收入
即让$$\min\{\sum{a_i}\ \ -n_a-n_b,\sum{b_i}\ \ -n_a-n_b \}$$ 即$$\min\{\sum{(a_i-1)}\ \, -n_b,\sum{(b_i-1)}\ \ -n_a \}$$最大  
可以发现这两个其实是独立的，只要枚举$$n_a$$和$$n_b$$就可以了（选择前$$n_a$$个最大的a[i]和$$n_b$$最大的b[i]）,但是$$O(n^2)$$显然不能过$$10^5$$
考虑给定$$n_a$$,随着$$n_b$$的增大，第一种情况获得的收益会逐渐减少，第二种情况的收益会逐渐增大，所以整个函数应该是个单峰的函数，三分搜索一下就好了，因此优化到$$O(n\log n)$$
```cpp
#include<cstdio>
#include<algorithm>
#define MAXN 100000
const double eps=1e-6;
template<typename T> T Max(T a,T b){if(a>b) return a;return b;}
template<typename T> T Min(T a,T b){if(a<b) return a;return b;}
double a[MAXN+10],b[MAXN+10];
int n;
inline bool cmp(double a,double b){return a>b;}
inline double Calc(int ua,int ub){
	return Min(a[ua]-ub,b[ub]-ua);
}
inline int Find(int ua){
	int l=0,r=n,mid,mmid;
	while(l<r-1){
		mid=(l+r)>>1;
		mmid=(mid+r)>>1;
		if(Calc(ua,mid)-Calc(ua,mmid)>eps) r=mmid;
		else l=mid;
	}
	if(Calc(ua,l)>Calc(ua,r)) return l;
	return r;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lf%lf",&a[i],&b[i]);
		a[i]-=1.0,b[i]-=1.0;
	}
	std::sort(a+1,a+1+n,cmp);
	for(int i=1;i<=n;i++) a[i]=a[i]+a[i-1];
	std::sort(b+1,b+1+n,cmp);
	for(int i=1;i<=n;i++) b[i]=b[i]+b[i-1];
	double ans=0;
	for(int ua=0,ub;ua<=n;ua++){
		ub=Find(ua);
		ans=Max(ans,Calc(ua,ub));
	}
	printf("%.4lf",ans);
	return 0;
}
```