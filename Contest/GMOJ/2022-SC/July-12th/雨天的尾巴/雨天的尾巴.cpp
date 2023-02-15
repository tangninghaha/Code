#include <stdio.h>

const int MAXN = 2001;
int p[MAXN][MAXN]; /* 每个节点的救济粮的桶 */
int bh[MAXN]; /* 每个救济粮的编号 */
int tot_l;

struct Edge
{
    int head[MAXN];
    int nxt[MAXN * 2];
    int to[MAXN * 2];
    int tot;
    void Add(int x, int y);
};
Edge G;
int GetLCA(int u, int v);
void Update(int x, int y, int z);
int fa[MAXN], deep[MAXN];
void Dfs(int x);

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int u, v, w;
    for (int i = 1; i < n; ++i)
    {
        scanf("%d%d", &u, &v);
        G.Add(u, v);
        G.Add(v, u);
    }
    Dfs(1);
    bool pd = false;
    int gbh, lca;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d%d", &u, &v, &w);
        pd = false;
        for (int j = 1; j <= tot_l; ++j)
        {
            if (bh[j] == w)
            {
                gbh = j;
                pd = true;
                break;
            }
        }
        if (!pd)
        {
            ++tot_l;
            gbh = tot_l;
            bh[tot_l] = w;
        }
        lca = GetLCA(u, v);
        Update(u, lca, gbh);
        Update(v, lca, gbh);
        --p[lca][gbh];
    }
    int maxn, ans;
    for (int i = 1; i <= n; ++i)
    {
        maxn = 0;
        ans = 0;
        for (int j = 1; j <= tot_l; ++j)
        {
            if (p[i][j] > maxn || (maxn == p[i][j] && bh[j] < ans))
            {
                ans = bh[j];
                maxn = p[i][j];
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}

void Update(int x, int y, int z)
{
    while (x != y)
    {
        ++p[x][z];
        x = fa[x];
    }
    ++p[y][z];
}
void Dfs(int x)
{
    deep[x] = deep[fa[x]] + 1;
    for (int i = G.head[x]; i; i = G.nxt[i])
    {
        if (G.to[i] != fa[x])
        {
            fa[G.to[i]] = x;
            Dfs(G.to[i]);
        }
    }
    return;
}
int GetLCA(int u, int v)
{
    while (deep[u] != deep[v])
    {
        if (deep[u] < deep[v])
        {
            v = fa[v];
        }
        else
        {
            u = fa[u];
        }
    }
    if (u == v)
        return u;
    while (u != v)
    {
        u = fa[u];
        v = fa[v];
    }
    return u;
}
void Edge::Add(int x, int y)
{
    ++tot;
    nxt[tot] = head[x];
    to[tot] = y;
    head[x] = tot;
}
