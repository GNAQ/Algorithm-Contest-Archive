#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int MAXN=5000;
int sum[MAXN],last,k;
char a[MAXN],b[MAXN];
int main()
{
	int T;cin>>T;
	while(T--)
	{		
		cin>>k;scanf("%s%s",a+1,b+1);
		int ans=0,Ans,lena=strlen(a+1),lenb=strlen(b+1);
		for(register int x=1;x<=lena;x++)
		{
			int maxlen=min(lenb,lena-x+1);
			for(register int y=1;y<=maxlen;y++)
				if(a[x+y-1]==b[y])
					sum[y]=sum[y-1];
				else sum[y]=sum[y-1]+1;
			last=0;
			for(int i=1;i<=maxlen;i++)
			{
				while(sum[i]-sum[last]>k)
					last++;
				ans=max(ans,i-last);
			}
		}
		for(register int x=1;x<=lenb;x++)
		{
			int maxlen=min(lena,lenb-x+1);
			for(register int y=1;y<=maxlen;y++)
				if(b[x+y-1]==a[y])
					sum[y]=sum[y-1];
				else sum[y]=sum[y-1]+1;
			last=0;
			for(int i=1;i<=maxlen;i++)
			{
				while(sum[i]-sum[last]>k)
					last++;
				ans=max(ans,i-last);
			}
		}
		cout<<ans<<endl;
	}
}
