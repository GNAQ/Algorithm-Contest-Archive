#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<string>
#include<set>
typedef long long ll;
using namespace std;

ll ans;
int a[6][6];
int d[6];
int ex, ey;
const int w = 3, mod = 20027777;
set<ll> hset;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int Fin() // NO = 0; BLACK = -1; WHITE = 1
{
	for (int i=1;i<=4;i++)
		for (int j=1;j<=2;j++) if (a[i][j]!=0)
			if (a[i][j]==a[i][j+1] && a[i][j+1]==a[i][j+2])
				return a[i][j];
				
	for (int i=1;i<=2;i++)
		for (int j=1;j<=4;j++) if (a[i][j]!=0)
			if (a[i][j]==a[i+1][j] && a[i+1][j]==a[i+2][j])
				return a[i][j];
	
	// /
	for (int i=1;i<=2;i++)
		for (int j=1;j<=2;j++) if (a[i][j]!=0)
			if (a[i][j]==a[i+1][j+1] && a[i+1][j+1]==a[i+2][j+2])
				return a[i][j];
	
	// forw
	for (int i=3;i<=4;i++)
		for (int j=1;j<=2;j++) if (a[i][j]!=0)
			if (a[i][j]==a[i-1][j+1] && a[i-1][j+1]==a[i-2][j+2])
				return a[i][j];
	
	return 0;
}

ll GetH()
{
	ll hs = 0;
	for (int i=1;i<=4;i++)
		for (int j=1;j<=4;j++)
			hs = ( hs * w + (a[i][j]+1) );
	return hs;
}

void Print()
{
	cout << endl;
	for (int i=4;i>=1;i--)
		for (int j=1;j<=4;j++)
			printf("%d%c", a[i][j], " \n"[j==4]);
	cout<<"_____________"<<endl;
	for (int i=1;i<=4;i++) printf("%d%c", d[i], " \n"[i==4]);
	
	cout << endl << endl;
}

void DFS(int turn)
{
	ll hs = GetH();
	if (hset.find(hs)!=hset.end()) return;
	
	hset.insert(hs);
	
	if (a[ex][ey]==-1) return;
	if (a[ex][ey]==1)
	{
		// Print();
		if (Fin()==1) ans++;
		return;
	}
	if (Fin()!=0) return;
	
	for (int i=1;i<=4;i++) if (d[i]<4)
	{
		d[i]++;
		a[d[i]][i] = turn;
		DFS(-turn);
		a[d[i]][i] = 0;
		d[i]--;
	}
}

int main()
{
	int x; readx(x);
	readx(ex); readx(ey);
	
	d[x]=1;
	a[1][x]=-1;
	
	DFS(1);
	
	cout << ans << endl;
	return 0;
}