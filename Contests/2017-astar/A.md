# A Arithmetic of Bomb
## Description
众所周知，度度熊非常喜欢数字。 

它最近在学习小学算术，第一次发现这个世界上居然存在两位数，三位数……甚至N位数！ 

但是这回的算术题可并不简单，由于含有表示bomb的#号，度度熊称之为 Arithmetic of Bomb。

![](/assets/C777-1001-1.jpg)

Bomb Number中的bomb，也就是#号，会展开一些数字，这会导致最终展开的数字超出了度度熊所能理解的范畴。比如”(1)#(3)”表示”1”出现了3次，将会被展开为”111”， 

同理，”(12)#(2)4(2)#(3)”将会被展开为”12124222”。 

为了方便理解，下面给出了Bomb Number的BNF表示。 

``` 
<bomb number> := <bomb term> | <bomb number> <bomb term> 
<bomb term> := <number> | '(' <number> ')' '#' '(' <non-zero-digit> ')' 
<number> := <digit> | <digit> <number> 
<digit> := '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' 
<non-zero-digit> := '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' 
``` 

请将Bomb Number中所有的#号展开，由于数字可能很长，结果对 1 000 000 007 取模。
## Input
第一行为T，表示输入数据组数。 

每组数据包含一个Bomb Expression。 


- 1≤T≤100 

- 1≤length(Bomb Number)≤1000

## Output
对每组数据输出表达式的结果，结果对 1 000 000 007 取模。
## Sample Input
```
4
1
(1)#(3)
(12)#(2)4(2)#(3)
(12)#(5)
```
## Sample Output
```
1
111
12124222
212121205
```
## Solve
简单模拟

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<cstring>
#include<iomanip>
#include<algorithm>
#define MAXN 9999
#define MAXSIZE 10
#define DLEN 4
#define MAXM 50000
#define K 1000000007
using namespace std;
typedef long long ll;
class BigNum
{
    private:
        int a[5000];
        int len; 
    public:
        BigNum()
        {
            len = 1;
            memset(a,0,sizeof(a));
        }
        BigNum(const int);
        BigNum(const char*);
        BigNum(const BigNum &);
        ll  operator%(const int  &) const;
        void print();
};
BigNum::BigNum(const int b)
{
    int c,d = b;
    len = 0;
    memset(a,0,sizeof(a));
    while(d > MAXN)
    {
        c = d - (d / (MAXN + 1)) * (MAXN + 1);
        d = d / (MAXN + 1);
        a[len++] = c;
    }
    a[len++] = d;
}
BigNum::BigNum(const char*s)
{
    int t,k,index,l,i;
    memset(a,0,sizeof(a));
    l=strlen(s);
    len=l/DLEN;
    if(l%DLEN)
        len++;
    index=0;
    for(i=l-1; i>=0; i-=DLEN)
    {
        t=0;
        k=i-DLEN+1;
        if(k<0)
            k=0;
        for(int j=k; j<=i; j++)
            t=t*10+s[j]-'0';
        a[index++]=t;
    }
}
BigNum::BigNum(const BigNum & T) : len(T.len)
{
    int i;
    memset(a,0,sizeof(a));
    for(i = 0 ; i < len ; i++)
        a[i] = T.a[i];
}

ll BigNum::operator %(const int & b) const  
{
    ll i,d=0;
    for (i = len-1; i>=0; i--)
    {
        d = ((d * (MAXN+1))% b + a[i])% b;
    }
    return d;
}

void BigNum::print()    //输出大数
{
    int i;
    cout << a[len - 1];
    for(i = len - 2 ; i >= 0 ; i--)
    {
        cout.width(DLEN);
        cout.fill('0');
        cout << a[i];
    }
    cout << endl;
}
char str[MAXM+10];
char temp[MAXM<<2|1];
int len;
inline void Work(){
    int times=0;
    char rem[MAXN+10];
    int tail=-1;
    int type=0;
    for(int i=0;i<len;i++){
        switch(str[i]){
            case '(':
                tail=0;
                if(!type) memset(rem,0,sizeof(rem));
                break;
            case ')':
                tail=-1;
                if(type){
                    for(int i=1;i<=times;i++)
                        strcat(temp,rem);
                    type=0;
                }
                break;
            case '#':
                times=0;
                type=1;
                break;
            default:
                if(tail<0){
                    temp[strlen(temp)]=str[i];
                    break;
                }
                if(!type)
                    rem[tail++]=str[i];
                else times=times*10+str[i]-'0';
                break;
        }
    }
}
int main(){
    int T;
    scanf("%d\n",&T);
    while(T--){
        gets(str);
        len=strlen(str);
        Work();
        BigNum ans=BigNum(temp);
        printf("%lld\n",ans%K);
        memset(temp,0,sizeof(temp));
    }
    return 0;
}
```