#include <cstdio>

/* Constant */
const int MAXN = 1e5 + 5;

/* Class */
struct Data
{
    long long l_max;
    long long r_max;
    long long mid_max;
    long long value;
    Data(long long, long long, long long, long long);
};

/* Declaration */
Data operator+(Data, Data);
int main();
Data Solution(int, int);
long long Max(long long, long long);

/* Variable */
long long a[2 * MAXN];

/* Definition */
Data::Data(long long _l_max, long long _r_max, long long _mid_max, long long _value)
{
    l_max = _l_max;
    r_max = _r_max;
    mid_max = _mid_max;
    value = _value;
    return;
}
Data Solution(int l, int r)
{
    if (l > r)
    {
        return Data(0, 0, 0, 0);
    }
    if (l == r)
    {
        return Data(Max(0, a[l]), Max(0, a[l]), Max(0, a[l]), a[l]);
    }
    int mid = (l + r) >> 1;
    return Solution(l, mid) + Solution(mid + 1, r);
}
Data operator+(Data _a, Data _b)
{
    return Data(Max(_a.value + _b.l_max, _a.l_max),
             Max(_b.r_max, _b.value + _a.r_max),
             _a.r_max + _b.l_max,
             _a.value + _b.value);
}
int main()
{
    freopen("in.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    bool negative = true;
    long long big_num = -1e17;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", &a[i]);
        a[i + n] = a[i];
        if (a[i] > 0)
        {
            negative = false;
        }
        if (a[i] > big_num)
        {
            big_num = a[i];
        }
    }
    if (negative)
    {
        printf("%lld", big_num);
        return 0;
    }
    Data ret = Solution(1, 2 * n);
    long long ans = Max(Max(ret.l_max, ret.r_max), ret.mid_max);
    printf("%lld", ans);
}
long long Max(long long _a, long long _b)
{
    return _a > _b ? _a : _b;
}
