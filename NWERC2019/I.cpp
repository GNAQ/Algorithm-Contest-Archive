#include <bits/stdc++.h>
typedef long long ll;
using namespace std;


int main()
{
	int n;
	vector<int> vec;
	int tmp;
	scanf("%d", &n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d", &tmp);
		vec.push_back(tmp);
	}
	
	vector<int> vec2 = vec;
	sort(vec2.begin(), vec2.end());
	
	int l = 0, r = n-1;
	while (vec[l] == vec2[l]) l++;
	while (vec[r] == vec2[r]) r--;
	if (l>r)
	{
		printf("1 1\n");
		return 0;
	}
	
	bool ok = 1;
	for (int i=0;i<l;i++)
	{
		if (i+1<l && vec[i+1]<vec[i]) 
			ok = 0;
	}
	for (int i=n-1;i>r;i--)
		if (i-1>r && vec[i-1]>vec[i])
			ok = 0;
	for (int i=l;i<=r;i++)
		if (i+1<=r && vec[i+1]>vec[i])
			ok = 0;
	
	if (!ok)
	{
		puts("impossible");
		return 0;
	}
	printf("%d %d\n", l+1, r+1);
	return 0;
}