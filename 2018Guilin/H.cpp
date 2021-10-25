#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

string s1, s2;
int len;
int pa[10010][3];
int suf[10010];

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Solve(int rid)
{
	cin >> s1 >> s2;
	len = s1.size();
	
	pa[0][1]=(s1[0]=='a');
	pa[0][2]=(s2[0]=='a');
	for (int i=1;i<len;i++)
	{
		pa[i][1] = pa[i-1][1] + (s1[i] == 'a');
		pa[i][2] = pa[i-1][2] + (s2[i] == 'a');
	}
	
	for (int i=len-1;i>=0;i--)
		suf[i] = suf[i+1] + (s1[i] != s2[i]);
	
	int pos = -1;
	for (int i=len-1;i>=0;i--)
		if (suf[i+1] >= abs(pa[i][1]-pa[i][2]) )
		{
			pos = i;
			break;
		}
	vector<char> ans(len);
	for (int i=0;i<=pos;i++) ans[i]='a';
	
	// val < 0 :  a of S1 < a of S2  -> add S1 matched chars
	// val > 0 :  a of S1 > a of S2  -> add S2 matched chars
	int val = pa[pos][1] - pa[pos][2];
	for (int i=pos+1;i<len;i++)
	{
		// dont care
		if (s1[i]==s2[i])
		{
			ans[i]='a';
			continue;
		}
		// have to reduce
		if (suf[i]==abs(val))
		{
			if (val < 0)
			{
				ans[i] = s1[i];
				val++;
			}
			if (val > 0)
			{
				ans[i] = s2[i];
				val--;
			}
		}
		// dont have to reduce
		else
		{
			if (s1[i]!='a' && s2[i]!='a')
				ans[i] = 'a';
			else
			{
				if (s1[i]=='a')
				{
					if (abs(val+1) <= suf[i+1]) // can put a
					{
						val++;
						ans[i] = 'a';
					}
					else // cannot put a
					{
						if (s2[i]=='b' && abs(val-1) > suf[i+1])
							ans[i]='c';
						else
						{
							ans[i]='b';
							if (s2[i]=='b') val--;
						}
					}
				}
				if (s2[i]=='a')
				{
					if (abs(val-1) <= suf[i+1]) // can put a
					{
						val--;
						ans[i] = 'a';
					}
					else // cannot put a
					{
						if (s1[i]=='b' && abs(val+1) > suf[i+1])
							ans[i] = 'c';
						else
						{
							ans[i]='b';
							if (s1[i]=='b') val++;
						}
					}
				}
			}
		}
	}
	
	printf("Case %d: ", rid);
	for (int i=0;i<len;i++)
		printf("%c", ans[i]);
	puts("");
}

void Clear()
{
	for (int i=0;i<=len+7;i++)
		suf[i]=pa[i][1]=pa[i][2]=0;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	int T; cin >> T;
	for (int t=1;t<=T;t++)
	{
		Solve(t);
		Clear();
	}
}