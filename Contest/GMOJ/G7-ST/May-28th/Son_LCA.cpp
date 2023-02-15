//LCA
#include <stdio.h>

const int MAXN = 40010;
int log_2[MAXN], two_pow[17];
int deep[MAXN];
int fa[MAXN][17];
int head[MAXN], to[MAXN], nxt[MAXN], tot;

void Add(int x, int y)
{
	tot++;
	to[tot] = y;
	nxt[tot] = head[x];
	head[x] = tot;
}
void Dfs(int x, int father, int d)
{
	deep[x] = d;
	fa[x][0] = father;
	for (int i = 1; i <= 16; i++)
	{
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	}
	for (int i = head[x]; i; i = nxt[i])
	{
		Dfs(to[i], x, d + 1);
	}
}

void Init() {
	log_2[1] = 0;
	log_2[2] = 1;
	for (int i = 3; i < MAXN; i++)
	{
		log_2[i] = log_2[i / 2] + 1;
	}
	two_pow[0] = 1;
	for (int i = 1; i <= 16; i++)
	{
		two_pow[i] = two_pow[i - 1] * 2;
	}
}

int main()
{
	Init();
	int n;
	scanf("%d", &n);
	int u, v;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d", &u, &v);
		if (v == -1)
		{
			v = 40001;
		}
		Add(v, u);
	}
	Dfs(40001, 40002, 0);
	int m;
	scanf("%d", &m);
	int u_, v_;
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d", &u, &v);
		u_ = u;
		v_ = v;
		int y = deep[u] - deep[v];
		if (y < 0) {
			y = -y;
			while (y)
			{
				int k = log_2[y];
				v = fa[v][k];
				y -= two_pow[log_2[y]];
			}
		}
		else
		{
			while (y)
			{
				int k = log_2[y];
				u = fa[u][k];
				y -= two_pow[log_2[y]];
			}
		}
		if(u == v) {
			if(deep[u_] > deep[v_]) {
				printf("2\n");
			}
			else
				printf("1\n");
		}
		else
			printf("0\n");
//		for (int j = 16; j >= 0; j--)
//		{
//			if (fa[u][j] != fa[v][j])
//			{
//				u = fa[u][j];
//				v = fa[v][j];
//			}
//		}
//		int lca = u;
//		if (lca == u_)
//		{
//			printf("1\n");
//		}
//		else if (lca == v_)
//		{
//			printf("2\n");
//		}
//		else
//		{
//			printf("0\n");
//		}
	}
	return 0;
}
