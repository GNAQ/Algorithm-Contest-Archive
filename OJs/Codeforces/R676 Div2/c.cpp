#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<queue>
#include<map>
#include<set>
typedef long long ll;
using namespace std;

char ch[100010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}



int main()
{
	scanf(" %s", ch+1);
	int len=strlen(ch+1);
	
	if (len==3)
	{
		printf("4\nL 2\nR 3\nL 4\nL 2\n");
		return 0;
	}
	printf("4\n");
	printf("L %d\n", len-1);
	len+=len-2;
	printf("R %d\n", len-1);
	len++;
	printf("L %d\n", len-1);
	len+=len-2;
	printf("L 2\n");
	return 0;
}