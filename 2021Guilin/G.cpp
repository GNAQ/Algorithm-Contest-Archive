#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

string str;
int n;
vector<int> pos;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

bool Check(int v)
{
	int lpos = 0;
	for (int i = 0; i < pos.size(); i++)
	{
		int p = pos[i];
		if ((p - lpos - 1) > v)
		{
			return false;
		}
		if ((p - lpos - 1) == v)
		{
			lpos = p + (v-1);
			if (i<pos.size()-1) 
				lpos = min(lpos, pos[i+1]-1);
		}
		else
		{
			lpos = p + v;
			if (i < pos.size()-1)
				lpos = min(lpos, pos[i+1]-1);
		}
	}
	if (lpos >= n) return true;
	return false;
}

void Solve()
{
	readx(n);
	cin >> str;
	
	for (int i=0;i<n;i++)
		if (str[i] == '1')
			pos.push_back(i + 1);
	
	if (pos.size() == n)
	{
		printf("0\n");
		return;
	}
	
	int l = 0, r = n + 1;
	int ans = 1e9;
	while (l<=r)
	{
		int mid = (l+r)/2;
		if (Check(mid))
		{
			ans = mid;
			r = mid - 1;
		}
		else
		{
			l = mid + 1;
		}
	}
	printf("%d\n", ans);
}


void Clear()
{
	pos.clear();
	str.clear();
}


int main()
{
	int T; readx(T);
	while (T--)
	{
		Solve();
		Clear();
	}
	
	
}