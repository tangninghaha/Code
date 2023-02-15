#include <stdio.h>
/* 声明 */
const int MAXTWO = 1048576, MAXN = 21;
long long f[MAXTWO]; /* 0 偶数 1 奇数*/
int flow[MAXN];
int nxt_f[MAXTWO];
int two_pow[MAXN];
int vis[MAXTWO];
long long num[MAXTWO];
void InitF(int n);
void InitTwoPow();
void GetAns(int n, long long h);
struct Graph
{
    int degree[MAXN];
    int head[MAXN];
    int nxt[MAXN * MAXN * 2];
    int to[MAXN * MAXN * 2];
    int tot;
    void Add(int x, int y);
};
Graph G;
void GetAns(int n, int h);
int main()
{
    int n;
    long long h;
    scanf("%d%lld", &n, &h);
    int xx;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            scanf("%1d", &xx);
            if (xx)
                G.Add(i, j);
        }
    }
    InitTwoPow();
    InitF(n);
    GetAns(n, h);
    return 0;
}

/* 定义 */
void Graph::Add(int x, int y)
{
    ++tot;
    ++degree[x];
    to[tot] = y;
    nxt[tot] = head[x];
    head[x] = tot;
    return;
}
void InitF(int n)
{
//    f[0] = G.degree[1];
//    for (int i = G.head[1]; i; i = G.nxt[i])
//    {
//        flow[G.to[i]] = 1;
//    }
    int s = 0;
//    for (int i = 1; i <= n; ++i)
//    {
//        s += (flow[i] % 2) * two_pow[i - 1];
//    }
//    for (int i = 1; i <= n; ++i)
//    {
//        flow[i] = 0;
//    }
//    nxt_f[0] = s;
    for (int i = 0; i < two_pow[n]; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if ((i >> (j - 1)) & 1)
            {
//                f[i] += G.degree[j];
                int cnt = 0;
                for (int k = G.head[j]; k; k = G.nxt[k])
                {
                    ++cnt;
                    flow[G.to[k]] += 1;
                    f[i] += 1;
                }
            }
            else
            {
//                f[i] += G.degree[j] * 2;
                int cnt = 0;
                for (int k = G.head[j]; k; k = G.nxt[k])
                {
                    ++cnt;
                    flow[G.to[k]] += 2;
                    f[i] += 2;
                }
            }
        }
        s = 0;
        for (int j = 1; j <= n; ++j)
        {
            s += (flow[j] % 2) * two_pow[j - 1];
        }
        nxt_f[i] = s;
        for (int j = 1; j <= n; ++j)
        {
            flow[j] = 0;
        }
    }
    return;
}
void InitTwoPow()
{
    two_pow[0] = 1;
    for (int i = 1; i <= 20; ++i)
    {
        two_pow[i] = two_pow[i - 1] << 1;
    }
    return;
}
void GetAns(int n, long long h)
{
    int s = 0;
    long long ans = G.degree[1];
    num[1] = ans;
    for (int i = G.head[1]; i; i = G.nxt[i])
    {
        ++flow[G.to[i]];
    }
    for (int i = 1; i <= n; ++i)
    {
        s += (flow[i] % 2) * two_pow[i - 1];
    }
    bool pd = false;
    int st, ed, len;
    for (long long i = 2; i <= h; ++i)
    {
        if (vis[s])
        {
            st = vis[s];
            ed = i - 1;
            len = ed - st + 1;
            pd = true;
            break;
        }
        ans += f[s];
        num[i] = num[i - 1] + f[s];
        vis[s] = i;
        s = nxt_f[s];
//        printf("%lld %lld\n", i, ans);
    }
    if (pd)
    {
        ans = num[st - 1] + ((h - st + 1) / len) * (num[ed] - num[st - 1])
              + num[(h - st + 1) % len + st - 1] - num[st - 1];
        printf("%lld\n", ans);
    }
    else
    {
        printf("%lld\n", ans);
    }
    return;
}
