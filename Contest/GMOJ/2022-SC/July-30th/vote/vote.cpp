#include <stdio.h>
const int MAXN = 2005;

void FileIO();
void GetF(int n);
void GetG(int n);
int main();
double Max(double a, double b);
void Qsort(int l, int r);
double Sovle(int n, int k);
void Swap(double &a, double &b);

double p[MAXN];
double f[MAXN][MAXN];
double g[MAXN][MAXN];

void FileIO()
{
    freopen("vote.in", "r", stdin);
    freopen("vote.out", "w", stdout);
    return;
}
void GetF(int n)
{
    f[0][0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            f[i][j] = f[i - 1][j] * (1 - p[i]);
            if (j)
            {
                f[i][j] += f[i - 1][j - 1] * p[i];
            }
        }
    }
    return;
}
void GetG(int n)
{
    g[n + 1][0] = 1;
    for (int i = n; i >= 1; --i)
    {
        for (int j = 0; j <= n - i + 1; ++j)
        {
            g[i][j] = g[i + 1][j] * (1 - p[i]);
            if (j)
            {
                g[i][j] += g[i + 1][j - 1] * p[i];
            }
        }
    }
    return;
}
int main()
{
    FileIO();
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lf", &p[i]);
    }
    printf("%lf", Sovle(n, k));
    return 0;
}
double Max(double a, double b)
{
    return a > b ? a : b;
}
void Qsort(int l, int r)
{
    int i = l, j = r;
    double mid = p[(l + r) >> 1];
    while (i <= j)
    {
        while (p[i] < mid)
            ++i;
        while (p[j] > mid)
            --j;
        if (i <= j)
        {
            Swap(p[i], p[j]);
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
double Sovle(int n, int k)
{
    Qsort(1, n);
    GetF(n);
    GetG(n);
    double ans = 0;
    int k_2 = k / 2;
    double sum;
    for (int i = 0; i <= k; ++i)
    {
        sum = 0;
        for (int j = 0; j <= k_2; ++j)
        {
            sum += f[i][j] * g[n - k + i + 1][k_2 - j];
        }
        ans = Max(ans, sum);
    }
    return ans;
}
void Swap(double &a, double &b)
{
    double tmp = a;
    a = b;
    b = tmp;
    return;
}
