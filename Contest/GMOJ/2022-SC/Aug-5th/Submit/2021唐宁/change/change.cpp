#include <stdio.h>

const long long INF = 1e17;
const int MAXN = 10005;

void FileIO();
int main();
long long Min(long long aa, long long bb);
long long Pow2(int x);
long long Sovle(int n, long long m);

long long f[2 * MAXN][2];
long long s_up[2 * MAXN], s_down[2 * MAXN];
int a[2 * MAXN];

void FileIO()
{
    freopen("change.in", "r", stdin);
    freopen("change.out", "w", stdout);
    return;
}
int main()
{
    FileIO();
    int n;
    long long m;
    scanf("%d%lld", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        a[i + n] = a[i];
    }
    a[2 * n + 1] = a[1];
    printf("%lld", Sovle(n, m));
    return 0;
}
long long Min(long long aa, long long bb)
{
    return aa < bb ? aa : bb;
}
long long Pow2(int x)
{
    return (long long)x * x;
}
long long Sovle(int n, long long m)
{
    for (int i = 2; i <= 2 * n + 1; ++i)
    {
        if (a[i] > a[i - 1])
        {
            s_up[i] = s_up[i - 1] + a[i] - a[i - 1];
            s_down[i] = s_down[i - 1] + Pow2(a[i] - a[i - 1]);
        }
        else
        {
            s_up[i] = s_up[i - 1] + Pow2(a[i - 1] - a[i]);
            s_down[i] = s_down[i - 1] + a[i - 1] - a[i];
        }
    }
    int ed;
    long long ret = INF;
    int minn1, minn2;
    for (int st = 1; st <= n; ++st)
    {
        f[st][0] = f[st][1] = 0;
        ed = st + n;
        minn1 = st;
        minn2 = st;
        for (int i = st + 1; i <= ed; ++i)
        {
            f[i][0] = f[i][1] = INF;
        }
        for (int i = st + 1; i <= ed; ++i)
        {
            f[i][0] = Min(f[i][0], Min(f[minn1][0] + s_up[i] - s_up[minn1],
                                f[minn2][1] + s_down[i] - s_down[minn2] + m));
            f[i][1] = Min(f[i][1], Min(f[minn1][0] + s_up[i] - s_up[minn1] + m,
                                    f[minn2][1] + s_down[i] - s_down[minn2]));
            if (f[i][0] - s_up[i] < f[minn1][0] - s_up[minn1])
                minn1 = i;
            if (f[i][1] - s_down[i] < f[minn2][1] - s_down[minn2])
                minn2 = i;
        }
        ret = Min(ret, Min(f[ed][0], f[ed][1]));
    }
    return ret;
}
