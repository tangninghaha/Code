#include <stdio.h>
#define INF 100000005
typedef long long int64;
const int MAXN = 1e5 + 5;

struct Graph
{
    int tot;
    int head[MAXN];
    int nxt[2 * MAXN];
    int to[2 * MAXN];
    void Add(int u, int v);
};
int64 Sovle(int n);
void DP(int x);
void InitF(int n);
void InitDfn(int x);
bool FindCycle(int x);
void FileIO();
int64 Min(int64 a, int64 b);
int main();

int64 f[MAXN][2][2];
int fa[MAXN], dfn[MAXN];
int tot_dfn;
int cycle_point_a, cycle_point_b;
int color_cycle_point_a, color_cycle_point_b;
Graph g;

void Graph::Add(int u, int v)
{
    ++tot;
    nxt[tot] = head[u];
    to[tot] = v;
    head[u] = tot;
    return;
}
void DP(int x)
{
    int64 sum_f_1_0 = 0;
    int64 sum_f_1_1 = 0;
    int son;
    for (int i = g.head[x]; i; i = g.nxt[i])
    {
        son = g.to[i];
        if (fa[son] != x)
        {
            continue;
        }
        DP(son);
        sum_f_1_0 += f[son][1][0];
        sum_f_1_1 += f[son][1][1];
    }
    for (int i = g.head[x]; i; i = g.nxt[i])
    {
        son = g.to[i];
        if (fa[son] != x)
        {
            continue;
        }
        f[x][0][1] = Min(f[x][0][1], f[son][0][0] + sum_f_1_0 - f[son][1][0] + 1);
        f[x][1][1] = Min(f[x][1][1], f[son][0][1] + sum_f_1_1 - f[son][1][1]);
    }
    f[x][0][0] = sum_f_1_0 + 1;
    f[x][1][0] = sum_f_1_1;
    if (x == cycle_point_a)
    {
        if (color_cycle_point_a == 0)
        {
            f[x][1][0] = f[x][1][1] = INF;

        }
        else
        {
            f[x][0][0] = f[x][0][1] = INF;
        }
        if (color_cycle_point_b == 0)
        {
            f[x][0][1] = f[x][0][0];
            f[x][1][1] = f[x][1][0];
            f[x][0][0] = INF;
            f[x][1][0] = INF;
        }
    }
    if (x == cycle_point_b)
    {
        if (color_cycle_point_b == 0)
        {
            f[x][1][0] = f[x][1][1] = INF;

        }
        else
        {
            f[x][0][0] = f[x][0][1] = INF;
        }
        if (color_cycle_point_a == 0)
        {
            f[x][0][1] = f[x][0][0];
            f[x][1][1] = f[x][1][0];
            f[x][0][0] = INF;
            f[x][1][0] = INF;
        }
    }
    return;
}
void FileIO()
{
    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);
}
bool FindCycle(int x)
{
    int son;
    for (int i = g.head[x]; i; i = g.nxt[i])
    {
        son = g.to[i];
        if (son == fa[x])
        {
            continue;
        }
        if (dfn[son] < dfn[x])
        {
            cycle_point_a = son;
            cycle_point_b = x;
            return true;
        }
        if (FindCycle(son))
            return true;
    }
    return false;
}
void InitDfn(int x)
{
    dfn[x] = ++tot_dfn;
    int son;
    for (int i = g.head[x]; i; i = g.nxt[i])
    {
        son = g.to[i];
        if (dfn[son])
        {
            continue;
        }
        fa[son] = x;
        InitDfn(son);
    }
    return;
}
void InitF(int n)
{
    for (int i = 1; i <= n; ++i)
    {
        f[i][0][0] = f[i][0][1] = f[i][1][0] = f[i][1][1] = INF;
    }
    return;
}

int main()
{
    FileIO();
    int n;
    scanf("%d", &n);
    int u, v;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d", &u, &v);
        g.Add(u, v);
        g.Add(v, u);
    }
    printf("%lld", Sovle(n));
    return 0;
}
int64 Min(int64 a, int64 b)
{
    return a < b ? a : b;
}
int64 Sovle(int n)
{
    int64 ret = 1e16 + 5;
    InitDfn(1);
    FindCycle(1);
    for (int i = 0; i <= 1; ++i)
    {
        for (int j = 0; j <= 1; ++j)
        {
            InitF(n);
            color_cycle_point_a = i;
            color_cycle_point_b = j;
            DP(1);
            ret = Min(ret, Min(f[1][0][1], f[1][1][1]));
        }
    }
    if (ret >= INF)
        return -1;
    return ret;
}
