#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
typedef long long ll;
using namespace std;

ll dam[1000010],ata,atb,hpa,hpb;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Init()
{
	for (int i=1;i<=1000000;i++)
	{
		dam[i]=dam[i-1]+(ll)i;
	}
}

int main()
{
	Init();
	int T; readx(T);
	while (T--)
	{
		readx(hpa); readx(hpb); readx(ata); readx(atb);
		
		ll suma,sumb,lim1,lim2;
		string sola,solb;
		
		// first attack A
		lim1=lower_bound(dam+1,dam+1000001,hpa)-dam;
		lim2=lower_bound(dam+1,dam+1000001,hpa+hpb)-dam;
		suma=ata*lim1+atb*lim2;
		if (dam[lim2]-dam[lim1]<hpb)
		{
			ll ovflow=dam[lim1]-hpa;
			for (int i=1;i<=lim2;i++)
			{
				if (i==ovflow) sola+='B';
				else
				{
					if (i<=lim1) sola+='A';
					else sola+='B';
				}
				
			}
		}
		else
		{
			for (int i=1;i<=lim2;i++)
			{
				if (i<=lim1) sola+='A';
				else sola+='B';
			}
		}
		
		// first attack B
		lim1=lower_bound(dam+1,dam+1000001,hpb)-dam;
		lim2=lower_bound(dam+1,dam+1000001,hpa+hpb)-dam;
		sumb=atb*lim1+ata*lim2;
		
		ll ovflow=dam[lim1]-hpb;
		ll pos=upper_bound(dam+1,dam+1000001,ovflow)-dam -1; // possible A insert pos || NOTICE -1!!!!!!!!!!!!!!!!!!!!
		
		if (dam[pos]>=hpa-(dam[lim2]-dam[lim1])) // ok to kill for A prefix
		{
			for (int i=1;i<=pos;i++) solb+='A';
			for (int i=pos+1;i<=lim1;i++) solb+='B';
			for (int i=lim1+1;i<=lim2;i++) solb+='A';
		}
		else // not OK, put last A backward
		{
			ll remhp=hpa-(dam[lim2]-dam[lim1]);
			for (int i=1;i<=lim1;i++)
			{
				if (remhp>=i+i+1 || remhp==i) // move backward strategy
				{
					solb+='A';
					remhp-=i;
				}
				else solb+='B';
			}
			for (int i=lim1+1;i<=lim2;i++) solb+='A';
		}
		
		if (sumb<suma)
			cout<<sumb<<" "<<solb<<endl;
		else if (suma<sumb)
			cout<<suma<<" "<<sola<<endl;
		else
		{
			cout<<suma<<" ";
			if (sola<solb) cout<<sola<<endl;
			else cout<<solb<<endl;
		}
	}
}