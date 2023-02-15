#include <stdio.h>
#define int long long
const int MAXN = 1e5 + 5;

int Abs(int x);
void FileIO();
signed main();
int Max(int a, int b);
int Min(int a, int b);
int Sovle(int n);

int num[MAXN];

int Abs(int x)
{
    return x < 0 ? -x : x;
}
void FileIO()
{
    freopen("lvxing.in", "r", stdin);
    freopen("lvxing.out", "w", stdout);
    return;
}
signed main()
{
    FileIO();
    int n;
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", &num[i]);
    }
    printf("%lld", Sovle(n));
    return 0;
}
int Max(int a, int b)
{
    return a > b ? a : b;
}
int Min(int a, int b)
{
    return a < b ? a : b;
}
int Sovle(int n)
{
    int ret = 0;
    int tmp;
    for (int i = 2; i < n; ++i)
    {
        if (num[i] > num[i + 1] && num[i] > num[i - 1])
        {
            tmp = Max(num[i + 1], num[i - 1]);
            ret += num[i] - tmp;
            num[i] = tmp;
        }
        if (num[i] < num[i + 1] && num[i] < num[i - 1])
        {
            tmp = Min(num[i + 1], num[i - 1]);
            ret += tmp - num[i];
            num[i] = tmp;
        }
    }
    for (int i = 1; i < n; ++i)
    {
        ret += Abs(num[i] - num[i + 1]);
    }
    return ret;
}

