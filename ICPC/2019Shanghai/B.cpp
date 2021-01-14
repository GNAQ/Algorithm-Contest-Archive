#include<bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int inf=0x3f3f3f3f;
const int N=100000+5;
 
int T,n;
string a[N];
unordered_map<string,int>mp;
 
bool check()
{
    for(int i=1;i<=n;i++)
    {
        string t="";
        int len=a[i].size();
        for(int j=0;j<len-1;j++)
        {
            t+=a[i][j];
            if(mp[t]) return true;
        }
        if(mp[a[i]]>1) return true;
    }
    return false;
}
 
int main()
{
    cin>>T;
    int cas=0;
    while(T--)
    {
        cout<<"Case #"<<++cas<<": ";
        cin>>n;
        mp.clear();
        for(int i=1;i<=n;i++)
        {
            cin>>a[i];
            mp[a[i]]++;
        }
        cout<<(check()?"No":"Yes")<<'\n';
    }
}