#include <cstdio>

/* Constant */
const int MAXN = 1e6 + 5;
const int MAXM = 2e6 + 5;

/* Class */
struct Graph
{
    int head[MAXN];
    int nxt[MAXM];
    int to[MAXM];
    int rd[MAXN];
    int tot;
    void Add(int, int);
};

/* Declaration */
int main();

/* Variable */
Graph G;
bool pd[MAXN];

/* Definition */
int main()
{
    freopen("pointsetop.in", "r", stdin);
    freopen("pointsetop.out", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    int u, v;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", &u, &v);
        G.Add(u, v);
    }
    for (int i = 1; i <= n; ++i)
    {
        if (G.rd[i])
        {
            for (int j = G.head[i]; j; j = G.nxt[j])
            {
                pd[G.to[j]] = true;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (!pd[i])
        {
            ++ans;
        }
    }
    printf("%d", ans);
    return 0;
}
void Graph::Add(int _u, int _v)
{
    ++tot;
    to[tot] = _v;
    nxt[tot] = head[_u];
    head[_u] = tot;
    ++rd[_v];
    return;
}
