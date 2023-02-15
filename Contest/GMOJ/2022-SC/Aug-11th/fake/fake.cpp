#include <cstdio>
#include <cstring>

/* Constant */
const int MAXN = 1e5 + 5;

/* Declaration */
void Init(int x);
void Dfs(int x, int chos);
bool Check(int x);
int main();
void Add(int u, int v);
void FileIO();

/* Variable */
int fa[MAXN];
int dep[MAXN];
int c[MAXN];
int p1[MAXN], p2[MAXN];
int head[MAXN];
int nxt[2 * MAXN];
int to[2 * MAXN];
int cnt[MAXN];
int tot;
int chos_num[MAXN];
int n, m;
int ans = 0;

/* Definition */
void Init(int x)
{
    dep[x] = dep[fa[x]] + 1;
    for (int i = head[x]; i; i = nxt[i])
    {
        if (to[i] != fa[x])
        {
            fa[to[i]] = x;
            Init(to[i]);
        }
    }
}

void Dfs(int x, int chos)
{
    if (chos - 1 > ans)
    {
        if (Check(chos))
        {
            if (chos > ans)
                ans = chos;
        }
    }
    if (chos > m)
        return;
    if (x > m)
        return;
    chos_num[chos] = x;
    Dfs(x + 1, chos + 1);
    Dfs(x + 1, chos);
}
bool Check(int x)
{
    memset(cnt, 0, sizeof(cnt));
    int aa, bb;
    for (int i = 1; i <= x; ++i)
    {
        aa = p1[chos_num[i]];
        bb = p2[chos_num[i]];
        while (aa != bb)
        {
            if (dep[aa] > dep[bb])
            {
                ++cnt[aa];
                aa = fa[aa];
            }
            else
            {
                ++cnt[bb];
                bb = fa[bb];
            }
        }
        ++cnt[bb];
    }
    for (int i = 1; i <= n; ++i)
    {
        if (c[i] < cnt[i])
            return false;
    }
    return true;
}
int main()
{
    FileIO();
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &c[i]);
    }
    int u, v;
    for (int i = 1; i < n; ++i)
    {
        scanf("%d%d", &u, &v);
        Add(u, v);
        Add(v, u);
    }
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &p1[i], &p2[i]);
    }
    Init(1);
    Dfs(1, 1);
    printf("%d", ans);
    return 0;
}
void FileIO()
{
    freopen("fake.in", "r", stdin);
    freopen("fake.out", "w", stdout);
    return;
}
void Add(int u, int v)
{
    ++tot;
    nxt[tot] = head[u];
    to[tot] = v;
    head[u] = tot;
}
