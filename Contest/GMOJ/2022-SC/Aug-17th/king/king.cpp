#include <cstdio>

/* Constant */
const int MAXN = 16;
const int MAXM = 65;
const int MAXS = 32769;
const int mod = 123456788;

/* Declaration */
int main();
void FileIO();

/* Class */
struct Link
{
    int head[2520];
    int nxt[45005];
    int to[45005];
    int tot;
    void Add(int u, int v);
};

/* Variable */
Link l;
int twom[MAXN];
int f[MAXN][MAXM][MAXS];
int num[MAXS];
int chos[2520];

/* Definition */
int main()
{
    FileIO();
    twom[0] = 1;
    for (int i = 1; i <= 15; ++i)
    {
        twom[i] = twom[i - 1] * 2;
    }
    int n, m;
    scanf("%d%d", &n, &m);
    int tot = 0;
    int s1, s2;
    bool pd;
    for (int s = 0; s < twom[n]; ++s)
    {
        pd = false;
        if (s & (s << 1))
            pd = true;
        if (s & (s >> 1))
            pd = true;
        if (pd)
            continue;
        for (int k = 0; k < n; ++k)
        {
            if ((s >> k) & 1)
            {
                ++num[s];
            }
        }
        f[1][num[s]][s] = 1;
        chos[++tot] = s;
    }
    for (int i = 1; i <= tot; ++i)
    {
        for (int j = i + 1; j <= tot; ++j)
        {
            if (chos[i] & chos[j])
                continue;
            if ((chos[i] >> 1) & chos[j])
                continue;
            if ((chos[i] << 1) & chos[j])
                continue;
            l.Add(i, j);
            l.Add(j, i);
        }
    }
    l.Add(1, 1);
    for (int i = 2; i <= n; ++i)
    {
        for (int s1_bh = 1; s1_bh <= tot; ++s1_bh)
        {
            s1 = chos[s1_bh];
            for (int j = num[s1]; j <= m; ++j)
            {
                for (int s2_bh = l.head[s1_bh]; s2_bh; s2_bh = l.nxt[s2_bh])
                {
                    s2 = chos[l.to[s2_bh]];
                    if (j + num[s2] > m)
                        continue;
                    if (s1 & s2)
                        continue;
                    if ((s1 >> 1) & s2)
                        continue;
                    if ((s1 << 1) & s2)
                        continue;
                    f[i][j + num[s2]][s2] += f[i - 1][j][s1];
                    f[i][j + num[s2]][s2] %= mod;
                }
            }
        }
    }
    long long ans = 0;
    for (int s = 1; s <= tot; ++s)
    {
        ans += f[n][m][chos[s]];
        ans %= mod;
    }
    printf("%lld", ans);
}
void FileIO()
{
    freopen("king.in", "r", stdin);
    freopen("king.out", "w", stdout);
    return;
}
void Link::Add(int u, int v)
{
    ++tot;
    nxt[tot] = head[u];
    to[tot] = v;
    head[u] = tot;
    return;
}
