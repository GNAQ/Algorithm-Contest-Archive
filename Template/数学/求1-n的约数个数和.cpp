#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<iterator>
#include<algorithm>
#include<utility>
#include<cstdlib>
using namespace std;

long long getsum(long long n)
{
	register long long q=0;
	for (register long long i=1,j=0;i<=n;i=j+1)
	{
		j=n/(n/i);		 //		(n/i)是约数i对答案的贡献 相邻的一些i对答案的贡献必定相同 (考虑下取整及i<=n,有一部分i,n/i是相等的)
		q+=(j-i+1)*(n/i);//		于是可以多步跳跃。在同一个n/i周期中的n/i值相同，且都为这个周期的末尾
	}					 //		j就是计算了周期末尾(除,取整,再乘回去就是n/i周期中最大的i),i跳到末尾后面.
}
