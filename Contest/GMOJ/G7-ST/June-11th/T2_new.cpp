#include <stdio.h>

const int MAXN = 30010, MAXM = 200010;
int head[MAXN], nxt[2 * MAXM], to[2 * MAXM], tot;
int num[MAXN];
int size[MAXN], hson[MAXN], dfn[MAXN], top[MAXN], deep[MAXN], cnt = 0;

void Add(int x, int y);
void Dfs1(int fa, int x);
void Dfs2(int fa, int x, int t);

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
    Dfs1(0, 1);
    Dfs2(0, 1, 1);
    for (int i = 1; i <= n; i++)
    {
        scanf ("%d", &num[i]);
    }
    int k;
    for (int i = 1; i <= m; i++)
    {
    }
}

void Dfs1(int fa, int x)
{
    deep[x] = deep[fa] + 1;
    int maxx = 0;
    size[x] = 1;
    for (int i = head[x]; i; i = nxt[i])
    {
        if (to[i] == fa) continue;
        Dfs(x, to[i]);
        size[x] += size[to[i]];
        if (size[to[i]] > maxx)
        {
            hson[x] = to[i];
        }
    }
}
void Dfs2(int fa, int x, int t)
{
    dfn[x] = ++cnt;
    top[x] = t;
    Dfs2(x, hson[x], t);
    for (int i = head[x]; i; i = nxt[i])
    {
        if (to[i] != fa && to[i] != hson[x])
        {
            Dfs2(x, to[i], to[i]);
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

