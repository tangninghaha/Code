#include <cstdio>

/* Constant */
const int MAXN = 105;
const int MAXM = 5005;
const int INF = 1e8 + 5;

/* Declaration */
int main();
void Qsort(int, int);
template <typename T> void Swap(T& _a, T& _b);
bool Check(int, int, int, int);
int Gf(int);
long long Min(long long, long long);

/* Variable */
int from[MAXM];
int to[MAXM];
long long dist[MAXM];

int fa[MAXN];
int sz[MAXN];

/* Definition */
int main()
{
    // freopen("in.txt", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);
    int _x, _y;
    long long _z;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d%lld", &_x, &_y, &_z);
        from[i] = _x;
        to[i] = _y;
        dist[i] = _z;
    }
    Qsort(1, m);
    int lbound, rbound, mid, r;
    long long ans = INF;
    for (int st = 1; st <= m - n + 2; ++st)
    {
        lbound = n - 1;
        rbound = m - st + 1;
        r = -1;
        while (lbound < rbound)
        {
            mid = (lbound + rbound) >> 1;
            if (Check(st, st + mid - 1, n, m))
            {
                rbound = mid;
                r = st + mid - 1;
            }
            else
            {
                lbound = mid + 1;
            }
        }
        if (r != -1)
        {
            ans = Min(ans, dist[r] - dist[st]);
        }
    }
    printf("%lld", ans);
    return 0;
}
bool Check(int st, int ed, int n, int m)
{
    for (int i = 1; i <= n; ++i)
    {
        fa[i] = i;
        sz[i] = 1;
    }
    int fa_a, fa_b;
    for (int i = st; i <= ed; ++i)
    {
        if (Gf(from[i]) != Gf(to[i]))
        {
            fa_a = Gf(from[i]);
            fa_b = Gf(to[i]);
            fa[fa_a] = fa_b;
            sz[fa_b] += sz[fa_a];
        }
    }
    if (sz[Gf(1)] == n)
    {
        return true;
    }
    return false;
}
int Gf(int x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = Gf(fa[x]);
}
void Qsort(int l, int r)
{
    const long long mid = dist[(l + r) >> 1];
    int i = l, j = r;
    while (i <= j)
    {
        while (dist[i] < mid)
            ++i;
        while (mid < dist[j])
            --j;
        if (i <= j)
        {
            Swap(dist[i], dist[j]);
            Swap(from[i], from[j]);
            Swap(to[i], to[j]);
            ++i;
            --j;
        }
    }
    if (i < r)
        Qsort(i, r);
    if (l < j)
        Qsort(l, j);
    return;
}
template <typename T> void Swap(T& _a, T& _b)
{
    T tmp = _a;
    _a = _b;
    _b = tmp;
    return;
}
long long Min(long long _a, long long _b)
{
    return _a < _b ? _a : _b;
}
