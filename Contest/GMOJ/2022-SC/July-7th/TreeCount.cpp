#include <stdio.h>
#include <cstring>
#define INF 707406379

const int MAXN = 1001, MAXM = 2 * 1001 * 1001;
const long long mod = 2147483647;
int head[MAXN], nxt[MAXM], to[MAXM], diss[MAXM], tot;
int dis1[MAXN];
int dis2[MAXN];
bool pd[MAXN];
bool c[MAXN];
int n, m;
long long ans = 0;

void Add(int u, int v, int w);
void Dfs(int x, int k);
void GetDis(int dis[], bool vis[]);

int main()
{
    memset(dis1, 127 / 3, sizeof(dis1));
    scanf("%d%d", &n, &m);
    int u, v, w;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d%d", &u, &v, &w);
        Add(u, v, w);
        Add(v, u, w);
    }
    dis1[1] = 0;
    GetDis(dis1, pd);
    Dfs(1, m);
    printf("%lld", ans % mod);
}

void GetDis(int dis[], bool vis[])
{
    int minn, p;
    for (int i = 1;i <= n; ++i)
    {
        minn = INF;
        p = 0;
        for (int j = 1; j <= n; ++j)
        {
            if (!vis[j] && dis[j] < minn)
            {
                minn = dis[j];
                p = j;
            }
        }
        vis[p] = 1;
        for (int j = head[p]; j; j = nxt[j])
        {
            if (diss[j] + dis[p] < dis[j] && !c[j])
            {
                dis[j] = dis[p] + diss[j];
            }
        }
    }
}

void Add(int u, int v, int w)
{
    tot++;
    nxt[tot] = head[u];
    to[tot] = v;
    diss[tot] = w;
    head[u] = tot;
}

void Dfs(int x, int k)
{
    if (k == n - 1)
    {
        memset(dis2, 127 / 3, sizeof(dis2));
        memset(pd, 0, sizeof(pd));
        dis2[1] = 0;
        GetDis(dis2, pd);
        bool bad = false;
        for(int i = 1; i <= n; ++i)
        {
            if (dis1[i] != dis2[i])
            {
                bad = true;
                break;
            }
        }
        if (!bad)
        {
            ans++;
            ans %= mod;
        }
        return;
    }
    if (x > m) return;
    c[x] = true;
    Dfs(x + 1, m - 1);
    c[x] = false;
    Dfs(x + 1, m);
    return;
}
