#include <cstdio>

/* Constant */
const int MAXN = 5e5 + 5;
const long long mod = 1e9 + 7;

/* Class */
struct Num
{
    int num;
    int bh;
    int last;
    int nxt;
};

/* Declaration */
int main();
void Qsort(int, int);
bool Cmp(const Num&, const Num&);
void Swap(Num&, Num&);

/* Variable */
Num a[MAXN];

/* Definition */
int main()
{
    // freopen("sum.in", "r", stdin);
    // freopen("sum.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i].num);
        a[i].bh = i;
    }
    Qsort(1, n);
    for (int i = 1; i <= n; ++i)
    {
        if (a[i].num == a[i + 1].num)
        {
            a[i].nxt = a[i + 1].bh;
        }
        else
        {
            a[i].nxt = n + 1;
        }
    }
    long long ans = 0;
    long long sum = 0;
    for (int i = 1; i <= n; ++i)
    {
        sum = (long long)((long long)a[i].nxt - a[i].bh) * a[i].bh;
        sum %= mod;
        sum *= a[i].num;
        sum %= mod;
        ans += sum;
        ans %= mod;
    }
    printf("%lld", ans);
    return 0;
}
void Qsort(int l, int r)
{
    int i = l, j = r;
    const Num mid = a[l + r >> 1];
    while (i <= j)
    {
        while (Cmp(a[i], mid))
            ++i;
        while (Cmp(mid, a[j]))
            --j;
        if (i <= j)
        {
            Swap(a[i], a[j]);
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
bool Cmp(const Num& _a, const Num& _b)
{
    if (_a.num == _b.num)
    {
        return _a.bh < _b.bh;
    }
    return _a.num < _b.num;
}
void Swap(Num& _a, Num& _b)
{
    Num tmp = _a;
    _a = _b;
    _b = tmp;
    return;
}
