# A. Short Program (Div 1)

time limit per test

2 seconds

memory limit per test

256 megabytes

input

standard input

output

standard output

Petya learned a new programming language CALPAS. A program in this language always takes one non-negative integer and returns one non-negative integer as well.

In the language, there are only three commands: apply a bitwise operation AND, OR or XOR with a given constant to the current integer. A program can contain an arbitrary sequence of these operations with arbitrary constants from0to1023. When the program is run, all operations are applied \(in the given order\) to the argument and in the end the result integer is returned.

Petya wrote a program in this language, but it turned out to be too long. Write a program in CALPAS that does the same thing as the Petya's program, and consists of no more than5lines. Your program should return the same integer as Petya's program for all arguments from0to1023.

## Input

The first line contains an integern\(1 ≤ n ≤ 5·105\) — the number of lines.

Nextnlines contain commands. A command consists of a character that represents the operation \("&", "\|" or "^" for AND, OR or XOR respectively\), and the constantxi0 ≤ xi ≤ 1023.

## Output

Output an integerk\(0 ≤ k ≤ 5\) — the length of your program.

Nextklines must contain commands in the same format as in the input.

## Examples

### input

```
3
| 3
^ 2
| 1


```

### output

```
2
| 3
^ 2
```

### input

```
3
& 1
& 3
& 5
```

### output

```
1
& 1
```

### input

```
3
^ 1
^ 2
^ 3
```

### output

```
0
```

## Note

You can read about bitwise operations in [https://en.wikipedia.org/wiki/Bitwise\_operation](https://en.wikipedia.org/wiki/Bitwise_operation).

Second sample:

Letxbe an input of the Petya's program. It's output is\(\(x&1\)&3\)&5 = x&\(1&3&5\) = x&1. So these two programs always give the same outputs.

## Solve

题目大意：给你一些位运算操作，将他们化简成5个以内的对于0~1023等价的位运算操作

题目给出限制条件0~1023 即固定数位 每个位是独立的，我们只要判断某一位0和1输入后变成的情况然后就可以知道如何操作了  
具体可以参考代码

```cpp
#include<cstdio>
#include<cstring>
int n;
int bit[2];
int main(){
	scanf("%d\n",&n);
	bit[0]=0;bit[1]=1023;
	char c;
	for(int i=1,x;i<=n;i++){
		c=getchar();
		while(c==' '||c=='\n') 
			c=getchar();
		scanf("%d",&x);
		if(c=='|') {
			bit[0]|=x;
			bit[1]|=x;
		}else if(c=='&'){
			bit[0]&=x;
			bit[1]&=x;
		}else if(c=='^'){
			bit[0]^=x;
			bit[1]^=x;
		}
	}
	puts("3");
	printf("& %d\n",bit[0]|bit[1]);
	printf("^ %d\n",bit[0]&(1023^bit[1]));
	printf("| %d\n",bit[0]&bit[1]);
	return 0;
}
```

解释： 

&1 对原位不改变 如果0-&gt;0且1-&gt;0 显然这位是与上了一个0

^1023相当于每位取反,0-&gt;1且1-&gt;0 这位要异或上一个1

对于某一位0-&gt;1且1-&gt;1显然要这位或上一个1

