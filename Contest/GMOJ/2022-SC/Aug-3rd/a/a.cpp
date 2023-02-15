#include <stdio.h>

const int MAXN = 2e6 + 5;
int s[MAXN];

int Abs(int x);
void FileIO();
int main();
long long Min(long long a, long long b);
long long Sovle(int n);

int Abs(int x)
{
    return x > 0 ? x : -x;
}
void FileIO()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    return;
}
int main()
{
    FileIO();
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &s[i]);
    }
    printf("%lld", Sovle(n));
    return 0;
}
long long Min(long long a, long long b)
{
    return a < b ? a : b;
}
long long Sovle(int n)
{
    long long ret = 1e17;
    long long sum;
    int x;
    for (int i = 1; i <= n; ++i)
    {
        sum = 0;
        x = i - s[i];
        while (x < 0)
        {
            x += n;
        }
        for (int j = 1; j <= n; ++j)
        {
            sum += Abs((s[j] - (((j - x - 1) % n + n) % n + 1)));
        }
        ret = Min(ret, sum);
    }
    return ret;
}
