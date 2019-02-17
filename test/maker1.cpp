#include<cstdio>
#include<iostream>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<algorithm>
using namespace std;



template<typename inp_typ>
void readx(inp_typ& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}



int main()
{
	srand(time(0));
	int n,m;
	readx(n); readx(m);
	
	freopen("dat.in","w",stdout);
	printf("%d %d\n",n,m);
	for (int i=1;i<=n;i++)
	{
		printf("%d %d\n",rand()%1000+1,1002);
	}
	
	
}