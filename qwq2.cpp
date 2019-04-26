#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<queue>
using namespace std;
typedef long long ll;
typedef ostream_iterator<int> os_iter_int;

int n,m;
char t[10010],s[1510][1510];
double x[10010],xi[10010];

char ans[10010];

template<typename int_t>
void readx(int_t& x)
{
    x=0; int_t k=1; char ch=0;
    while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
    while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
    x*=k;
}

namespace ACAM
{
	struct ACAM_Node
	{
		int ch[10],fail,id;
		double val;
	}node[1510];
	int nsiz=0;
	
	void Ins(char* chr,int len,int _id)
	{
		int now=0;
		for (int i=1;i<=len;i++)
		{
			if (!node[now].ch[chr[i]-'0']) node[now].ch[chr[i]-'0']=++nsiz;
			now=node[now].ch[chr[i]-'0'];
		}
		node[now].id=_id;
	}
	
	queue<int> que;
	void GetFail()
	{
		int cac; 
		for (int i=0;i<10;i++) if (node[0].ch[i]) 
			que.push(node[0].ch[i]);
		
		while (!que.empty())
		{
			cac=que.front(); que.pop(); 
			for (int i=0;i<10;i++)
			{
				if (node[cac].ch[i])
				{
					node[node[cac].ch[i]].fail=node[node[cac].fail].ch[i];
					que.push(node[cac].ch[i]);
				}
				else node[cac].ch[i]=node[node[cac].fail].ch[i];
			}
		}
	}
	
	void Make()
	{
		for (int i=1;i<=nsiz;i++)
		{
			int cac=node[i].fail;
			node[i].val=x[node[i].id];
			while (cac)
			{
				node[i].val+=x[node[cac].id];
				cac=node[cac].fail;
			}
		}
	}
};

double dp[1510][1510];
int pre[1510][1510][2];
int Judge()
{
	using namespace ACAM;
	for (int i=0;i<=n;i++)
		for (int j=0;j<=nsiz;j++) 
			dp[i][j]=-20000000;
	
	dp[0][0]=0;
	for (int i=1;i<=n;i++)
	{
		if (t[i]=='.') 
		{
			for (int w=0;w<10;w++)
				for (int j=0;j<=nsiz;j++) 
				{
					int ch=node[j].ch[w];
					if (dp[i-1][j]+node[ch].val>dp[i][ch])
					{
						dp[i][ch]=dp[i-1][j]+node[ch].val;
						pre[i][ch][0]=j;
						pre[i][ch][1]=w+'0';
					}
				}
		}
		else for (int j=0;j<=nsiz;j++) 
		{
			int ch=node[j].ch[t[i]-'0'];
			if (dp[i-1][j]+node[ch].val>dp[i][ch])
			{
				dp[i][ch]=dp[i-1][j]+node[ch].val;
				pre[i][ch][0]=j;
				pre[i][ch][1]=t[i];
			}
		}
		
//		for (int j=1;j<=nsiz;j++) printf("%.2lf ",dp[i][j]);
//		cout<<endl;
	}
	
	for (int i=1;i<=nsiz;i++) if (dp[n][i]>0) return i;
	return false;
}

void Print()
{
	using namespace ACAM;
	for (int i=1;i<=nsiz;i++)
	{
		printf("id = %d\n",i);
		for (int j=0;j<10;j++) printf("%d ",node[i].ch[j]);
		printf("\nid %d | fail %d\n\n",node[i].id,node[i].fail);
	}
}

int main()
{
//	freopen("13.in","r",stdin);
//	freopen("dat.out","w",stdout);
	
	readx(n); readx(m);
	scanf("%s",t+1);
	for (int i=1;i<=m;i++)
	{
		scanf("%s%lf",s[i]+1,&xi[i]);
		ACAM::Ins(s[i],strlen(s[i]+1),i);
		xi[i]=log2(xi[i]);
	}
	
	// deb
//	for (int i=1;i<=m;i++) printf("%.2lf%c",xi[i]," \n"[i==m]);
	
	ACAM::GetFail(); //Print(); return 0;
	
	for (int i=1;i<=n;i++) ans[i]=t[i];
	double l=0,r=100;
	for (int wt=1;wt<=32;wt++) // time
	{
		double mid=(l+r)/2.0;
		for (int i=1;i<=m;i++) x[i]=xi[i]-mid;
		ACAM::Make();
		
		// deb
//		printf("mid = %.2lf\n",mid);
//		for (int i=1;i<=m;i++) printf("%.2lf ",x[i]);
//		cout<<endl<<"----"<<endl;
//		for (int i=1;i<=ACAM::nsiz;i++) printf("%.2lf ",ACAM::node[i].val);
//		cout<<endl<<endl<<endl;
		
		int now=Judge();
		if (now)
		{
			for (int i=n;i>=1;i--)
			{
				ans[i]=pre[i][now][1];
				now=pre[i][now][0];
			}
			l=mid;
		}
		else r=mid;
		
//		cout<<endl<<endl<<endl;
//		system("pause"); 
	}
	for (int i=1;i<=n;i++) printf("%c",ans[i]);
}
