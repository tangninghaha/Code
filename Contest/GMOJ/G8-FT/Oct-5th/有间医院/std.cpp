#include <cstdio>

/* Class */
struct Graph
{
    int head[85];
    int nxt[85];
    int to[85];
    int tot;
    void Add(int, int);
};

/* Declaration */
int main();
void JiuZhen(int);
long long LCM(long long, long long);
long long GCD(long long, long long);

/* Variable */
bool vis[85];
int a[5][85];
int g[5];
int cnt[5];
int b[85];
int cycle[85];
Graph G;

/* Definition */
int main()
{
    int p;
    scanf("%d%d%d%d%d", &g[1], &g[2], &g[3], &g[4], &p);
    while (g[1] | g[2] | g[3] | g[4] | p)
    {
        cnt[1] = g[1];
        cnt[2] = g[2];
        cnt[3] = g[3];
        cnt[4] = g[4];
        int xx = 1;
        for (int i = 1; i <= 4; ++i)
        {
            for (int j = 1; j <= g[i]; ++j)
            {
                a[i][j] = xx++;
            }
        }
        for (int i = 1; i <= p; ++i)
        {
            JiuZhen((i - 1) % 4 + 1);
        }
        xx = 0;
        for (int i = 1; i <= 4; ++i)
        {
            for (int j = 1; j <= cnt[i]; ++j)
            {
                b[++xx] = a[i][j];
            }
        }
        G.tot = 0;
        for (int i = 1; i <= xx; ++i)
        {
            vis[i] = true;
            if (i != b[i])
            {
                G.Add(b[i], i);
                vis[i] = false;
            }
        }
        int cycle_tot = 0;
        int now;
        for (int i = 1; i <= xx; ++i)
        {
            if (!vis[i])
            {
                ++cycle_tot;
                ++cycle[cycle_tot];
                now = i;
                vis[now] = true;
                for (int j = G.head[now];; j = G.head[now])
                {
                    if (vis[G.to[j]])
                        break;
                    now = G.to[j];
                    vis[now] = true;
                    ++cycle[cycle_tot];
                }
            }
        }
        long long lcm = 1;
        for (int i = 1; i <= cycle_tot; ++i)
        {
            lcm = LCM(lcm, cycle[i]);
        }
        printf("%lld\n", lcm);
        for (int i = 1; i <= cycle_tot; ++i)
        {
            cycle[i] = 0;
        }
        scanf("%d%d%d%d%d", &g[1], &g[2], &g[3], &g[4], &p);
    }
}
void JiuZhen(int x)
{
    int nxt = x + 1 == 5 ? 1 : x + 1;
    int tmp = a[x][1];
    for (int i = 1; i < cnt[x]; ++i)
    {
        a[x][i] = a[x][i + 1];
    }
    --cnt[x];
    ++cnt[nxt];
    a[nxt][cnt[nxt]] = tmp;
    return;
}

void Graph::Add(int _u, int _v)
{
    ++tot;
    nxt[tot] = head[_u];
    to[tot] = _v;
    head[_u] = tot;
    return;
}
long long LCM(long long _a, long long _b)
{
    return _a / GCD(_a, _b) * _b;
}
long long GCD(long long _a, long long _b)
{
    if (!_b)
        return _a;
    return GCD(_b, _a % _b);
}
