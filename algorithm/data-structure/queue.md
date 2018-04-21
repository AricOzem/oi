```cpp
template <typename T>
struct Queue{
	T a[MAXQ],*l,*r;
	Queue():front(a),tail(a-1){}
	void push(const T &x){
		*++l=x;
	}
	void pop(){
		r++;
	}
	T &front(){
		return *l;
	} 
	const bool empty(){
		return l>r;
	}
};
```



