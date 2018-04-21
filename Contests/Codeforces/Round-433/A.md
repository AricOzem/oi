# A. Planning (Div 1)
time limit per test1 second
memory limit per test512 megabytes

inputstandard input
outputstandard output

Helen works in Metropolis airport. She is responsible for creating a departure schedule. There are n flights that must depart today, the i-th of them is planned to depart at the i-th minute of the day.

Metropolis airport is the main transport hub of Metropolia, so it is difficult to keep the schedule intact. This is exactly the case today: because of technical issues, no flights were able to depart during the first k minutes of the day, so now the new departure schedule must be created.

All n scheduled flights must now depart at different minutes between (k + 1)-th and (k + n)-th, inclusive. However, it's not mandatory for the flights to depart in the same order they were initially scheduled to do so — their order in the new schedule can be different. There is only one restriction: no flight is allowed to depart earlier than it was supposed to depart in the initial schedule.

Helen knows that each minute of delay of the i-th flight costs airport ci burles. Help her find the order for flights to depart in the new schedule that minimizes the total cost for the airport.

## Input
The first line contains two integers n and k (1 ≤ k ≤ n ≤ 300 000), here n is the number of flights, and k is the number of minutes in the beginning of the day that the flights did not depart.

The second line contains n integers c1, c2, ..., cn (1 ≤ ci ≤ 10^7), here ci is the cost of delaying the i-th flight for one minute.

## Output
The first line must contain the minimum possible total cost of delaying the flights.

The second line must contain n different integers t1, t2, ..., tn (k + 1 ≤ ti ≤ k + n), here ti is the minute when the i-th flight must depart. If there are several optimal schedules, print any of them.

## Example
### input
```
5 2
4 2 1 10 2
```
### output
```
20
3 6 7 4 5 
```
## Note
Let us consider sample test. If Helen just moves all flights 2 minutes later preserving the order, the total cost of delaying the flights would be (3 - 1)·4 + (4 - 2)·2 + (5 - 3)·1 + (6 - 4)·10 + (7 - 5)·2 = 38 burles.

However, the better schedule is shown in the sample answer, its cost is (3 - 1)·4 + (6 - 2)·2 + (7 - 3)·1 + (4 - 4)·10 + (5 - 5)·2 = 20 burles.
## Solve
显然$$sum=\sum\limits_{i=1}^{n}{(t_i-i)*c_i}=\sum\limits_{i=1}^{n}{t_i*c_i}-\sum\limits_{i=1}^{n}{-i*c_i}$$

我们要使$$\sum\limits_{i=1}^{n}{t_i*c_i}$$尽可能小同时满足第$$i$$架飞机不早于$$i$$时起飞，

耗费大的越早越好，最好准点，所以我们一边加入堆，一边取堆中最大元素在当时起飞就可以了
因为延迟的总时间是一定的，所以越小的承担越多肯定是最优的
```cpp
#include<cstdio>
#define MAXN 300000
typedef long long ll;
template <typename T>
struct Heap {
	T a[MAXN+10];
	int tail;
	void Swap(T &a,T &b) {
		T t=a;
		a=b;
		b=t;
	}
	void Push(const T x) {
		a[++tail]=x;
		int now=tail;
		while(now>1&&a[now]<a[now>>1]) Swap(a[now],a[now>>1]),now>>=1;
	}
	void Pop(void) {
		a[1]=a[tail--];
		int now=2;
		while(now<=tail) {
			if(a[now+1]<a[now]) now++;
			if(a[now]<a[now>>1]) Swap(a[now],a[now>>1]),now<<=1;
			else break;
		}
	}
	inline const T Top(void) {
		return a[1];
	}
	inline const bool Empty(void) {
		return tail==0;
	}
};
struct Flight {
	int id,c;
	Flight() {}
	Flight(int _id,int _c):id(_id),c(_c) {}
	friend bool operator <(Flight a,Flight b) {
		return a.c>b.c;
	}
} f[MAXN+10];
Heap<Flight> q;
int n,k,best[MAXN+10];
ll sum;
int main() {
	scanf("%d%d",&n,&k);
	register int i;
	int x;
	for(i=1,x; i<=n; i++) {
		scanf("%d",&x);
		f[i]=Flight(i,x);
	}
	for(i=1; i<=k; i++) q.Push(f[i]);
	Flight u;
	for(; i<=k+n; i++) {
		if(i<=n) q.Push(f[i]);
		u=q.Top();
		q.Pop();
		best[u.id]=i;
		sum+=1LL*(i-u.id)*u.c;
	}
	printf("%lld\n",sum);
	for(int i=1; i<=n; i++) printf("%d ",best[i]);
	return 0;
}
```
