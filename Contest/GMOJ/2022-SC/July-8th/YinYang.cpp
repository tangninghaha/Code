#include <stdio.h>
#include <cstring>

const int MAXN = 1e5 + 1, MAXM = 1e5 + 1;

struct Edge
{
    Edge();
    int head[MAXN];
    int nxt[MAXM * 2];
    int to[MAXM * 2];
    int color[MAXM * 2];
    int tot;
    void Add(int u, int v, int c);
};
Edge G;

int deep[MAXN];
int fa[MAXN][18];
int log_2[MAXN];
int diss[MAXN];

void pre(int x);
int GetLCM(int x, int y);
bool Check();
int st, ed, lcm;
bool Dfs(int x, int w);
int Dfs2(int x, int w);

int main()
{
    log_2[1] = 0;
    log_2[2] = 1;
    for (int i = 3; i < MAXN; ++i)
    {
        log_2[i] = log_2[i >> 1] + 1;
    }
    int n;
    scanf("%d", &n);
    int u, v, c;
    for (int i = 1; i < n; ++i)
    {
        scanf("%d%d%d", &u, &v, &c);
        if (!c) c = -1;
        G.Add(u, v, c);
        G.Add(v, u, c);
    }
    deep[1] = 0;
    pre(1);
    long long ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = i + 1; j <= n; ++j)
        {
            if (i != j)
            {
                st = i;
                ed = j;
                if (Check())
                {
                    printf("%d %d\n", i, j);
                    ans++;
                }
            }
        }
    }
    printf("%lld", ans);
}
Edge::Edge()
{
    tot = 0;
}

void pre(int x)
{
    for (int i = G.head[x]; i; i = G.nxt[i])
    {
        if (G.to[i] != fa[x][0])
        {
            fa[G.to[i]][0] = x;
            for (int j = 1; j <= 17; ++j)
            {
                fa[G.to[i]][j] = fa[fa[G.to[i]][j - 1]][j - 1];
            }
            deep[G.to[i]] = deep[x] + 1;
            diss[G.to[i]] = G.color[i];
            pre(G.to[i]);
        }
    }
}
void Edge::Add(int u, int v, int c)
{
    ++tot;
    nxt[tot] = head[u];
    to[tot] = v;
    color[tot] = c;
    head[u] = tot;
}
bool Check()
{
    lcm = GetLCM(st, ed);
    if (deep[st] > deep[lcm])
    {
        if(Dfs(st, 0))
            return true;
        else if (Dfs(ed, 0))
            return true;
    }
    else
    {
        int k = st;
        st = ed;
        ed = k;
        if (Dfs(st, 0))
            return true;
    }
    return false;
}
int GetLCM(int x, int y)
{
    while(deep[x] != deep[y])
    {
        if (deep[x] < deep[y])
        {
            y = fa[y][log_2[deep[y] - deep[x]]];
        }
        else
        {
            x = fa[x][log_2[deep[x] - deep[y]]];
        }
    }
    if (x == y) return x;
    for (int i = 17; i >= 0; --i)
    {
        if (fa[x][i] != fa[y][i])
        {
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
}
bool Dfs(int x, int w)
{
    if (w == 0 && x != st)
    {
        if(Dfs2(ed, 0) + Dfs2(x, 0) == 0)
            return true;
    }
    if (x == lcm) return false;
    return Dfs(fa[x][0], w + diss[x]);
}
int Dfs2(int x, int w)
{
    if (x == lcm) return w;
    return Dfs2(fa[x][0], w + diss[x]);
}
