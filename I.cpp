#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll n, d[1010], t1[1010], t2[1010], t3[1010];
ll s[1010][4];

ll A[1010][2], B[1010][2];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

ll GetDis(int st, int ed, int w)
{
	if (ed < st)
	{
		return s[ed][w]+s[n][w]-s[st-1][w];
	}
	else 
		return s[ed][w] - s[st-1][w];
}

void Solve()
{
	for (int i=1;i<=n;i++) // 1 3 2
	{
		for (int j=1;j<i;j++) 
		{
			// init
			A[i][0]=0;
			B[j][0]=0;
			A[i][1]=t1[i];
			B[j][1]=t2[i];
			int p1, p2, w1, w2;
			for (int k=1;k<n;k++)
			{
				w1 = i + k;
				if (w1>n) w1-=n;
				A[w1][0]=A[p1]][1]+d[p1];
				A[w1][1]=A[w1][0]+t1[w1];
				p1 = w1;
				w2 = j + k;
				if (w2>n) w2-=n;
				B[w2][0]=B[p2][1]+d[p2];
				B[w2][1]=B[w2][0]+t2[w2];
				p2 = w2;
			}
			
			// check
			ll st=, ed;
			for (int k=1;k<n;k++)
			{
				
			}
			
		}
	}
}

int main()
{
	readx(n);
	for (int i=1;i<=n;i++) 
	{
		readx(d[i]);
		s[i][0]=s[i-1][0]+d[i];
	}
	for (int i=1;i<=n;i++)
	{
		readx(t1[i]);
		s[i][1]=s[i-1][1]+t1[i];
	}
	for (int i=1;i<=n;i++)
	{
		readx(t2[i]);
		s[i][2]=s[i-1][2]+t2[i];
	}
	for (int i=1;i<=n;i++)
	{
		readx(t3[i]);
		s[i][3]=s[i-1][3]+t3[i];
	}
	
	Solve();
	
}