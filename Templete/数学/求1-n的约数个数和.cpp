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
		j=n/(n/i);		 //		(n/i)��Լ��i�Դ𰸵Ĺ��� ���ڵ�һЩi�Դ𰸵Ĺ��ױض���ͬ (������ȡ����i<=n,��һ����i,n/i����ȵ�)
		q+=(j-i+1)*(n/i);//		���ǿ��Զಽ��Ծ����ͬһ��n/i�����е�n/iֵ��ͬ���Ҷ�Ϊ������ڵ�ĩβ
	}					 //		j���Ǽ���������ĩβ(��,ȡ��,�ٳ˻�ȥ����n/i����������i),i����ĩβ����.
}
