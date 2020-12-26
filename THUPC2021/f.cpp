#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
typedef long long ll;
using namespace std;

int n,m;
int a[10010];

int out[500][500];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int trans[10010];

int getNext(int i)
{
	for (int j=i+1;j<=m;j++) if (a[j]==n/2+1) return j;
	return -1;
}

int main()
{
	memset(out, 0, sizeof(out));
	int lim;
	
	readx(n); readx(m);
	for (int i=1;i<=m;i++) readx(a[i]);
	
	if (n%2==0)
	{
		// while (1);
		lim=n/2; 
		for (int i=1;i<=m;i++)
		{
			if (a[i]>lim)
			{
				printf("No\n");
				return 0;
			}
		}
		
		for (int i=1;i<=m;i++)
		{
			if (i%2)
			{
				for (int j=1;(j+1)/2<=a[i];j+=2)
					out[j][i]=1;
			}
			else
			{
				for (int j=2;j/2<=a[i];j+=2)
					out[j][i]=1;
			}
		}
		
		printf("Yes\n");
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
				printf("%d%c", out[i][j], " \n"[j==m]);
	}
	else
	{
		int need = 0; // 需要换序
		memset(trans, 0, sizeof(trans));
		lim = n/2+1;
		// int lpos=0, ok=1;
		int lpos=0, ok=0;
		
		for (int i=1;i<=m;i++) 
		{
			if (a[i]==lim)
			{
				trans[0]=(i+1)%2;
				lpos=i;
				break;
			}
		}
		
		for (int i=1;i<=m;i++)
		{
			if (a[i]>lim)
			{
				printf("No\n");
				// while (1);
				return 0;
			}
			if (a[i]==lim)
			{
				if (i%2==lpos%2) // ok case 2
				{
					lpos=i;
				}
				else if (ok) // ok case 1
				{
					lpos=i;
					ok=0;
				}
				else 
				{
					printf("No\n");
					// while (1);
					return 0;
				}
				trans[i]=1;
				int npos=getNext(i);
				// cout<<"cur "<< i <<"NPOS = "<<npos<<endl;
				if (npos!=-1 && npos%2!=i%2) need=1;
				else need=0;
				// need=0;
			}
			else // a[i]<lim
			{
				if (trans[i-1]==-2) trans[i]=1;
				else if (trans[i-1]==-1) trans[i]=0;
				else trans[i]=(trans[i-1]+1)%2;
				
				if (need && (!ok)) 
				{
					if (i>1 && ((trans[i-1]==0 && a[i]+a[i-1]<=n/2) || (trans[i-1]==1 && a[i]+a[i-1]<=n/2+1))) // try to greedy
					{
						trans[i]=trans[i-1]=(trans[i-1]-2);
						ok=1;
					}
				}
			}
		}
		
		// cout<<"$ "<<trans[0]<<endl;
		// for (int i=1;i<=m;i++) printf("%d%c", trans[i], " \n"[i==m]);
		
		for (int i=1;i<=m;i++)
		{
			if (trans[i]==1)
			{
				for (int j=1;(j+1)/2<=a[i];j+=2)
					out[j][i]=1;
			}
			else if (trans[i]==0)
			{
				for (int j=2;j/2<=a[i];j+=2)
					out[j][i]=1;
			}
			else if (trans[i]==-2)
			{
				for (int j=2;j/2<=a[i];j+=2)
					out[j][i]=1;
				i++;
				int cnt=0;
				for (int j=n-1;cnt<a[i];j-=2)
					{ out[j][i]=1; cnt++; }
			}
			else if (trans[i]==-1)
			{
				for (int j=1;(j+1)/2<=a[i];j+=2)
					out[j][i]=1;
				i++;
				int cnt=0;
				for (int j=n;cnt<a[i];j-=2)
					{ out[j][i]=1; cnt++; }
			}
		}
		
		printf("Yes\n");
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
				printf("%d%c",out[i][j], " \n"[j==m]);
	}
	
	return 0;
}