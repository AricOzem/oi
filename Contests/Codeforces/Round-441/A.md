# A. Classroom Watch \(Div 1 \)

time limit per test 1 second memory limit per test 512 megabytes

Eighth-grader Vova is on duty today in the class. After classes, he went into the office to wash the board, and found on it the numbern. He asked what is this number and the teacher of mathematics Inna Petrovna answered Vova thatnis the answer to the arithmetic task for first-graders. In the textbook, a certainpositive integerxwas given. The task was to addxto the sum of the digits of the numberxwritten in decimal numeral system.

Since the numbernon the board was small, Vova quickly guessed whichxcould be in the textbook. Now he wants to get a program which will search for arbitrary values of the numbernfor all suitable values ofxor determine that suchxdoes not exist. Write such a program for Vova.

## Input

The first line contains integer n\(1 ≤ n ≤ 109\).

## Output

In the first line print one integer k — number of different values ofxsatisfying the condition.

In nextklines print these values in ascending order.

## Examples

### input

```
21
```

### output

```
1


15
```

### input

```
20
```

### output

```
0
```

### Note

In the first test casex = 15there is only one variant:15 + 1 + 5 = 21.

In the second test case there are no suchx.

## Solve

题目大意：求满足数位和+该数等于给定数的树

一开始想的是数位dp，后来发现枚举数位和（9\*9），剩下的数字是确定的，然后就变成枚举水题了

注意升序输出

```cpp
#include<cstdio>
int n;
int ans[120];
inline bool check(int val,int t){
    int ret=0;
    while(val>0){
        ret+=val%10;
        val/=10;
    }
    return ret==t;
}
int main(){
    scanf("%d",&n);
    int cnt=0;
    for(int i=81;i>=1;i--){
        if(i>n) continue;
        if(check(n-i,i)) ans[++cnt]=n-i;
    }
    printf("%d",cnt);
    if(cnt!=0) puts(""); 
    for(int i=1;i<=cnt;i++) printf("%d ",ans[i]);
    return 0;
}
```



