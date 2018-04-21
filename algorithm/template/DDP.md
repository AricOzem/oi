# 数位DP 模板

```cpp
/*    pos    = 当前处理的位置(一般从高位到低位)
      pre    = 上一个位的数字(更高的那一位)
      status = 要达到的状态,如果为1则可以认为找到了答案,到时候用来返回,
         　　  给计数器+1。 
		       下文以HDU P6148为例 要达到的状态为upTimes<=1 
      limit  = 是否受限,也即当前处理这位能否随便取值。如567,当前处理6这位,
         　　 如果前面取的是4,则当前这位可以取0-9。如果前面取的5,那么当前
         　　 这位就不能随便取，不然会超出这个数的范围,所以如果前面取5的
         　　 话此时的limit=1,也就是说当前只可以取0-6。
*/ 
int dfs(int pos,int pre,int upTimes,bool limit) {//记忆化搜素 pre=-1 说明存在前导零 
	if(pos==-1) {
		if(pre!=-1) return 1;//修正前导零 
		return 0;
	}
	if(!limit&&pre!=-1&&f[pos][pre][upTimes]!=-1) return f[pos][pre][upTimes];//如果已经统计过且符合要求就直接return 节省时间 
	int end=limit?a[pos]:9;//前一位是否达到上限 若达到该位上限也受限  
	ll ret=0;
	for(int i=0; i<=end; i++) {
		if(pre==-1) { //前导零 按情况分类讨论 
			if(i==0) ret=(ret+dfs(pos-1,-1,upTimes,limit&&i==end))%K;
			else ret=(ret+dfs(pos-1,i,upTimes,limit&&i==end))%K;
		} else if(upTimes==0) ret=(ret+dfs(pos-1,i,i>pre,limit&&i==end))%K;
		else if(upTimes==1&&i>=pre) ret=(ret+dfs(pos-1,i,upTimes,limit&&i==end))%K;
	}
	if(!limit&&pre!=-1) f[pos][pre][upTimes]=ret;//记忆化 
	return ret;
}
```
实质上pre也是描述状态的一部分，下面是一个更广泛的例子，以HDU 4507为例
```cpp
struct Rem{
	ll cnt,sum,sqsum;
	Rem():cnt(-1),sum(0),sqsum(0){}
	Rem(ll _cnt,ll _sum,ll _sqsum):cnt(_cnt),sum(_sum),sqsum(_sqsum){}
}f[MAXLEN][15][15];//对于复杂的状态我们使用结构体
Rem dfs(int pos,int sum1,int sum2,bool limit){
	if(pos==-1){
		if(sum1==0||sum2==0) return Rem(0,0,0);
		return Rem(1,0,0);
	}
	if(!limit&&f[pos][sum1][sum2].cnt!=-1) return f[pos][sum1][sum2];
	int end=limit?a[pos]:9;
	Rem ret,tail;ret.cnt=0;
	for(int i=0;i<=end;i++){
		if(i==7) continue;
		tail=dfs(pos-1,(sum1+i)%7,(sum2*10+i)%7,limit&&i==end);
		ret.cnt=(ret.cnt+tail.cnt)%MOD;
		ret.sum=(ret.sum+(((i*pow10[pos])%MOD)*tail.cnt)%MOD+tail.sum)%MOD;
		ret.sqsum=(ret.sqsum+((((i*pow10[pos])%MOD)*((i*pow10[pos])%MOD))%MOD*tail.cnt%MOD+(2*((i*pow10[pos])%MOD)*tail.sum)%MOD+tail.sqsum))%MOD;
	}
	if(!limit) f[pos][sum1][sum2]=ret;
	return ret;
}
```
