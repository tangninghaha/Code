#include <cstdio>

/* Constant */
const int MAXN = 1e5 + 5;
const int MAXM = 2e5 + 5;
const int MAXQ = 5e6 + 5;
const int T = 5e6;
const long long INF = 1e18 + 5;
const int MAXK = 25;
const long long mod = 998244353;

/* Class */
class Graph
{
    public:
        int head[MAXN];
        int nxt[MAXM * 2];
        int to[MAXM * 2];
        long long dis[MAXM * 2];
        int tot;
        void Add(int u, int v, long long w);
};

/* Declaration */
long long Bfs();
int main();
void Dfs(int);
int Max(int, int);
long long Max(long long, long long);
void FileIO();
int qpow(int, int);

/* Variable */
Graph g;
long long diss[MAXN];
bool chos[MAXN];
int queue[MAXQ];
int fire[MAXK];
bool vis[MAXN];
int k, n, m;
long long y_max;
int non;

/* Definition */
void Dfs(int x_)
{
    if (x_ > k)
    {
        long long ret = Bfs();
        if (ret == y_max)
        {
            ++non;
        }
        return;
    }
    chos[fire[x_]] = false;
    Dfs(x_ + 1);
    chos[fire[x_]] = true;
    Dfs(x_ + 1);
    return;
}
long long Bfs()
{
    int head = 0;
    int tail = 0;
    for (int i = 1; i <= n; ++i)
    {
        diss[i] = INF;
        if (chos[i])
        {
            diss[i] = 0;
            ++tail;
            queue[tail] = i;
        }
    }
    int now;
    long long ret = 0;
    while (head < tail)
    {
        ++head;
        if (head == T)
            head = 1;
        now = queue[head];
        for (int i = g.head[now]; i; i = g.nxt[i])
        {
            if (diss[g.to[i]] > diss[now] + g.dis[i])
            {
                diss[g.to[i]] = diss[now] + g.dis[i];
                if (!vis[g.to[i]])
                {
                    ++tail;
                    if (tail == T)
                        tail = 1;
                    queue[tail] = g.to[i];
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        ret = Max(ret, diss[i]);
    }
    return ret;
}
int main()
{
    FileIO();
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= k; ++i)
    {
        scanf("%d", &fire[i]);
        chos[fire[i]] = true;
    }
    int u, v;
    long long w;
    for (int j = 1; j <= m; ++j)
    {
        scanf("%d%d%lld", &u, &v, &w);
        g.Add(u, v, w);
        g.Add(v, u, w);
    }
    y_max = Bfs();
    Dfs(1);
    long long alll = qpow(2, k);
    long long ans = non;
    ans *= qpow(alll, mod - 2);
    ans %= mod;
    printf("%lld", ans);
    return 0;
}
int qpow(int x, int y)
{
    if (!y)
        return 1;
    if (y == 1)
        return x;
    long long ret = qpow(x, y / 2) % mod;
    if (y & 1)
    {
        return (((ret * ret) % mod) * x) % mod;
    }
    else 
    {
        return (ret * ret) % mod;
    }
    return 1;
}
int Max(int a_, int b_)
{
    return a_ > b_ ? a_ : b_;
}
long long Max(long long a_, long long b_)
{
    return a_ > b_ ? a_ : b_;
}
void Graph::Add(int u, int v, long long w)
{
    ++tot;
    nxt[tot] = head[u];
    to[tot] = v;
    dis[tot] = w;
    head[u] = tot;
    return;
}
void FileIO()
{
    freopen("flame.in", "r", stdin);
    freopen("flame.out", "w", stdout);
    return;
}
