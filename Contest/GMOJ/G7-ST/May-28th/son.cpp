#include <stdio.h>

const int MAXN = 40010, MAXM = 1e7 + 5;

int fa[MAXN];
int deep[MAXN];
//int head[MAXM], to[MAXM], nxt[MAXM], tot;
//
//void Add(int x, int y)
//{
//	tot++;
//	nxt[tot] = head[x];
//	to[tot] = y;
//	head[x] = tot;
//	return;
//}
//
//void Dfs(int x, int d)
//{
//	deep[x] = d;
//	for (int i = head[x]; i; i = nxt[i])
//	{
//		Dfs(to[i], d + 1);
//	}
//	return;
//}

bool gf(int x, int p)
{
	if(x == p) return 1;
	if (fa[x] == x)
	{
		return 0;
	}
	return gf(fa[x], p);
}

int main()
{
	for (int i = 0; i <= 40000; i++)
	{
		fa[i] = i;
	}
	int n;
	
	scanf("%d", &n);
	int u, v;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", &u, &v);
		if(v != -1)
		{
			fa[u] = v;
		}
	}
	
//	Dfs(0, 0);
	
	int m;
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d", &u, &v);
		if (gf(v, u))
		{
			printf("1\n");
		}
		else if (gf(u, v))
		{
			printf("2\n");
		}
		else
		{
			printf("0\n");
		}
	}
	return 0;
}
