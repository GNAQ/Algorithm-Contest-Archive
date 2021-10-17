#include <bits/stdc++.h>
using namespace std;

int n;
map< int, pair<int, int>> mp;
vector<pair<double, double>> ve;

int main()
{
	char ca, cb, cc; 
	scanf("%d%c", &n, &cc);
	int cnt[2]={0, 0};
	pair<int, char> tmp;
	for (int i=1;i<=n;i++)
	{
		scanf("%c%c%d%c", &tmp.second, &ca, &tmp.first, &cb);
		if (tmp.second == '+')
		{
			mp[tmp.first].second++;
			cnt[1]++;
		}
		else
		{
			mp[tmp.first].first++;
			cnt[0]++;
		}
	}
	
	int TP = cnt[1], FN = 0;
	int TN = 0, FP = cnt[0];
	double FPR = 0, TPR = 0;
	map<int, pair<int, int> >::iterator it = mp.begin();
	for (;it!=mp.end();it++)
	{
		TPR = (double) TP / cnt[1];
		FPR = (double) FP / cnt[0];
		ve.push_back(make_pair(FPR, TPR));
		
		TP -= it->second.second;
		FN += it->second.second;
		FP -= it->second.first;
		TN += it->second.first;
	}
	TPR = (double) TP / cnt[1];
	FPR = (double) FP / cnt[0];
	ve.push_back(make_pair(FPR, TPR));
	
	double ans = 0;
	for (int i=1;i<ve.size();i++)
		ans += fabs(ve[i].first - ve[i-1].first) * ve[i].second;
	
	printf("%.12lf\n", ans);
}