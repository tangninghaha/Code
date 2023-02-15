#include <cstdio>

#include <algorithm>

using std::pair;
using std::make_pair;

/* Constant */
const int MAXN = 1e5 + 5;
const int MAXM = 2e5 + 5;
const int MAXK = 25;
const int MAXK2 = 1048576;
const long long INF = 1e18 + 5;
const long long mod = 998244353;

/* Class */
class Graph
{
    public:
        int head[MAXN];
        int nxt[MAXM * 2];
        int to[MAXM * 2];
        int dis[MAXM * 2];
        int tot;
        void Add(int, int, int);
};
class Heap
{
    private:
        pair<long long, int> t[MAXN];
        int size;
    public:
        pair<long long, int> Front();
        void Up(int);
        void Down(int);
        void Pop();
        void clear();
        void Insert(pair<long long, int>);
        void Build(int, int);
        void Change(int, long long);
};

/* Declaration */
long long qpow(long long, int);
int main();
void Dij(int, int);
template <typename T> void Swap(T&, T&);
long long Max(long long, long long);
long long Min(long long, long long);
void FileIO();

/* Variable */
Heap queue;
Graph g;
long long dist[MAXN][MAXK];
int a[MAXN];
int fire[MAXK];
long long max_time;
int rk[MAXN];
int twom[21];
bool pd[MAXK2];

/* Definition */
int main()
{
    FileIO();
    twom[0] = 1;
    for (int i = 1; i <= 20; ++i)
    {
        twom[i] = twom[i - 1] * 2;
    }
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= k; ++i)
    {
        scanf("%d", &fire[i]);
    }
    int u, v, w;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d%d", &u, &v, &w);
        g.Add(u, v, w);
        g.Add(v, u, w);
    }
    Dij(n, k);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= k; ++j)
        {
            if (dist[i][j] > max_time)
            {
                a[i] += twom[j - 1];
            }
        }
        pd[a[i]] = true;
    }
    int cnt = 0;
//    for (int i = 0; i < twom[k]; ++i)
//    {
//        bool pdd = false;
//        for (int j = 1; j <= n; ++j)
//        {
//            if ((i & a[j]) == 0)
//            {
//                pdd = true;
//                break;
//            }
//        }
//        if (!pdd)
//        {
//            ++cnt;
//        }
//    }
    for (int i = twom[k] - 1; i >= 0; --i)
    {
        for (int j = 0; j < k; ++j)
        {
            if (!((i >> j) & 1))
            {
                if (pd[i + twom[j]])
                {
                    pd[i] = true;
                    break;
                }
            }
        }
    }
    for (int i = 1; i < twom[k]; ++i)
    {
        if (!pd[i])
            ++cnt;
    }
    long long ans = cnt;
    ans *= qpow(twom[k], mod - 2);
    ans %= mod;
    printf("%lld", ans);
    return 0;
}
long long qpow(long long a_, int b_)
{
    if (!b_)
        return 1;
    if (b_ == 1)
        return a_;
    long long ret = qpow(a_, b_ / 2);
    if (b_ & 1)
    {
        return (((ret * ret) % mod) * a_) % mod;
    }
    else
    {
        return (ret * ret) % mod;
    }
    return 1;
}
void Swap(int& a_, int& b_)
{
    int tmp = a_;
    a_ = b_;
    b_ = tmp;
    return;
}
void Dij(int n, int k)
{
    int now;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= k; ++j)
        {
            dist[i][j] = INF;
        }
    }
    for (int i = 1; i <= k; ++i)
    {
        queue.clear();
//        queue.Insert(make_pair(0, fire[i]));
        queue.Build(n, fire[i]);
        dist[fire[i]][i] = 0;
        for (int j = 1; j <= n; ++j)
        {
            now = queue.Front().second;
            queue.Pop();
            for (int x = g.head[now]; x; x = g.nxt[x])
            {
                if (dist[now][i] + g.dis[x] < dist[g.to[x]][i])
                {
                    dist[g.to[x]][i] = dist[now][i] + g.dis[x];
                    queue.Change(rk[g.to[x]], dist[g.to[x]][i]);
                }
            }
        }
    }
    long long sum;
    for (int i = 1; i <= n; ++i)
    {
        sum = INF;
        for (int j = 1; j <= k; ++j)
        {
            sum = Min(sum, dist[i][j]);
        }
        max_time = Max(sum, max_time);
    }
    return;
}
void Heap::Change(int rk_, long long x_)
{
    t[rk_].first = x_;
    Up(rk_);
}
long long Min(long long a_, long long b_)
{
    return a_ < b_ ? a_ : b_;
}
long long Max(long long a_, long long b_)
{
    return a_ > b_ ? a_ : b_;
}
void Heap::Build(int n, int st)
{
    Insert(make_pair(0, st));
    rk[st] = 1;
    for (int i = 1; i <= n; ++i)
    {
        if (i != st)
        {
            Insert(make_pair(INF, i));
        }
    }
}
pair<long long, int> Heap::Front()
{
    return t[1];
}
void Heap::clear()
{
    size = 0;
}
void Heap::Up(int x_)
{
    int nxt = x_ / 2;
    while (nxt && t[nxt] > t[x_])
    {
        Swap(rk[t[nxt].second], rk[t[x_].second]);
        Swap(t[nxt], t[x_]);
        x_ = nxt;
        nxt = x_ / 2;
    }
    return;
}
void Heap::Down(int x_)
{
    int nxt = x_ * 2;
    while ((nxt <= size && t[nxt] < t[x_]) || (nxt + 1 <= size && t[nxt + 1] < t[x_]))
    {
        if (t[nxt + 1] < t[nxt] && nxt + 1 <= size)
            ++nxt;
        Swap(rk[t[nxt].second], rk[t[x_].second]);
        Swap(t[nxt], t[x_]);
        x_ = nxt;
        nxt = x_ * 2;
    }
    return;
}
void Heap::Pop()
{
    Swap(rk[t[size].second], rk[t[1].second]);
    Swap(t[1], t[size]);
    --size;
    Down(1);
    return;
}
void Heap::Insert(pair<long long, int> x_)
{
    ++size;
    rk[x_.second] = size;
    t[size] = x_;
    Up(size);
    return;
}
void Graph::Add(int u, int v, int w)
{
    ++tot;
    nxt[tot] = head[u];
    to[tot] = v;
    dis[tot] = w;
    head[u] = tot;
    return;
}
template <typename T> void Swap(T& a_, T& b_)
{
    T tmp = a_;
    a_ = b_;
    b_ = tmp;
}
void FileIO()
{
    freopen("flame.in", "r", stdin);
    freopen("flame.out", "w", stdout);
    return;
}
