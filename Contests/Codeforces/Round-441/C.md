## C. National Property 

time limit per test1 second memory limit per test 512 megabytes

You all know that the Library of Bookland is the largest library in the world. There are dozens of thousands of books in the library.

Some long and uninteresting story was removed...

The alphabet of Bookland is so large that its letters are denoted by positive integers. Each letter can be small or large, the large version of a letterxis denoted byx'. BSCII encoding, which is used everywhere in Bookland, is made in that way so that large letters are presented in the order of the numbers they are denoted by, and small letters are presented in the order of the numbers they are denoted by, but all large letters arebeforeall small letters. For example, the following conditions hold:2 &lt; 3,2' &lt; 3',3' &lt; 2.

A wordx1, x2, ..., xais notlexicographicallygreater thany1, y2, ..., ybif one of the two following conditions holds:

* a≤b and x1= y1, ..., xa= ya, i.e. the first word is the prefix of the second word;

* there is a position  
  1 ≤ j ≤ min\(a, b\), such thatx1 = y1, ..., xj-1 = yj- 1andxj&lt;yj, i.e. at the first position where the words differ the first word has a smaller letter than the second word has.

For example, the word "3'75" is before the word "24'6" in lexicographical order. It is said that sequence of words is in lexicographical order if each word is not lexicographically greater than the next word in the sequence.

Denis has a sequence of words consisting of small letters only. He wants to change some letters to large \(let's call this process acapitalization\) in such a way that the sequence of words is in lexicographical order. However, he soon realized that for some reason he can't change a single letter in a single word. He only can choose a letter and change all of its occurrences inallwords to large letters. He can perform this operation any number of times with arbitrary letters of Bookland's alphabet.

Help Denis to choose which letters he needs to capitalize \(make large\) in order to make the sequence of words lexicographically ordered, or determine that it is impossible.

Note that some words can beequal.

## Input

The first line contains two integersnandm\(2 ≤ n ≤ 100 000,1 ≤ m ≤ 100 000\) — the number of words and the number of letters in Bookland's alphabet, respectively. The letters of Bookland's alphabet are denoted by integers from1tom.

Each of the nextnlines contains a description of one word in formatli, si, 1, si, 2, ..., si, li\(1 ≤ li ≤ 100 000,1 ≤ si, j ≤ m\), whereliis the length of the word, andsi, jis the sequence of letters in the word. The words are given in the order Denis has them in the sequence.

It is guaranteed that the total length of all words is not greater than100 000.

## Output

In the first line print "Yes" \(without quotes\), if it is possible to capitalize some set of letters in such a way that the sequence of words becomes lexicographically ordered. Otherwise, print "No" \(without quotes\).

If the required is possible, in the second line printk — the number of letters Denis has to capitalize \(make large\), and in the third line printkdistinct integers — these letters. Note that youdon't need to minimizethe valuek.

You can print the letters in any order. If there are multiple answers, print any of them.

## Examples

### input

```
4 3


1 2


1 1


3 1 3 2


2 1 1
```

### output

```
Yes


2


2 3
```

### input

```
6 5


2 1 2


2 1 2


3 1 2 3


2 1 5


2 4 4


2 4 4
```

### output

```
Yes


0
```

### input

```
4 3


4 3 2 2 1


3 1 1 3


3 2 3 3


2 3 1
```

### output

```
No
```

## Note

In the first example after Denis makes letters2and3large, the sequence looks like the following:

* 2'
* 1
* 1 3' 2'
* 1 1

The condition2' &lt; 1holds, so the first word is not lexicographically larger than the second word. The second word is the prefix of the third word, so the are in lexicographical order. As the first letters of the third and the fourth words are the same, and3' &lt; 1, then the third word is not lexicographically larger than the fourth word.

In the second example the words are in lexicographical order from the beginning, so Denis can do nothing.

In the third example there is no set of letters such that if Denis capitalizes them, the sequence becomes lexicographically ordered.

## Solve

题目大意：按顺序给定一些数字构成的“字符串” 要使其符合字典序 可以把某种数全部变为大写

对于每个数只有两种操作变大写或不变，数之间有一些约束关系，然后就可以想到2-Sat了,但因为了边不是双向的，而是给定的，所以稍有变化，但还是2-sat的思想。

我们给每个字母一个状态$$isCapital[i]=0$$表示未确定,$$isCaptail[i]=1$$表示必须大写，$$isCaptail[i]=-1$$表示必须小写。

显然如果前后两个单词的某一对字符不同且前一个字符大于后一个字符，前一个字符必须大写，后一个字符必须小写

如果前一个字符小于后一个字符，情况不确定，因为可能后一个字符需要大写，那么前一个字符就要大写了，所以我们先连一条回边来“悔棋”，等所有情况确定后dfs确定

如果一个单词是恰好等于上一个单词的前缀，那么显然怎么搞都不行，所以直接<code>puts("NO");</code>
```cpp
#include<cstdio>
#include<cstring>
#define MAXN 100000
#define MAXM 100000
template <typename T>
inline void Swap(T &a,T &b){
	T t=a;a=b;b=t;
}
int n,m;
struct Edge{
	int v,nxt;
	Edge(){}
	Edge(int _v,int _nxt):v(_v),nxt(_nxt){};
}E[MAXN+10];int nE,head[MAXN+10];
inline void EdgeInit(){
	nE=0;memset(head,-1,sizeof(head));
}
inline void AddEdge(int u,int v){
	E[nE]=Edge(v,head[u]);head[u]=nE++;
}
int isCapital[MAXM+1],cnt;
bool ok;
int s[2][MAXM+1];
void dfs(int u){
	if(isCapital[u]==-1){
		ok=false; return ;
	}
	isCapital[u]=1;
	for(int i=head[u],v=E[i].v;i!=-1;i=E[i].nxt,v=E[i].v) dfs(v);
}
int main(){
	scanf("%d%d",&n,&m);
	int now=0,last=1;bool flag=false;
	EdgeInit();
	scanf("%d",&s[now][0]);for(int i=1;i<=s[now][0];i++) scanf("%d",&s[now][i]);Swap(now,last);
	for(int i=2,p;i<=n;i++){
		scanf("%d",&s[now][0]);for(int i=1;i<=s[now][0];i++) scanf("%d",&s[now][i]);
		flag=false;
		for(p=1;p<=s[now][0]&&p<=s[last][0];p++) if(s[last][p]!=s[now][p]){
			if(s[last][p]<s[now][p]){
				AddEdge(s[now][p],s[last][p]);//回边
			}else {
				if(isCapital[s[now][p]]!=1&&isCapital[s[last][p]]!=-1) isCapital[s[last][p]]=1,isCapital[s[now][p]]=-1;
				else {puts("No");return 0;}
			}
			flag=true;break;
		}
		if(!flag&&s[last][0]>s[now][0]) {puts("No");return 0;} 
		Swap(now,last);
	}
	ok=true;
	for(int i=1;i<=m;i++) if(isCapital[i]==1) dfs(i); 
	if(ok){
		puts("Yes");
		for(int i=1;i<=m;i++) if(isCapital[i]==1) cnt++;
		printf("%d\n",cnt);
		for(int i=1;i<=m;i++) if(isCapital[i]==1) printf("%d ",i);
	}else {puts("No");return 0;} 
	return 0;
}
```



