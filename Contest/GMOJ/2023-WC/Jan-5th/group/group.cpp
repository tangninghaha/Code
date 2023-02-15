#include <cstdio>
#include <cstring>

//#define DEBUG

/* Constant */
const int MAXN = 5e3 + 5;
const int MAXK = 555;
const long long BASE = 1145141;
const long long mod = 1e9 + 7;
const long long INF = 2e9 + 5;

/* Graph */
struct Graph
{
    int head[MAXN * 2];
    int nxt[MAXN * 6];
    int to[MAXN * 6];
    int f[MAXN * 6];
    int bh[MAXN * 6];
    int tot;
    void Add(int, int, int, int);
    Graph();
};
Graph::Graph()
{
    tot = 1;
    return;
}
void Graph::Add(int _u, int _v, int _f, int _bh)
{
    #ifdef DEBUG
        printf("%d %d %d\n", _u + 1, _v + 1, _f);
    #endif
    ++tot;
    nxt[tot] = head[_u];
    to[tot] = _v;
    f[tot] = _f;
    bh[tot] = _bh;
    head[_u] = tot;
    return;
};

/* Declaration */
int main();

// Netword Flows
int GetMaxFlow(int, int);
int Dfs(int, int, int);
void Bfs(int, int);
void Upload(int);

// Sort
void Qsort(int, int, long long*, long long*);
void Qsort(int, int, int*);
void Swap(long long&, long long&);
void Swap(int&, int&);

/* Variable */
// Network Flows
int d[MAXN];
int cur[MAXN];
Graph G;
int point_num;
int queue[MAXN];

// string
char a[MAXN][MAXK];
int hash[MAXK];
long long hash_num[2][MAXN];
int bh[MAXN];
long long base_pow[MAXK];
int ans[MAXN];
int ans_num;
int len[MAXN];

// Tool
int Min(int, int);

/* Definition */
int main()
{
    freopen("group.in", "r", stdin);
    freopen("group.out", "w", stdout);
    base_pow[0] = 1;
    for (int i = 1; i <= 550; ++i)
    {
        base_pow[i] = base_pow[i - 1] * BASE;
        base_pow[i] %= mod;
    }
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", a[i]);

        len[i] = strlen(a[i]);
//        for (int j = 0; j < k; ++j)
//        {
//            printf("%c", a[i][j]);
//        }
//        printf(" ");
//        for (int j = len[i] - k - 1; j < len[i]; ++j)
//        {
//            printf("%c", a[i][j]);
//        }
//        printf("\n");

        bh[i] = i;
    }
//    printf("###\n");
    for (int i = 1; i <= n; ++i)
    {
        hash[0] = a[i][0];
        for (int j = 1; j < len[i]; ++j)
        {
            hash[j] = (hash[j - 1] * BASE) % mod + a[i][j];
            hash[j] %= mod;
        }
        hash_num[0][i] = hash[k - 1];
        hash_num[1][i] = hash[len[i] - 1] - (hash[len[i] - k] * base_pow[k]) % mod;
        hash_num[1][i] = (hash_num[1][i] % mod + mod) % mod;
    }
    Qsort(1, n, hash_num[0], hash_num[1]);
    int cnt = 0;
    long long last = mod;
    for (int i = 1; i <= n; ++i)
    {
        if (hash_num[0][i] != last)
        {
            last = hash_num[0][i];
            hash_num[0][i] = ++cnt;
        }
        else
        {
            hash_num[0][i] = cnt;
        }
    }
    Qsort(1, n, hash_num[1], hash_num[0]);
    last = mod;
    for (int i = 1; i <= n; ++i)
    {
        if (hash_num[1][i] != last)
        {
            last = hash_num[1][i];
            hash_num[1][i] = ++cnt;
        }
        else
        {
            hash_num[1][i] = cnt;
        }
    }

    for (int i = 1; i <= n; ++i)
    {
        G.Add(hash_num[0][i], hash_num[1][i], INF, bh[i]);
        G.Add(hash_num[1][i], hash_num[0][i], 0, bh[i]);
        if (hash_num[1][i] == hash_num[1][i - 1])
            continue;
        G.Add(hash_num[1][i], cnt + 1, 1, 0);
        G.Add(cnt + 1, hash_num[1][i], 0, 0);
    }
    Qsort(1, n, hash_num[0], hash_num[1]);
    for (int i = 1; i <= n; ++i)
    {
        if (hash_num[0][i] == hash_num[0][i - 1])
            continue;
        G.Add(0, hash_num[0][i], 1, 0);
        G.Add(hash_num[0][i], 0, 0, 0);
    }
    point_num = cnt + 1;
#ifndef DEBUG
    printf("%d\n", GetMaxFlow(0, point_num));
    int nxt;
    for (int i = G.head[0]; i; i = G.nxt[i])
    {
        if (!G.f[i])
        {
            nxt = G.to[i];
            ans_num = 0;
            for (int j = G.head[nxt]; j; j = G.nxt[j])
            {
                if (G.to[j] != 0)
                {
                    ++ans_num;
                    ans[ans_num] = G.bh[j];
                }
            }
            Qsort(1, ans_num, ans);
            printf("%d ", ans_num);
            for (int j = 1; j <= ans_num; ++j)
            {
                printf("%d ", ans[j]);
            }
            printf("\n");
        }
        else
        {
            nxt = G.to[i];
            ans_num = 0;
            for (int j = G.head[nxt]; j; j = G.nxt[j])
            {
                if (G.to[j] != 0)
                {
                    ++ans_num;
                    ans[ans_num] = G.bh[j];
                }
            }
            Qsort(1, ans_num, ans);
            printf("%d ", ans_num);
            for (int j = 1; j <= ans_num; ++j)
            {
                printf("%d ", ans[j]);
            }
            printf("\n");
        }
    }
#endif
}
void Qsort(int l, int r, int* a)
{
    int mid = a[(l + r) >> 1];
    int i = l, j = r;
    while (i <= j)
    {
        while (a[i] < mid)
            ++i;
        while (mid < a[j])
            --j;
        if (i <= j)
        {
            Swap(a[i], a[j]);
            ++i;
            --j;
        }
    }
    if (i < r)
        Qsort(i, r, a);
    if (l < j)
        Qsort(l, j, a);
    return;
}
void Qsort(int l, int r, long long* a, long long* b)
{
    long long mid = a[(l + r) >> 1];
    int i = l, j = r;
    while (i <= j)
    {
        while (a[i] < mid)
            ++i;
        while (mid < a[j])
            --j;
        if (i <= j)
        {
            Swap(a[i], a[j]);
            Swap(b[i], b[j]);
            Swap(bh[i], bh[j]);
            ++i;
            --j;
        }
    }
    if (i < r)
        Qsort(i, r, a, b);
    if (l < j)
        Qsort(l, j, a, b);
    return;
}
void Swap(long long& _a, long long& _b)
{
    long long t = _a;
    _a = _b;
    _b = t;
    return;
}
void Swap(int& _a, int& _b)
{
    int t = _a;
    _a = _b;
    _b = t;
    return;
}
int GetMaxFlow(int s, int t)
{
    Bfs(s, t);
    int max_flow = 0;
    while (d[s] < point_num + 1)
    {
        for (int i = 0; i <= point_num; ++i)
        {
            cur[i] = G.head[i];
        }
        max_flow += Dfs(s, t, INF);
    }
    return max_flow;
}
void Bfs(int s, int t)
{
    int head = 0, tail = 1;
    queue[1] = t;
    for (int i = 0; i <= point_num; ++i )
    {
        d[i] = point_num + 1;
    }
    d[t] = 0;
    int now;
    while (head < tail)
    {
        ++head;
        now = queue[head];
        for (int i = G.head[now]; i; i = G.nxt[i])
        {
            if (G.f[i])
                continue;
            if (d[G.to[i]] > d[now] + 1)
            {
                d[G.to[i]] = d[now] + 1;
                ++tail;
                queue[tail] = G.to[i];
            }
        }
    }
    return;
}
int Dfs(int now, int t, int flow)
{
    if (now == t)
    {
        return flow;
    }
    int f;
    int ret = 0;
    bool ok = false;
    for (int i = cur[now]; i; i = G.nxt[i])
    {
        if (G.f[i] > 0 && d[G.to[i]] == d[now] - 1)
        {
            ok = true;
            f = Dfs(G.to[i], t, Min(flow, G.f[i]));
            G.f[i] -= f;
            G.f[i ^ 1] += f;
            flow -= f;
            ret += f;
            cur[now] = i;
            if (!flow)
            {
//                Upload(now);
                return ret;
            }
        }
    }
    if (!ok) 
        Upload(now);
    return ret;
}
int Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}
void Upload(int now)
{
    int minn = point_num + 1;
    for (int i = G.head[now]; i; i = G.nxt[i])
    {
        if (G.f[i] > 0)
        {
            minn = Min(minn, d[G.to[i]] + 1);
        }
    }
    d[now] = minn;
    return;
}
