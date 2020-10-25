#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<iterator>
#include<cstdlib>
#include<queue>
#include<vector>
#include<map>
#include<set>
using namespace std;
typedef long long ll;
typedef ostream_iterator<int> os_iter_int;

char ch1[1000010],ch2[1000010];
int arr[1000010];

template<typename inp_t>
void readx(inp_t& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void KMP_Init(char* str,int* fail)
{
	int pos=0,len=strlen(str+1);
	for (int i=2;i<=len;i++)
	{
		while (pos && str[i]!=str[pos+1]) pos=fail[pos];
		if (str[i]==str[pos+1]) pos++;
		fail[i]=pos;
	}
}

vector<int> KMP_Match(char* strs,char* strt, int* fail)
{
	vector<int> result;
	int pos=0,lens=strlen(strs+1),lent=strlen(strt+1);
	
	for (int i=1;i<=lens;i++)
	{
		while (pos && strt[pos+1]!=strs[i]) pos=fail[pos];
		if (strs[i]==strt[pos+1]) pos++;
		if (pos==lent)
		{
			result.push_back(i-lent+1);
			pos=fail[pos];
		}
	}
	return result;
}

int main()
{
	scanf("%s%s",ch1+1,ch2+1);
	KMP_Init(ch2,arr);
	vector<int> result = KMP_Match(ch1,ch2,arr);
	
	for (auto v:result) printf("%d\n",v);
	int len=strlen(ch2+1);
	for (int i=1;i<=len;i++) printf("%d%c",arr[i]," \n"[i==len]);
}