#include <stdio.h>
/* 全局变量 */
const long long mod = 998244353;
const int MAXN = 1e7 + 1;
int b[MAXN], c[MAXN];
long long f[MAXN];
int inverse[MAXN];

/* 声明 */
void FileIO();
void InitBC(int n, int bx, int by, int cx, int cy, int p);
void InitInverse();
void GetF(int n, int a);
int min(int a, int b);

int main();

/* 定义 */
int main()
{
    FileIO();
    InitInverse();
    int n, a, bx, by, cx, cy, p;
    scanf("%d%d%d%d%d%d%d", &n, &a, &bx, &by, &cx, &cy, &p);
    InitBC(n, bx, by, cx, cy, p);
    f[0] = a;
    GetF(n, a);
    printf("%lld", f[n]);
    return 0;
}
void GetF(int n, int a)
{
    int k;
    k = min(c[0], b[0]);
    f[1] = (((((long long) c[0] * inverse[k]) % mod) * a) % mod + a) % mod;
    for (int i = 2; i <= n; ++i)
    {
        k = min(c[i - 1], b[i - 2]);
        f[i] = (((((long long) f[i - 1] * c[i - 1]) % mod) * inverse[k] % mod + f[i - 2])) % mod;
    }
    return;
}
void FileIO()
{
    freopen("forging.in", "r", stdin);
    freopen("forging.out", "w", stdout);
    return;
}
void InitBC(int n, int bx, int by, int cx, int cy, int p)
{
    b[0] = by + 1;
    c[0] = cy + 1;
    for (int i = 1; i < n; ++i)
    {
        b[i] = ((long long) b[i - 1] * bx + by) % p + 1;
        c[i] = ((long long) c[i - 1] * cx + cy) % p + 1;
    }
    return;
}
void InitInverse()
{
    inverse[1] = 1;
    for (int i = 2; i < MAXN; ++i)
    {
        inverse[i] = ((long long) (mod - mod / i) * inverse[mod % i]) % mod;
    }
    return;
}
int min(int a, int b)
{
    return a < b ? a : b;
}
