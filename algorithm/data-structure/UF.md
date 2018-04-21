# 并查集

## 引入

## 解决
```cpp
int find(int x){
	int r,t;
	for(r=x;r!=pre[x];r=pre[r]);
	while(x!=pre[x]) t=pre[x],pre[x]=r,x=t;//路径压缩 
	return r;
}
inline void join(int a,int b){
	pre[find(a)]=find(b);
}
```
## 应用
动态给出两个节点，判断它们是否连通，如果连通，不需要给出具体的路径

动态给出两个节点，判断它们是否连通，如果连通，需要给出具体的路径
