#include <bits/stdc++.h>
using namespace std;

const char CHARSET[4] = {'L', 'R', 'U', 'D'};

int main()
{
	mt19937(time(NULL));
	uniform_int_distribution<int> dist(0, 3);
	for (int i=1;i<=49999;i++)
	{
		putchar(CHARSET[dist(mtgen)]);
	}
	putchar('\n');
}