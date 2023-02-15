#include <stdio.h>
#include <math.h>
const int MAXN = 1505;
double degree[MAXN];
int number[MAXN];
int x[MAXN], y[MAXN];
double xexp = 0.00000000000001;
void Qsort(int l, int r);
template <typename T> void swap(T &a, T &b);
int cmp(double a, double b);
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d", &x[i], &y[i]);
    }
    double t = M_PI_2;
    int ans = 0;
    for (int k = 1; k <= n; ++k)
    {
        for (int i = 1; i <= n; ++i)
        {
            degree[i] = atan2(y[i] - y[k], x[i] - x[k]);
            while (cmp(degree[i], M_PI) >= 0)
            {
                degree[i] -= M_PI;
            }
            while (cmp(degree[i], 0) < 0)
            {
                degree[i] += M_PI;
            }
            number[i] = i;
        }
        Qsort(1, n);
        int i = 1, j = 2, yj = 2;
        while (i < n)
        {
//            j = i + 1;
            if (j > n)
                break;
            if (number[i] == k)
            {
                ++i;
                continue;
            }
            while (cmp(degree[j] - degree[i], t) < 0 && j < n)
            {
                ++j;
            }
            yj = j;
            while (cmp(degree[j] - degree[i], t) == 0 && j <= n)
            {
                if (number[j] == k)
                {
                    ++j;
                    continue;
                }
                ++ans;
                ++j;
            }
            ++i;
            j = yj;
        }
    }
    printf("%d", ans);
    return 0;
} 
template <typename T> void swap(T &a, T &b)
{
    T t = a;
    a = b;
    b = t;
    return;
}
int cmp(double a, double b)
{
    if (a > b)
    {
        if (a - b <= xexp)
        {
            return 0;
        }
        return 1;
    }
    if (a < b)
    {
        if (b - a <= xexp)
        {
            return 0;
        }
        return -1;
    }
    return 0;
}
void Qsort(int l, int r)
{
    int i = l, j = r;
    double mid = degree[(l + r) >> 1];
    while (i <= j)
    {
        while (cmp(degree[i], mid) < 0)
            ++i;
        while (cmp(degree[j], mid) > 0)
            --j;
        if (i <= j)
        {
            swap(degree[i], degree[j]);
            swap(number[i], number[j]);
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
