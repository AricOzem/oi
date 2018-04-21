# 读入优化
```cpp
inline char nc(){
  static char buf[100000],*p1=buf,*p2=buf;
  return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
template <typename T>
inline void Read(T &a){
	a=0;
    char c;int p=1;
    for(c=nc();!(c>='0'&&c<='9');c=nc()) if(c=='-') p=-1;
    for(a=0;c>='0'&&c<='9';a=a*10+c-'0',c=nc()); 
    a*=p;
}
```