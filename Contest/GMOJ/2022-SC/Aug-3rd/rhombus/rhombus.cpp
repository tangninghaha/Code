#include <stdio.h>
const int MAXN = 3005;
struct Data_Maker
{
    long long Seed, a, b, c, MOD;
    long long Random();
    int Random_int();
    void MAKE(int n, int m);
};
Data_Maker DM;

int Abs(int x);
void FileIO();
void InitS(int n, int m);
int main();
int Min(int a, int b);
long long Max(long long a, long long b);
long long Sovle(int n, int m, int h);

int A[MAXN][MAXN];
long long s1[MAXN][MAXN], s2[MAXN][MAXN];
long long ans[MAXN];

long long Data_Maker::Random()
{
    c++;
    Seed = (Seed * a + b * c) % MOD;
    return Seed;
}
int Data_Maker::Random_int()
{
    int tmp = Random();
    if (Random() & 1)
        tmp *= -1;
    return tmp;
}
void Data_Maker::MAKE(int n, int m)
{
    scanf("%lld%lld%lld%lld%lld", &Seed, &a, &b, &c, &MOD);
    for(int i = 1; i <= n; i++)
        for(int j = 1;j <= m; j++)
            A[i][j] = Random_int();
    return;
}

int Abs(int x)
{
    return x > 0 ? x : -x;
}
void FileIO()
{
    freopen("rhombus.in", "r", stdin);
    freopen("rhombus.out", "w", stdout);
    return;
}
void InitS(int n, int m)
{
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            s1[i][j] = s1[i - 1][j + 1] + A[i][j];
            s2[i][j] = s2[i - 1][j - 1] + A[i][j];
        }
    }
    return;
}
int main()
{
    FileIO();
    int n, m, h;
    scanf("%d%d%d",&n, &m, &h);
    int ty;
    scanf("%d", &ty);
    if (!ty)
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                scanf("%d", &A[i][j]);
            }
        }
    }
    else
    {
        DM.MAKE(n, m);
    }
    printf("%lld", Sovle(n, m, h));
    return 0;
}
int Min(int a, int b)
{
    return a < b ? a : b;
}
long long Max(long long a, long long b)
{
    return a > b ? a : b;
}
long long Sovle(int n, int m, int h)
{
    InitS(n, m);
    long long sum = 0;
    long long ret = -1e17;
    int ed1 = 2 * h - 1;
    int ed2 = 2 * h - 1;
    for (int i = 1; i <= ed1; ++i)
    {
        for (int j = 1; j <= ed2; ++j)
        {
            if (Abs(i - h) + Abs(j - h) < h)
            {
                sum += A[i][j];
            }
        }
    }
    ans[h] = sum;
    for (int i = h; i <= n - h + 1; ++i)
    {
        for (int j = h; j <= m - h + 1; ++j)
        {
            if (j != h)
            {
                sum -= s1[i][j - h] - s1[i - h][j];
                sum -= s2[i + h - 1][j - 1] - s2[i][j - h];
                sum += s2[i][j + h - 1] - s2[i - h][j - 1];
                sum += s1[i + h - 1][j] - s1[i][j + h - 1];
            }
            else if (i != h)
            {
                sum = ans[i - 1];
                sum -= s1[i - 1][1] - s1[i - h - 1][j + 1];
                sum -= s2[i - 1][j + h - 1] - s2[i - h][j];
                sum += s2[i + h - 1][j] - s2[i - 1][j - h];
                sum += s1[i + h - 2][j + 1] - s1[i - 1][j + h];
                ans[i] = sum;
            }
            ret = Max(ret, sum);
        }
    }
    return ret;
}
