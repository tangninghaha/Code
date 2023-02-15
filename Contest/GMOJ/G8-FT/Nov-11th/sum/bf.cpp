#include <cstdio>

/* Constant */
const int MAXN = 5e5 + 5;
const long long mod = 1e9 + 7;

/* Declaration */
int main();
void Qsort(int, int);
void Swap(int&, int&);

/* Variable */
int a[MAXN];
int tmp[MAXN];

/* Definition */
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
    }
    long long ans = 0;
    for (int l = 1; l <= n; ++l)
    {
        for (int r = l; r <= n; ++r)
        {
            for (int k = l; k <= r; ++k)
            {
                tmp[k] = a[k];
            }
            Qsort(l, r);
            int last = 0;
            for (int k = l; k <= r; ++k)
            {
                if (tmp[k] != last)
                {
                    ans += tmp[k];
                    ans %= mod;
                    last = tmp[k];
                }
            }
        }
    }
    printf("%lld", ans);
    return 0;
}
void Qsort(int l, int r)
{
    int i = l, j = r;
    int mid = tmp[(l + r) >> 1];
    while (i <= j)
    {
        while (tmp[i] < mid)
            ++i;
        while (tmp[j] > mid)
            --j;
        if (i <= j)
        {
            Swap(tmp[i], tmp[j]);
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
void Swap(int& _a, int& _b)
{
    int mid = _a;
    _a = _b;
    _b = mid;
    return;
}
