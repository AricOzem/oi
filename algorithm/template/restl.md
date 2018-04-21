# 手动重写的STL中原有的数据结构

>似乎会更快?

1. queue

```cpp
template <typename T>
struct Queue{
	T a[MAXQ],*l,*r;
	Queue():l(a),r(a-1){}
	void Push(const T x){*++r=x;}
	void Pop(void){++l;}
	const T Front(){return *l;}
	bool Empty(void){return r<l;}
};
```
2. Heap (priority_queue) 小根堆 重载"&lt;"运算符

```cpp
template <typename T>
struct Heap{
	T a[MAXH+10];int tail;
	Heap():tail(0){}
	void Insert(const T x){
		a[++tail]=x;
		int now=tail;
		while(a[now]<a[now>>1]&&now>1) Swap(a[now],a[now>>1]),now>>=1;
	}
	void Pop(void){
		if(tail==0) return ;
		a[1]=a[tail--];
		int now=2;
		while(now<=tail){
			if(a[now+1]<a[now]) now++;
			if(a[now]<a[now>>1]) Swap(a[now],a[now>>1]);else break;
			now<<=1;
		}
	}
	const T Top(void){return a[1];}
	bool Empty(void){return tail==0;}
};
```