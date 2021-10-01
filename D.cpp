#include <bits/stdc++.h>
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

bool Isint(ll x)
{
	return (long long)sqrt(x)*(long long)sqrt(x)==x;
}
int n;

bool In(ll x,ll y)
{
	return x<=1000000&&y<=1000000&&x>=0&&y>=0;
}

int main()
{

	cin >> n;
	mt19937 mtgen(time(NULL));
	uniform_int_distribution<int> dist(0, 1000000);

	for (int w = 1; w <= n; w++)
	{
		ll ox = dist(mtgen), oy = dist(mtgen);
		cout << ox << " " << oy << endl;
		ll r2;
		cin >> r2;
		ll r = sqrt(r2);
		
		for (ll i = 0; i <= r; i++)
		{
			if (Isint(r2 - i * i))
			{
				ll j = sqrt(r2 - i * i);
				ll d;
				if (In(ox + i, oy + j))
				{
					cout << ox + i << ' ' << oy + j << endl;
					cin >> d;
					if (d == 0)
						break;
				}
				if (In(ox - i, oy - j))
				{
					cout << ox - i << ' ' << oy - j << endl;
					cin >> d;
					if (d == 0)
						break;
				}
				if (In(ox + i, oy - j))
				{
					cout << ox + i << ' ' << oy - j << endl;
					cin >> d;
					if (d == 0)
						break;
				}
				if (In(ox - i, oy + j))
				{
					cout << ox - i << ' ' << oy + j << endl;
					cin >> d;
					if (d == 0)
						break;
				}
			}
		}
	}
}