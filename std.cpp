#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define mst(a, b) memset((a), (b), sizeof(a))
#define mp(a, b) make_pair(a, b)
#define pi acos(-1)
#define pii pair<int, int>
#define pb push_back
const int INF = 0x3f3f3f3f;
const double eps = 1e-6;
const int maxn = 1e6 + 10;
const int maxm = 1e5 + 10;
const ll mod = 998244353;

int n, k;
string s1, s2;
int st[maxn], cnt[maxn];

string F(string s)
{
	if (k == 1)
		return "";
	int top = 0;
	for (int i = 0; i < n; i++)
	{
		if (top && st[top] == s[i] - '0')
		{
			cnt[top]++;
			if (cnt[top] == k)
				top--;
		}
		else
		{
			st[++top] = s[i] - '0';
			cnt[top] = 1;
		}
	}
	s = "";
	for (int i = 1; i <= top; i++)
	{
		while (cnt[i])
		{
			s += st[i];
			cnt[i]--;
		}
	}
	return s;
}

int main()
{
#ifdef local
	freopen("data.txt", "r", stdin);
//    freopen("data.txt", "w", stdout);
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k >> s1 >> s2;
	if (F(s1) == F(s2))
		cout << "Yes" << endl;
	else
		cout << "No" << endl;
	return 0;
}