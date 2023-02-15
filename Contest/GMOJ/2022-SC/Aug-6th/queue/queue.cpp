#include <stdio.h>

const int MAXN = 1005;
const int MAXM = 1000005;
const int mod = 10007;

struct Graph
{
    int head[MAXN];
    int nxt[MAXM];
    int to[MAXM];
    int tot;
    void Add(int u, int v);
};
Graph G;

bool vis[MAXN];
int xs[MAXN];
int f[MAXN];
int c[MAXN][MAXN];
int sz[MAXN];
#ifdef DEBUG
int cnt[MAXN];
#endif

int n;
void Dfs(int x);
void FileIO();
void Init();
int main();
#ifdef DEBUG
void Print()
{
    for (int i = 1; i <= G.tot; ++i)
    {
//        printf("%d\n", cnt[i]);
    }
}
#endif

void Graph::Add(int u, int v)
{
//    printf("%d %d\n", u, v);
    ++tot;
    nxt[tot] = head[u];
    to[tot] = v;
    head[u] = tot;
}
void Dfs(int x)
{
#ifdef DEBUG
    ++cnt[x];
#endif
    f[x] = 1;
    int son1 = -1;
    int son2 = -1;
    sz[x] = 1;
    for (int i = G.head[x]; i; i = G.nxt[i])
    {
        Dfs(G.to[i]);
        sz[x] += sz[G.to[i]];
        if (son1 == -1)
            son1 = G.to[i];
        else if (son2 == -1)
            son2 = G.to[i];
    }
    if (son1 == -1)
    {
        return;
    }
    else if (son2 == -1)
    {
        f[x] = f[son1] % mod;
    }
    else
    {
        f[x] = f[son1] * f[son2];
        f[x] %= mod;
        f[x] *= c[sz[son1] + sz[son2]][sz[son1]];
        f[x] %= mod;
    }
    return;
}
void FileIO()
{
    freopen("queue.in", "r", stdin);
//    freopen("queue.out", "w", stdout);
    return;
}
void Init()
{
    c[0][0] = 1;
    for (int i = 1; i < MAXN; ++i)
    {
        for (int j = 0; j < MAXN; ++j)
        {
            if (j == 0)
                c[i][j] = 1;
            else
                c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
            c[i][j] %= mod;
        }
    }
}
int main()
{
    FileIO();
    Init();
    int t;
    scanf("%d", &t);
    int k;
    for (int dat = 1; dat <= t; ++dat)
    {
        G.tot = 0;
        scanf("%d", &n);
        int x;
        int tott = 0;
        for (int i = 1; i <= n; ++i)
        {
        	G.head[i] = 0;
            sz[i] = 0;
		}
        for (int i = 1; i <= n; ++i)
        {
            tott = 0;
            scanf("%d", &k);
            for (int j = 1; j <= k; ++j)
            {
                scanf("%d", &x);
                for (int l = tott; l <= tott; ++l)
                {
                	G.Add(xs[l], x);
				}
                if (tott == 0)
					G.Add(i, x);
                ++tott;
				xs[tott] = x;
            }
        }
        Dfs(1);
        printf("%d\n", f[1]);
    }
    return 0;
}
