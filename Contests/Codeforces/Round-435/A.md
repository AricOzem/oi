# C  Mahmoud and Ehab and the xor \(Div 1 \)

time limit per test

2 seconds

memory limit per test

256 megabytes

Mahmoud and Ehab are on the third stage of their adventures now. As you know, Dr. Evil likes sets. This time he won't show them any set from his large collection, but will ask them to create a new set to replenish his beautiful collection of sets.

Dr. Evil has his favorite evil integerx. He asks Mahmoud and Ehab to find a set ofndistinct non-negative integers such the bitwise-xor sum of the integers in it is exactlyx. Dr. Evil doesn't like big numbers, so any number in the set shouldn't be greater than106.

## Input

The only line contains two integersnandx\(1 ≤ n ≤ 105,0 ≤ x ≤ 105\) — the number of elements in the set and the desired bitwise-xor, respectively.

## Output

If there is no such set, print "NO" \(without quotes\).

Otherwise, on the first line print "YES" \(without quotes\) and on the second line printndistinct integers, denoting the elements in the set is any order. If there are multiple solutions you can print any of them.

## Examples

### input

```
5 5
```

### output

```
YES


1 2 4 5 7
```

### input

```
3 6
```

### output

```
YES


1 2 5
```

## Note

You can read more about the bitwise-xor operation here:[https://en.wikipedia.org/wiki/Bitwise\_operation\#XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)

For the first sample![](http://codeforces.com/predownloaded/07/44/0744694ffedad9a8e0a8341c7b2f8998a5541770.png).

For the second sample![](http://codeforces.com/predownloaded/5a/16/5a167323d6fb40ff326a173bbd0691180fecf396.png).

## Solve

题目大意：选n不同个数使他们的异或和为x 这n个数均不超过$$10^6$$

看了Tutorial才想到的神奇构造题

根据异或和自反性，不论y为什么总有

$$x=(x \oplus y) \oplus y$$

我们还可以把后面的y在根据自反性拆分  
$$x=(x \oplus y) \oplus ((y\oplus z)\oplus z)$$

然后就能组合一下得到4个数他们的异或和为$$x$$

然后我们呢之前的数都可以瞎枚举了

我们枚举$$1\ldots(n-3)$$ 计算他们的异或和，然后用一个较大的数$$pw$$对其进行操作满足条件

为什么手动操作的是后面的三个呢

考虑他们的异或和刚好为x，有

根据异或的结合律和交换律

$$x=y=y\oplus pw\oplus pw=y \oplus pw\oplus (pw\oplus pw2\oplus pw2)=tmp\oplus pw\oplus pw2\oplus (pw \oplus pw2)$$

其中$$pw2$$为另一个较大的数\(比$$pw$$大\)

可见我们至少需要三个手动位置才能构造解

如果不等于$$x$$其实我们只需要两个手动位置

$$x \oplus y \oplus y =x\oplus y\oplus (y\oplus pw\oplus pw)=y\oplus (y\oplus x \oplus pw)\oplus pw$$

但是为了适应上面的情况我们多了一个位置， 还是因为自反性 我们异或上一个0就行了

```cpp
#include<cstdio>
#include<cstring>
int n,x;
const int pw=1<<17;
const int pw2=1<<18;
int main(){
    scanf("%d%d",&n,&x);
    if(n==1) {printf("Yes\n%d",x);return 0;}
    if(n==2&&x==0) {puts("No");return 0;}
    puts("Yes");
    int tmp=0;
    for(int i=1;i<=n-3;i++) {
        printf("%d ",i);
        tmp^=i;
    }
    if(tmp==x) printf("%d %d %d",pw,pw2,pw^pw2);//x=tmp=tmp^pw^pw=tmp^pw^(pw^pw2^pw2)=tmp^pw^pw2^(pw^pw2)
    else printf("%d %d %d",pw,tmp^x^pw,0); //x=x^0=x^tmp^tmp=x^tmp^(tmp^pw^pw)^0=tmp^(x^tmp^pw)^pw^0
    return 0;
}
```



