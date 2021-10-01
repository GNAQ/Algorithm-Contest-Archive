#include<bits/stdc++.h>
using namespace std;

struct _Node
{
	int val, lid, rid;
	int sta;
}node[10000010];

int LK, RK;
int len, nid, mid;

template<typename int_t>
void readx(int_t &x)
{
	x=0; int_t k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

void Debug()
{
	printf("LK = %d | RK = %d | mid = %d\n", LK, RK, mid);
	printf("len = %d\n", len);
	int x = LK;
	do
	{
		printf("(%d) <- [%d] -> (%d)  || sta = %d\n", node[x].lid, x, node[x].rid, node[x].sta);
		if (x==RK) break;
		x = node[x].rid;
	} while (1);
	puts("\n\n");
}

int main()
{
	ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
	int q; cin >> q;
	
	LK=-1; RK=-1; len = 0; nid=0; mid=-1;
	
	for (int qq=1;qq<=q;qq++)
	{
		char op; cin>>op;
		
		if (op=='L')
		{
			nid++;
			if (len) // 有长度
			{
				node[nid].rid=LK;
				node[nid].lid = -1;
				node[LK].lid = nid;
				LK = nid;
				
				node[nid].sta = 1;
				
				if (len%2) // 奇数：不动
				{
					;
				}
				else // 偶数：左移
				{
					node[mid].sta = 2;
					mid = node[mid].lid;
					node[mid].sta = 3;
				}
			}
			else // 空
			{
				LK=RK=mid=nid;
				node[nid].lid=-1; node[nid].rid=-1;
				node[nid].sta=3; // node[nid].val=nid;
			}
			len++;
		}
		else if (op=='R')
		{
			nid++;
			if (len)
			{
				node[nid].lid = RK;
				node[nid].rid = -1;
				node[RK].rid = nid;
				RK = nid;
				
				node[nid].sta = 2;
				
				if (len%2)
				{
					node[mid].sta = 1;
					mid = node[mid].rid;
					node[mid].sta = 3;
				}
				else
				{
					;
				}
			}
			else
			{
				LK=RK=mid=nid;
				node[nid].lid=-1; node[nid].rid=-1;
				node[nid].sta=3;
			}
			len++;
		}
		else if (op=='Q')
		{
			printf("%d\n", mid);
		}
		else if (op=='G')
		{
			int x; cin >> x;
			
			if (len==1)
			{
				LK=RK=mid=-1;
				node[x].sta=-1;
				node[x].lid=node[x].rid=0;
			}
			else if (len==2)
			{
				if (x == LK)
				{
					LK=mid=RK;
					node[RK].lid = node[RK].rid = -1;
					node[RK].sta = 3;
				}
				if (x == RK)
				{
					RK=mid=LK;
					node[LK].lid = node[LK].rid = -1;
					node[LK].sta = 3;
				}
			}
			else
			{
				if (x==mid)
				{
					if (len%2)
					{
						int tmp = mid;
						mid = node[mid].rid;
						node[mid].sta = 3;
						node[mid].lid = node[tmp].lid;
						node[node[tmp].lid].rid = mid;
					}
					else
					{
						int tmp = mid;
						mid = node[mid].lid;
						node[mid].sta = 3;
						node[mid].rid = node[tmp].rid;
						node[node[tmp].rid].lid = mid;
					}
				}
				else if (node[x].sta == 1)
				{
					if (x==LK) // 左头
					{
						LK = node[x].rid;
						node[LK].lid = -1;
					}
					else
					{
						node[node[x].lid].rid = node[x].rid;
						node[node[x].rid].lid = node[x].lid;
					}
					if (len%2)
					{
						node[mid].sta = 1;
						mid = node[mid].rid;
						node[mid].sta = 3;
					}
					else
					{
						;
					}
				}
				else if (node[x].sta == 2)
				{
					if (x==RK) // 左头
					{
						RK = node[x].lid;
						node[LK].rid = -1;
					}
					else
					{
						node[node[x].lid].rid = node[x].rid;
						node[node[x].rid].lid = node[x].lid;
					}
					if (len%2)
					{
						;
					}
					else
					{
						node[mid].sta = 2;
						mid = node[mid].lid;
						node[mid].sta = 3;
					}
				}
			}
			len--;
		}
		// Debug();
	}
	return 0;
}