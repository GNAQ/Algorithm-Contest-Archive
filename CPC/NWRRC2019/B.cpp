#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

double ve[18000000*2+10];

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
	int n; readx(n);
	
	for (int i=-18000000;i<=18000000;i++)
		ve[i+18000000] = sin(i);
	
	int mint=0;
	for (int i=0;i<=10000;i++)
	{
		if (ve[mint] > ve[i])
			mint = i;
	}
	
	int cnt = 1, cur = mint;
	
	printf("%d\n", cur - 18000000);
	if (n==1) return 0;
	
	for (int i=mint+1;i<=18000000*2;i++)
	{
		if (ve[i] > ve[cur] && 
			((ve[i] - ve[cur] < 0.00002 && i-cur <= 400) || 
			 (ve[i] - ve[cur] < 0.000043  && i-cur <= 1000) ||
			 (ve[i] - ve[cur] < 0.000058  && i-cur <= 3000) ||
			 (ve[i] - ve[cur] < 0.0000633)))
		{
			cnt++;
			cur = i;
			
			printf("%d\n", i - 18000000);
			if (cnt==n) break;
		}
	}
	
	return 0;
}