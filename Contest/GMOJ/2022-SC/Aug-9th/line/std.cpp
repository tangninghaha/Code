#include <cstdio>
#include <cmath>

/* declaration */

const int MAXN = 5e4 + 5;
const int MAXP = 1e9 + 1;
const long double EXP = 1e-10;

void FileIO();
int main();
long double cot(long double x);
void Qsort(int l, int r);
void Swap(long double& a, long double& b);
void Swap(long long& a, long long& b);
long long Sovle(int l, int r);
long long Min(long long a, long long b);

class Point
{
    public:
        long long x;
        long long y;
};
Point p[MAXN];
long double x_new[MAXN];
long long y_new[MAXN];
long long y_tmp[MAXN];

namespace Tree
{
    long long cf[MAXN];
    long long c[MAXN];
}


/* definition */
long long Min(long long a, long long b)
{
    return a < b ? a : b;
}

void FileIO()
{
    freopen("line.in", "r", stdin);
    freopen("line.out", "w", stdout);
    return;
}
int main()
{
    FileIO();
    int n;
    scanf("%d", &n);
    long long min_x = MAXP, min_y = MAXP;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld%lld", &p[i].x, &p[i].y);
        min_x = Min(min_x, p[i].x);
        min_y = Min(min_y, p[i].y);
    }
    for (int i = 1; i <= n; ++i)
    {
        p[i].x += min_x;
        p[i].y += min_y;
    }
    long double lbound = 0, rbound = M_PI;
    long double mid;
    long long ans;
    long long xx;
    long long xxx = (long long)n * (n - 1) / 2;
    if (xxx & 1)
    {
        xx = (xxx + 1) / 2;
    }
    else
    {
        xx = xxx / 2;
    }
    long double mid1, mid2;
    while (rbound - lbound > EXP)
    {
        mid = (lbound + rbound) / 2.0;
        for (int i = 1; i <= n; ++i)
        {
            if (mid >= M_PI_2)
            {
                x_new[i] = p[i].x + cot(M_PI - mid) * p[i].y;
            }
            else
            {
                x_new[i] = p[i].x - cot(mid) * p[i].y;
            }
            y_new[i] = p[i].y;
        }
        Qsort(1, n);
        ans = Sovle(1, n);
        ans = xxx - ans;
        if (ans == xx)
        {
            mid1 = mid;
            lbound = mid;
        }
        if (ans < xx)
        {
            rbound = mid;
        }
        else if(ans > xx)
        {
            lbound = mid;
        }
    }
    if (xxx & 1)
    {
        printf("%.15Lf", mid);
        return 0;
    }
    lbound = 0, rbound = M_PI;
    xx = xxx / 2 + 1;
    while (rbound - lbound > EXP)
    {
        mid = (lbound + rbound) / 2.0;
        for (int i = 1; i <= n; ++i)
        {
            if (mid >= M_PI_2)
            {
                x_new[i] = p[i].x + cot(M_PI - mid) * p[i].y;
            }
            else
            {
                x_new[i] = p[i].x - cot(mid) * p[i].y;
            }
            y_new[i] = p[i].y;
        }
        Qsort(1, n);
        ans = Sovle(1, n);
        ans = xxx - ans;
        if (ans == xx)
        {
            mid2 = mid;
            lbound = mid;
        }
        if (ans < xx)
        {
            rbound = mid;
        }
        else if(ans > xx)
        {
            lbound = mid;
        }
    }
    printf("%.15Lf", (mid1 + mid2) / 2.0);
    return 0;
}
void Qsort(int l, int r)
{
    int i = l, j = r;
    long double mid = x_new[(l + r) >> 1];
    while (i <= j)
    {
        while (x_new[i] < mid)
            ++i;
        while (x_new[j] > mid)
            --j;
        if (i <= j)
        {
            Swap(x_new[i], x_new[j]);
            Swap(y_new[i], y_new[j]);
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
long long Sovle(int l, int r)
{
    if (l == r)
        return 0;
    int mid = (l + r) >> 1;
    long long ret = 0;
    ret += Sovle(l, mid);
    ret += Sovle(mid + 1, r);
    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r)
    {
        if (y_new[i] > y_new[j])
        {
            y_tmp[k] = y_new[i];
            ++i;
            ++k;
        }
        else
        {
            ret += mid - i + 1;
            y_tmp[k] = y_new[j];
            ++j;
            ++k;
        }
    }
    while (i <= mid)
    {
        y_tmp[k] = y_new[i];
        ++i;
        ++k;
    }
    while (j <= r)
    {
        y_tmp[k] = y_new[j];
        ++j;
        ++k;
    }
    for (int ii = l; ii <= r; ++ii)
    {
        y_new[ii] = y_tmp[ii];
    }
    return ret;
}
long double cot(long double x)
{
    return 1.0 / (tan(x));
}
void Swap(long double& a, long double &b)
{
    long double tmp = a;
    a = b;
    b = tmp;
    return;
}
void Swap(long long& a, long long& b)
{
    long long tmp = a;
    a = b;
    b = tmp;
    return;
}
