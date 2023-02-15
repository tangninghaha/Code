#include <cstdio>

/* Constant */
const int MAXN = 1e3 + 5;
const int MAXQ = MAXN * 2;
const int MAXM = 2e6 + 5;

/* Declaration */
int main();
long long Max(long long, long long);
void SPFA();

/* Class */
struct Graph
{
    int head[MAXN];
    int nxt[MAXM];
    int to[MAXM];
    int dis[MAXM];
    bool lx[MAXM];
    int tot;
    void Add(int, int, int, bool);
};

/* Variable */
int n, k;
int value[MAXN];
int queue[MAXQ][3];
long long v[MAXQ];
long long sum[MAXN];
bool vis[MAXN][2];
long long ans = 0;
Graph G;

/* Definition */
void Graph::Add(int _u, int _v, int _w, bool _lx)
{
    ++tot;
    nxt[tot] = head[_u];
    to[tot] = _v;
    dis[tot] = _w;
    lx[tot] = _lx;
    head[_u] = tot;
    return;
}
int main()
{
    freopen("jump.in", "r", stdin);
    freopen("jump.out", "w", stdout);
    int t;
    scanf("%d", &t);
    for (int fot = 1; fot <= t; ++fot)
    {
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &value[i]);
            sum[i] = sum[i - 1] + value[i];
        }
        for (int i = 1; i <= n; ++i)
        {
            for (int j = i; j <= n; ++j)
            {
                G.Add(i, j, sum[j] - sum[i - 1], 0);
                G.Add(j, i, sum[j] - sum[i - 1], 1);
            }
        }
        SPFA();
        printf("%lld\n", ans);
    }
}
void SPFA()
{
    for (int i = 1; i <= n; ++i)
    {
        vis[i][0] = vis[i][1] = false;
    }
    int head = 0, tail = 1;
    queue[1][0] = 1;
    queue[1][1] = 0;
    queue[1][2] = 0;
    v[1] = 0;
    int now, zt;
    while (head < tail)
    {
        ++head;
        now = queue[head][0];
        zt = queue[head][1];
        for (int i = G.head[now]; i; i = G.nxt[i])
        {
            if (G.lx[i] == zt)
            {
                ++tail;
                queue[tail][0] = G.to[i];
                queue[tail][1] = !zt;
                queue[tail][2] = queue[head][2] + 1;
                v[tail] = v[head] + G.dis[i];
                if (v[tail] < 0)
                {
                    --tail;
                    continue;
                }
                if (vis[G.to[i]][!zt])
                {
                    ans = Max(ans, k / queue[tail][2] * v[tail]);
                    --tail;
                }
                vis[G.to[i]][zt] = true;
            }
        }
    }
    return;
}
long long Max(long long _a, long long _b)
{
    return _a > _b ? _a : _b;
}
