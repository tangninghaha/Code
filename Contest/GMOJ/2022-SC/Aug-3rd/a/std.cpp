#include <stdio.h>

const int MAXN = 2e6 + 5;
int s[MAXN * 2];
int f[MAXN * 2];

int Abs(int x);
void FileIO();
int main();
long long Min(long long a, long long b);
int Read();
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
    n = Read();
    for (int i = 1; i <= n; ++i)
    {
        s[i] = Read();
    }
    for (int i = 1; i <= n; ++i)
    {
        s[i + n] = s[i];
    }
    printf("%lld", Sovle(n));
    return 0;
}
long long Min(long long a, long long b)
{
    return a < b ? a : b;
}
int Read()
{
    int ret = 0;
    char cha = getchar();
    while (cha < '0' || cha > '9')
    {
        cha = getchar();
    }
    while (cha >= '0' && cha <= '9')
    {
        ret = ret * 10 + cha - '0';
        cha = getchar();
    }
    return ret;
}
long long Sovle(int n)
{
    for (int i = 1; i <= 2 * n; ++i)
    {
        if (s[i] < i)
        {
            ++f[i - s[i]];
        }
    }
    int x = 0, y = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (s[i] >= i)
        {
            ++x;
        }
        else
        {
            ++y;
        }
    }
    long long sum = 0;
    for (int i = 1; i<= n; ++i)
    {
        sum += Abs(s[i] - i);
    }
    long long ret = sum;
    int ed;
    for (int st = 2; st <= n; ++st)
    {
        ed = st + n - 1;
        --x;
        sum += x - y;
        sum -= s[st - 1] - 1;
        if (s[ed] != n)
        {
            ++y;
            sum += n - s[ed];
        }
        else
        {
            ++x;
        }
        x += f[st - 1];
        y -= f[st - 1];
        ret = Min(ret, sum);
    }
    return ret;
}
