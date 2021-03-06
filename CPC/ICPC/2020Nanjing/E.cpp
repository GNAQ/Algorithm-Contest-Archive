#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
typedef long long ll;
using namespace std;
const int MAXN=1e5+100;
char ch[MAXN];
template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

int main()
{
	int T,xx,yy,l,r,u,d;cin>>T;
	while(T--)
	{
		l=r=u=d=0;
		scanf("%d%d",&xx,&yy);
		scanf("%s",ch);
		int len=strlen(ch);
		for(int i=0;i<=len-1;i++)
		{
			if(ch[i]=='L') l++;
			if(ch[i]=='R') r++;
			if(ch[i]=='U') u++;
			if(ch[i]=='D') d++;
		}
		if(xx==r-l&&yy==u-d)
		{
			printf("Impossible\n");
			continue;
		}
		if(xx==0&&yy==0)
		{
			printf("Impossible\n");
			continue;
		}
		
		
		if(l==0&&r==0)
		{
			if(u>=d)
			{
				if(xx==0&&yy>=0&&yy<=u-d)
				{
					printf("Impossible\n");
					continue;
				}
				if(yy>=0)
				{
					for(int i=1;i<=d;i++)
						printf("D");
					for(int i=1;i<=u;i++)
						printf("U");
					printf("\n");
				}
				else {
					for(int i=1;i<=u;i++)
						printf("U");
					for(int i=1;i<=d;i++)
						printf("D");
					printf("\n");					
				}
				continue;
			}
			if(u<=d)
			{
				if(xx==0&&yy<=0&&yy>=u-d)
				{
					printf("Impossible\n");
					continue;
				}
				if(yy>=0)
				{
					for(int i=1;i<=d;i++)
						printf("D");
					for(int i=1;i<=u;i++)
						printf("U");
					printf("\n");
				}
				else {
					for(int i=1;i<=u;i++)
						printf("U");
					for(int i=1;i<=d;i++)
						printf("D");	
					printf("\n");				
				}
				continue;
			}
		}
		
		
		if(u==0&&d==0)
		{
			if(r>=l)
			{
				if(yy==0&&xx>=0&&xx<=r-l)
				{
					printf("Impossible\n");
					continue;
				}
				if(xx>=0)
				{
					for(int i=1;i<=l;i++)
						printf("L");
					for(int i=1;i<=r;i++)
						printf("R");
					printf("\n");
				}
				else {
					for(int i=1;i<=r;i++)
						printf("R");
					for(int i=1;i<=l;i++)
						printf("L");
					printf("\n");					
				}
				continue;
			}
			if(r<=l)
			{
				if(yy==0&&xx<=0&&xx>=r-l)
				{
					printf("Impossible\n");
					continue;
				}
				if(xx>=0)
				{
					for(int i=1;i<=l;i++)
						printf("L");
					for(int i=1;i<=r;i++)
						printf("R");
					printf("\n");
				}
				else {
					for(int i=1;i<=r;i++)
						printf("R");
					for(int i=1;i<=l;i++)
						printf("L");
					printf("\n");					
				}
				continue;
			}
		}
		
		if(l==r)
		{
			if(xx==0)
			{
				for(int i=1;i<=l;i++)
					printf("L");
				for(int i=1;i<=u;i++)
					printf("U");
				for(int i=1;i<=d;i++)
					printf("D");
				for(int i=1;i<=r;i++)
					printf("R");
				printf("\n");
				continue;
			}
		}
		
		if(u==d)
		{
			if(yy==0)
			{
				for(int i=1;i<=u;i++)
					printf("U");
				for(int i=1;i<=l;i++)
					printf("L");
				for(int i=1;i<=r;i++)
					printf("R");
				for(int i=1;i<=d;i++)
					printf("D");
				printf("\n");
				continue;
			}
		}
		
		if(u>=d&&r>=l)
		{
			if((xx==0)||(yy==u-d))
			{
				for(int i=1;i<=l;i++)
					printf("RL");
				for(int i=1;i<=r-l;i++)
					printf("R");
				for(int i=1;i<=d;i++)
					printf("UD");
				for(int i=1;i<=u-d;i++)
					printf("U");
				printf("\n");
				continue;
			}
			for(int i=1;i<=d;i++)
				printf("UD");
			for(int i=1;i<=u-d;i++)
				printf("U");
			for(int i=1;i<=l;i++)
				printf("RL");
			for(int i=1;i<=r-l;i++)
				printf("R");
			printf("\n");
			continue;			
		}
		
		if(u>=d&&r<=l)
		{
			if((xx==0)||(yy==u-d))
			{
				for(int i=1;i<=r;i++)
					printf("LR");
				for(int i=1;i<=l-r;i++)
					printf("L");
				for(int i=1;i<=d;i++)
					printf("UD");
				for(int i=1;i<=u-d;i++)
					printf("U");
				printf("\n");
				continue;
			}
			for(int i=1;i<=d;i++)
				printf("UD");
			for(int i=1;i<=u-d;i++)
				printf("U");
			for(int i=1;i<=r;i++)
				printf("LR");
			for(int i=1;i<=l-r;i++)
				printf("L");
			printf("\n");
			continue;			
		}
		
		if(u<=d&&r<=l)
		{
			if((xx==0)||(yy==u-d))
			{
				for(int i=1;i<=r;i++)
					printf("LR");
				for(int i=1;i<=l-r;i++)
					printf("L");
				for(int i=1;i<=u;i++)
					printf("DU");
				for(int i=1;i<=d-u;i++)
					printf("D");
				printf("\n");
				continue;
			}
			for(int i=1;i<=u;i++)
				printf("DU");
			for(int i=1;i<=d-u;i++)
				printf("D");
			for(int i=1;i<=r;i++)
				printf("LR");
			for(int i=1;i<=l-r;i++)
				printf("L");
			printf("\n");
			continue;			
		}
		
		if(u<=d&&r>=l)
		{
			if((xx==0)||(yy==u-d))
			{
				for(int i=1;i<=l;i++)
					printf("RL");
				for(int i=1;i<=r-l;i++)
					printf("R");
				for(int i=1;i<=u;i++)
					printf("DU");
				for(int i=1;i<=d-u;i++)
					printf("D");
				printf("\n");
				continue;
			}
			for(int i=1;i<=u;i++)
				printf("DU");
			for(int i=1;i<=d-u;i++)
				printf("D");
			for(int i=1;i<=l;i++)
				printf("RL");
			for(int i=1;i<=r-l;i++)
				printf("R");
			printf("\n");
			continue;			
		}
	}
	return 0;
}