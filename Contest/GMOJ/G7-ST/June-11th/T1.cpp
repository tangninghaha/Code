#include <stdio.h>

const int MAXN = 30010, MAXM = 200010;
int head[MAXN], nxt[2 * MAXM], to[2 * MAXM], tot;
int num[MAXN];
int fa[MAXN][16];
int n;
long long sum[MAXN][16];
int deep[MAXN];
int log_2[MAXN];

void Add(int x, int y);
int GetLCA(int a, int b);
void InitLCA();
void Dfs(int father, int x, int deepth);
long long GetAns(int a, int b, int lca);

int main()
{
    int m;
    scanf ("%d%d", &n, &m);
    int u, v;
    for (int i = 1; i < n; i++)
    {
        scanf ("%d%d", &u, &v);
        Add(u, v);
        Add(v, u);
    }
    Dfs(0, 1, 1);
    InitLCA();
    for (int i = 1; i <= n; i++)
    {
        scanf ("%d", &num[i]);
    }
    int k;
    for (int i = 1; i <= m; i++)
    {
        scanf ("%d%d%d", &k ,&u, &v);
        if (k == 1)
            num[u] = v;
        else
            printf ("%lld\n", GetAns(u, v, GetLCA(u, v)));
    }
}

void Dfs(int father, int x, int deepth)
{
    deep[x] = deepth;
    fa[x][0] = father;
    for (int i = head[x]; i; i = nxt[i])
    {
        if (to[i] != father)
        {
            Dfs(x, to[i], deepth + 1);
        }
    }
}

void Add(int x, int y)
{
    tot++;
    nxt[tot] = head[x];
    to[tot] = y;
    head[x] = tot;
}

int GetLCA(int a, int b)
{
    while(deep[a] != deep[b])
    {
        if (deep[a] < deep[b]) b = fa[b][log_2[deep[a] - deep[b]]];
        else a = fa[a][log_2[deep[b] - deep[a]]];
    }
    if (a == b) return a;
    for (int i = 15; i >= 0; i--)
    {
        if (fa[a][i] != fa[b][i])
        {
            a = fa[a][i];
            b = fa[b][i];
        }
    }
    return fa[a][0];
}

void InitLCA()
{
    for (int i = 1; i <= 15; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            fa[j][i] = fa[fa[j][i - 1]][i - 1];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        sum[i][0] = num[i] + num[fa[i][0]];
    }
    for (int i = 1; i <= 15; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            sum[j][i] = sum[j][i - 1] + sum[fa[j][i - 1]][i - 1];
        }
    }
    log_2[1] = 0;
    for (int i = 2; i <= 30001; i++)
    {
        log_2[i] = log_2[i / 2] + 1;
    }
}

long long GetAns(int a, int b, int lca)
{
    long long ret = 0;
    while (a != lca)
    {
        ret += num[a];
        a = fa[a][0];
    }
    while (b != lca)
    {
        ret += num[b];
        b = fa[b][0];
    }
    ret += num[lca];
    return ret;
}
