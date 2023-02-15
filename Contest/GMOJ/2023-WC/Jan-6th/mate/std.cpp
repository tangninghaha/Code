#include <cstdio>

/* Constant */
const int MAXN = 2e5 + 5;
const long long mod = 1e9 + 7;

/* Class */
struct Graph
{
    int head[MAXN];
    int nxt[MAXN * 4];
    int to[MAXN * 4];
    bool type[MAXN * 4];
    int tot;
    void Add(int, int, bool);
};

/* Declaration */
int main();
void Dfs(int _x, int, bool);
long long qpow(int _a, int _b);

/* Variable */
bool pd_type;
long long twom[MAXN];
long long jc[MAXN];
int len;
bool pd;
Graph G;
int type1[MAXN];
int type2[MAXN];
int type3[MAXN]; //偶链类型0
int type4[MAXN]; //偶链类型1
bool vis[MAXN];

/* Definition */
void Graph::Add(int _x, int _y, bool flag)
{
    ++tot;
    nxt[tot] = head[_x];
    to[tot] = _y;
    type[tot] = flag;
    head[_x] = tot;
    return;
}
int main()
{
    freopen("mate.in", "r", stdin);
    freopen("mate.out", "w", stdout);
    int n, m1, m2;
    scanf("%d%d%d", &n, &m1, &m2);
    int x, y;
    twom[0] = 1;
    jc[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        twom[i] = twom[i - 1] << 1;
        twom[i] %= mod;
        jc[i] = jc[i - 1] * i;
        jc[i] %= mod;
    }
    for (int i = 1; i <= m1; ++i)
    {
        scanf("%d%d", &x, &y);
        G.Add(x, y, 0);
        G.Add(y, x, 0);
    }
    for (int i = 1; i <= m2; ++i)
    {
        scanf("%d%d", &x, &y);
        G.Add(x, y, 1);
        G.Add(y, x, 1);
    }
    long long ans = 1;
    for (int i = 1; i <= n; ++i)
    {
        if (!vis[i])
        {
            len = 0;
            pd = false;
            Dfs(i, 0, 0);
            if (pd)
            {
                ++type2[len];
            }
            else if (len & 1)
            {
                ++type1[len];
            }
            else if(pd_type)
            {
                ++type4[len]; 
            }
            else
            {
                ++type3[len];
            }
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        if (i & 1)
        {
            if (type1[i])
            {
                ans *= jc[type1[i]];
                ans %= mod;
            }
        }
        else
        {
            if (type3[i])
            {
                ans *= (jc[type3[i]] * twom[type3[i]]) % mod;
                ans %= mod;
            }
            if (type4[i])
            {
                ans *= (jc[type4[i]] * twom[type4[i]]) % mod;
                ans %= mod;
            }
            if (type2[i])
            {
                ans *= (jc[type2[i]] * qpow(i, type2[i])) % mod;
                ans %= mod;
            }
        }
    }
    printf("%lld", ans);
    return 0;
}
void Dfs(int _x, int from, bool from_type)
{
    if (vis[_x])
    {
        pd = true;
        return;
    }
    ++len;
    vis[_x] = true;
    bool pdd = false;
    for (int i = G.head[_x]; i; i = G.nxt[i])
    {
        if (G.to[i] == from)
            continue;
        Dfs(G.to[i], _x, G.type[i]);
        pdd = true;
    }
    if (!pdd && !(len & 1))
    {
        pd_type = from_type;
    }
}
long long qpow(int _a, int _b)
{
    if (_b == 1)
    {
        return _a;
    }
    long long ret = qpow(_a, _b / 2);
    if (_b & 1)
    {
        return (((ret * ret) % mod) * _a) % mod;
    }
    else
    {
        return (ret * ret) % mod;
    }
    return 1;
}
