#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<stack>
typedef long long ll;
using namespace std;

int n, m;
int ai[100010], ki[10010];

struct Node
{
	int val, id;
	Node(int _val, int _id) : val(_val), id(_id) {}
	Node () {}
}s1[100010], s2[100010];
int h1, h2;

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
	readx(n); readx(m);
	for (int i=1;i<=n;i++) readx(ai[i]);
	
	for (int ii=1;ii<=m;ii++)
	{
		int k; readx(k);
		h1 = h2 = 0;
		
		int ans = 0, r1 = -1, r2 = -1;
		for (int i=1;i<=n;i++)
		{
			while (h1>=1 && s1[h1].val >= ai[i]) h1--; 
			while (h2>=1 && s2[h2].val <= ai[i]) h2--; 
			
			s2[++h2] = s1[++h1] = Node(ai[i], i);
			
			if (r1==-1 && r2==-1)
				if (s2[1].val-s1[1].val>k)
				{
					r1 = 1; r2 = 1;
				}
			
			if (r1>=1 && r2>=1)
			{
				if (r1>=h1) r1 = h1;
				if (r2>=h2) r2 = h2;
				while (1)
				{
					if (r2 < h2 && s2[r2+1].val - s1[r1].val > k && s2[r2].id <= s1[r1].id)
					{
						r2++;
						continue;
					}
					if (r1 < h1 && s2[r2].val - s1[r1+1].val > k && s1[r1].id <= s2[r2].id)
					{
						r1++;
						continue;
					}
					break;
				}
			}
			
			if (r1>=1 && r2>=1)
				ans+=min(s1[r1].id, s2[r2].id);
		}
		cout << ans << endl;
	}
}