#include<bits/stdc++.h>

using namespace std;

int n;
int dp[510][510];
int ans[510][510];
int ddp[510][510];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            char c;
            cin>>c;
            dp[i][j]=c-'0';
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j+i<=n;j++)
        {
            int l=j,r=j+i;
            int tmp=0;
            for(int k=l+1;k<r;k++)
            {
                tmp+=ans[l][k]*dp[k][r];
                tmp%=10;
            }
            if(tmp!=dp[l][r]) ans[l][r]=1;
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cout<<ans[i][j];
        }
        cout<<'\n';
    }
}