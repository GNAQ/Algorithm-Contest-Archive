#pragma GCC optimize(3)
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

int G[110][110];
int dp[1<<19];
map<string,int> arcname;
string name[24];
bool vis[1<<19];
int val[24], n,m;
int pre[24];

void addedge(int u,int v)
{
	G[u][v]=1;
}

void clear()
{
	memset(dp,-1,sizeof(dp));
	memset(vis,0,sizeof(vis));
	for (int i=0;i<20;i++) name[i].clear();
	memset(G,0,sizeof(G));
	memset(val,0,sizeof(val));
	memset(pre,0,sizeof(pre));
    arcname.clear();
}

int Toint(string s)
{
    int res=0;
    for(int i=0;i<s.size();i++)
    {
        res+=(s[i]-'0')*pow(10,s.size()-i-1);
    }
    return res;
}

int main()
{
    int T;
    cin>>T;
    while(T--)
    {
		
		map<string, int> mp;
        scanf("%d%d", &n, &m);
        memset(dp, -1, sizeof(dp));
        memset(val, 0, sizeof(val));
        memset(pre, 0, sizeof(pre));
        getchar();
        string s, name;
        for(int k = 0; k < n; k++) {
            int flag = 0;
            getline(cin, s);
            int l = s.size();
            for(int i = 0; i < l; i++) {
                if (!flag && s[i] >= '0' && s[i] <= '9') {
                    flag = i;
                }
                if (flag) val[k] = val[k]*10+s[i]-'0';
            }
            name = s.substr(0, flag-1);
            mp[name] = k;
        }
        while (m--) {
            getline(cin, s);
            int l = s.size(), l1;
            int flag = 0;
            string xx;
            for(int i = 0; i < l; i++) {
                if (s[i] == '-' && !flag) {
                    flag = 1;
                    l1 = i-1;
                }
                if (flag == 1 && s[i] == ' ') {
                    flag = 2;
                    continue;
                }
                if (flag == 2) xx += s[i];
            }
            s = s.substr(0, l1);
            pre[mp[xx]] |= 1<<mp[s];
        }
		
		dp[0]=0;
		for(int j = 0; j < (1<<n)-1; j++) {
            if (dp[j] < 0) continue;
            int num = 0;
            for(int i = 0; i < n; i++) {
                num += j>>i&1;
            }
            for(int i = 0; i < n; i++) {
                int xx = j|((1<<i));
                if (xx != j && (j&pre[i]) == pre[i]) {
                    dp[xx] = max(dp[xx], dp[j]+val[i]*(num+1));
                }
            }
        }
        printf("%d\n", dp[(1<<n)-1]);
		
    }
}
