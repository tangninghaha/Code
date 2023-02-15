#include <stdio.h>
const int MAXN = 1e5 + 5;
long long input_l[MAXN], input_r[MAXN];
long long px[MAXN * 2];
long long ynum[MAXN * 2];
long long min(long long a, long long b);
long long abs(long long x);
void swap(long long &a, long long &b);
void Qsort(int lb, int rb, long long a[], long long b[]);
int main()
{
    freopen("linear.in", "r", stdin);
    freopen("linear.out", "w", stdout);
    int n;
    scanf("%d", &n);
    bool pd = 0;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld%lld", &input_l[i], &input_r[i]);
        if (input_l[i] != input_r[i])
        {
            pd = true;
        }
    }
    if (!pd)
    {
        Qsort(1, n, input_l, input_r);
        if (n % 2)
        {
            printf("%lld %lld", input_l[n / 2 + 1], input_l[n / 2 + 1]);
        }
        else
        {
            printf("%lld %lld", input_l[n / 2], input_l[n / 2 + 1]);
        }
        return 0;
    }
    for (int i = 1; i <= n; ++i)
    {
        px[i] = input_l[i];
        px[i + n] = input_r[i];
        ynum[i] = input_l[i];
        ynum[i + n] = input_r[i];
    }
    Qsort(1, 2 * n, px, ynum);
    int last = -1, tot = 0;
    for (int i = 1; i <= 2 * n; ++i)
    {
        if (px[i] != last)
        {
            last = px[i];
            ++tot;
            ynum[tot] = ynum[i];
        }
    }
    long long sum = 0, ans = 10000000000000005;
    long long ans_l = 0, ans_r = 0;
    int lbound = 1, rbound = tot;
    while (lbound <= rbound)
    {
        int mid = (lbound + rbound) >> 1;
        sum = 0;
        for (int j = 1; j <= n; ++j)
        {
            if (input_l[j] <= ynum[mid] && ynum[mid] <= input_r[j])
                continue;
            sum += min(abs(ynum[mid] - input_l[j]), abs(ynum[mid] - input_r[j]));
        }
    }
    printf("%lld %lld", ans_l, ans_r);
    return 0;
}
long long min(long long a, long long b)
{
    return a < b ? a : b;
}
long long abs(long long x)
{
    return x > 0 ? x : -x;
}
void Qsort(int lb, int rb, long long a[], long long b[])
{
    int i = lb, j = rb;
    int mid = a[(lb + rb) >> 1];
    while (i <= j)
    {
        while (a[i] < mid)
            ++i;
        while (a[j] > mid)
            --j;
        if (i <= j)
        {
            swap(a[i], a[j]);
            swap(b[i], b[j]);
            ++i;
            --j;
        }
    }
    if (i < rb)
        Qsort(i, rb, a, b);
    if (lb < j)
        Qsort(lb, j, a, b);
    return;
}
void swap(long long &a, long long &b)
{
    long long t = a;
    a = b;
    b = t;
    return;
}
