#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;

int n,m;
int a[1010][1010],b[1010][1010];

int mlen[1010][1010],nlen[1010][1010],mpos[1000010],npos[1000010];
int ans;

pair<int,int> stk[1010];
int at=0;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Force_Pop()
{
	while (at>0)
	{
		ans=max(ans,stk[at].first*stk[at].second);
		at--;
		if (at>0) stk[at].second+=stk[at+1].second;
	}
}

int main()
{
	memset(a,0,sizeof(a)); 
	memset(b,0,sizeof(b));
	
	readx(n); readx(m);
	for (int i=1;i<=n;i++) 
		for (int j=1;j<=m;j++)
			readx(a[i][j]);
	for (int i=1;i<=n;i++) 
		for (int j=1;j<=m;j++)
		{
			readx(b[i][j]);
			mpos[ b[i][j] ] = j;
			npos[ b[i][j] ] = i;
		}
	
	for (int l=1;l<=n;l++)
	{
		mlen[l][m]=1;
		for (int i=m-1;i;i--)
		{
			if ((mpos[a[l][i]] == mpos[a[l][i + 1]] - 1) && (npos[a[l][i]] == npos[a[l][i + 1]]))
				mlen[l][i]=mlen[l][i+1]+1;
			else 
				mlen[l][i]=1;
		}
	}
	
	// for (int i=1;i<=n;i++)
	// 	for (int j=1;j<=m;j++)
	// 		printf("%d%c",mlen[i][j]," \n"[j==m]);
	
	for (int l=1;l<=m;l++)
	{
		nlen[n][l]=1;
		for (int i=n-1;i;i--)
		{
			if ((npos[a[i][l]] == npos[a[i + 1][l]] - 1) && (mpos[a[i][l]] == mpos[a[i + 1][l]]))
				nlen[i][l]=nlen[i+1][l]+1;
			else 
				nlen[i][l]=1;
		}
	}
	
	// for (int i=1;i<=n;i++)
	// 	for (int j=1;j<=m;j++)
	// 		printf("%d%c",nlen[i][j]," \n"[j==m]);
	
	for (int i=1;i<=m;i++)
	{
		at=1; stk[at]=make_pair(mlen[n][i],1);
		ans=max(ans,mlen[n][i]);
		for (int j=n-1;j>=1;j--)
		{
			if (nlen[j][i]==1) Force_Pop();
			int add=0;
			while (at>0 && stk[at].first>=mlen[j][i])
			{
				ans=max(ans,stk[at].first*stk[at].second);
				at--;
				if (at>0 && stk[at].first>=mlen[j][i])
					stk[at].second+=stk[at+1].second;
				else
					add=stk[at+1].second;
			}
			at++; 
			stk[at]=make_pair(mlen[j][i],add+1);
		}
		
		Force_Pop();
	}
	
	printf("%d\n",ans);
	return 0;
}