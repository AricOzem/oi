# B. Sorting the Coins \(Div 1 \)

time limit per test 1 second

memory limit per test 512 megabytes

Recently, Dima met with Sasha in a philatelic store, and since then they are collecting coins together. Their favorite occupation is to sort collections of coins. Sasha likes having things in order, that is why he wants his coins to be arranged in a row in such a way that firstly come coins out of circulation, and then come coins still in circulation.

For arranging coins Dima uses the following algorithm. One step of his algorithm looks like the following:

1. He looks through all the coins from left to right;
2. If he sees that the
   i-th coin is still in circulation, and\(i+ 1\)-th coin is already out of circulation, he exchanges these two coins and continues watching coins from\(i + 1\)-th.

Dima repeats the procedure above until it happens that no two coins were exchanged during this procedure. Dima callshardness of orderingthe number of steps required for him according to the algorithm above to sort the sequence, e.g. the number of times he looks through the coins from the very beginning. For example, for the ordered sequence hardness of ordering equals one.

Today Sasha invited Dima and proposed him a game. First he putsncoins in a row, all of them are out of circulation. Then Sasha chooses one of the coins out of circulation and replaces it with a coin in circulation forntimes. During this process Sasha constantly asks Dima what is the hardness of ordering of the sequence.

The task is more complicated because Dima should not touch the coins and he should determine hardness of ordering in his mind. Help Dima with this task.

## Input

The first line contains single integern\(1 ≤ n ≤ 300 000\) — number of coins that Sasha puts behind Dima.

Second line containsndistinct integersp1, p2, ..., pn\(1 ≤ pi ≤ n\) — positions that Sasha puts coins in circulation to. At first Sasha replaces coin located at positionp1, then coin located at positionp2and so on. Coins are numbered from left to right.

## Output

Print n + 1 numbers a0, a1, ..., an, where a 0 is a hardness of ordering at the beginning, a 1 is a hardness of ordering after the first replacement and so on.

## Examples

### input

```
4

1 3 4 2
```

## output

```
1 2 3 2 1
```

### input

```
8


6 8 3 4 7 2 1 5
```

## output

```
1 2 2 3 4 3 4 5 1
```

## Solve

题目大意：给定一些A硬币在给定位置替换为B类型硬币，通过比较-交换使序列变为所有A在前B在后的有序序列

题中的每一次操作就是一次冒泡排序，冒泡排序每次使数列中所有的数的逆序数减少，所以需要操作的次数就是最大的逆序数，一开始以为是动态逆序和什么的高级操作，然而只有两种硬币，最大逆序数显然是最右侧的A硬币左侧B硬币的数量。这就很好维护了。

```cpp
#include<cstdio>
#include<cstring>
#define MAXN 400000
int n;
int coin[MAXN+10];
bool used[MAXN+10];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",coin+i);
    int r=n,ans=0;
    printf("1");
    for(int i=1;i<=n;i++){
        used[coin[i]]=true;ans++;
        while(used[r]) 
            r--,ans--;
        printf(" %d",ans+1);
    }
    return 0;
}
```



