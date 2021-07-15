#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<vector>
#include<string>
typedef long long ll;
using namespace std;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Solve()
{
	string ans[2]={"false", "true"};
	int a, b, op;
	readx(a);
	char ch1 = 0, ch2 = 0;
	ch1=getchar();
	ch2=getchar();
	readx(b);
	if (ch2==' ')
	{
		if (ch1=='<') op = 3; // <
		else op = 5; // >
	}
	else
	{
		if (ch1=='!') op = 1; // !=
		if (ch1=='=') op = 2; // ==
		if (ch1=='<') op = 4; // <=
		if (ch1=='>') op = 6; // >=
	}
	
	switch (op)
	{
	case 1:
		cout << ans[a!=b] << endl;
		break;
	case 2:
		cout << ans[a==b] << endl;
		break;
	case 3:
		cout << ans[a<b] << endl;
		break;
	case 4:
		cout << ans[a<=b] << endl;
		break;
	case 5:
		cout << ans[a>b] << endl;
		break;
	case 6:
		cout << ans[a>=b] << endl;
		break;
	default:
		while (1);
		break;
	}
	
}

int main()
{
	int T; readx(T);
	while (T--)
	{
		Solve();
	}
	
}