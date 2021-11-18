#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN=1e5+100;
int ji[MAXN][31],pos[MAXN][31];
void add(int dat,int p)
{
	for(int i=0;i<=30;i++)
	{
		ji[p][i]=ji[p-1][i];
		pos[p][i]=pos[p-1][i];
	}
	int tmp_dat=dat,tmp_p=p;
	for(int i=30;i>=0;i--)
		if(tmp_dat&(1<<i))
		{
			if(!ji[p][i])
			{
				ji[p][i]=tmp_dat;
				pos[p][i]=tmp_p;
				return ;
			}
			else {
				if(pos[p][i]<tmp_p)
				{
					swap(tmp_p,pos[p][i]);
					swap(tmp_dat,ji[p][i]);
				}
				tmp_dat^=ji[p][i];
			}
		}
}
int query(int l,int r)
{
	int ans=0;
	for(int i=30;i>=0;i--)
		if(ji[r][i]&&(!((ans>>i)&1)))
		{
			if(pos[r][i]>=l)
				ans^=ji[r][i];
		}
	return ans;
}
int main()
{
	int T;cin>>T;
	while(T--)
	{
		int n,q,k;
		cin>>n>>q>>k;
		int ks=k^((1<<30)-1);
		for(int i=1;i<=n;i++)
		{
			int tmp;
			scanf("%d",&tmp);
			
			tmp&=ks;
			add(tmp,i);
		}
		for(int i=1;i<=q;i++)
		{
			int l,r;
			scanf("%d%d",&l,&r);
			printf("%d\n",k|query(l,r));
		}
	}
}
