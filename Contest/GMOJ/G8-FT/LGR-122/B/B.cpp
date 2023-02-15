#include <cstdio>

/* Constant */
const int MAXN = 5005;

/* Class */
class Graph
{
    public:
        int head[MAXN];
        int nxt[MAXN * 2];
        int to[MAXN * 2];
        int tot;
        void Add(int u, int v);
};

/* Declaration */
long long Min(long long _a, long long _b);
void Chos(int x);
long long Dfs(int x);
int main();
void Init(int x);
void Bj(int x);

/* Variable */
int n;
Graph G;
long long ans = 1e18;
long long f[MAXN];
bool zt[MAXN];
int sz[MAXN];
int nsz[MAXN];
bool vis[MAXN];
int fa[MAXN];

/* Definition */
void Graph::Add(int u, int v)
{
    ++tot;
    nxt[tot] = head[u];
    to[tot] = v;
    head[u] = tot;
    return;
}
void Chos(int x)
{
    if (x > n)
    {
        for (int i = 1; i <= n; ++i)
        {
            sz[i] = nsz[i];
            vis[i] = true;
        }
        long long ret = Dfs(1);
        for (int i = 2; i <= n; ++i)
        {
            if (vis[i])
            {
                return;
            }
        }
        ans = Min(ret, ans);
        return;
    }
    zt[x] = true;
    Chos(x + 1);
    zt[x] = false;
    Chos(x + 1);
}
long long Dfs(int x)
{
    long long ret = 0;
    for (int i = G.head[x]; i; i = G.nxt[i])
    {
    	if (G.to[i] != fa[x])
    	{
	        ret += Dfs(G.to[i]);
	        if (zt[G.to[i]])
	            sz[x] -= sz[G.to[i]] - 1;
        }
    }
    if (zt[x])
    {
        Bj(x);
        ret += f[sz[x]];
    }
    return ret;
}
void Bj(int x)
{
    for (int i = G.head[x]; i; i = G.nxt[i])
    {
    	if (G.to[i] == fa[x])
    		continue;
        Bj(G.to[i]);
        vis[G.to[i]] = false;
    }
    return;
}
void Init(int x)
{
    nsz[x] = 1;
    for (int i = G.head[x]; i; i = G.nxt[i])
    {
    	if (G.to[i] == fa[x])
    		continue;
    	fa[G.to[i]] = x;
        Init(G.to[i]);
        nsz[x] += nsz[G.to[i]];
    }
    return;
}
int main()
{
    scanf("%d", &n);
    for (int i = 2; i <= n; ++i)
    {
        scanf("%lld", &f[i]);
    }
    int u, v;
    for (int i = 1; i < n; ++i)
    {
        scanf("%d%d", &u, &v);
        G.Add(u, v);
        G.Add(v, u);
    }
    Init(1);
    Chos(1);
    printf("%lld", ans);
    return 0;
}
long long Min(long long _a, long long _b)
{
    return _a < _b ? _a : _b;
}
