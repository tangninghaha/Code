#include <stdio.h>

const long long INF = 1e18;
const int MAXN = 2e5 + 5;
long long a[MAXN];
long long g[MAXN];
int s[MAXN];
long long mx_g[MAXN];
long long A, B, C, D;

long long f(int x);
void FileIO();
int main();
long long Max(long long a, long long b);
long long Sovle(int n);

long long f(int x)
{
    return (long long) A * x * x * x + B * x * x + C * x + D;
}
void FileIO()
{
    freopen("min.in", "r", stdin);
    freopen("min.out", "w", stdout);
    return;
}
int main()
{
    FileIO();
    int n;
    scanf("%d", &n);
    scanf("%lld%lld%lld%lld", &A, &B, &C, &D);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", &a[i]);
    }
    printf("%lld", Sovle(n));
    return 0;
}
long long Max(long long aa, long long bb)
{
    return aa > bb ? aa : bb;
}
long long Sovle(int n)
{
    for (int i = 1; i <= n; ++i)
    {
        g[i] = mx_g[i] = -INF;
    }
    int top = 0;
    s[++top] = 1;
    g[1] = f(a[1]);
    mx_g[1] = g[1];
    for (int i = 2; i <= n; ++i)
    {
        while (a[s[top]] >= a[i] && top >= 1)
        {
            mx_g[i] = Max(mx_g[i], g[s[top]]);
            mx_g[i] = Max(mx_g[i], mx_g[s[top]]);
            --top;
        }
        g[i] = Max(mx_g[i] + f(a[i]), g[s[top]] + f(a[i]));
        if (s[top])
        {
            g[i] = Max(g[i], g[s[top]]);
        }
        s[++top] = i;
    }
    return g[n];
}
