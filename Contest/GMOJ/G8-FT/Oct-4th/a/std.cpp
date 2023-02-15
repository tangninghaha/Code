#include <cstdio>

/* Constant */
const int MAXN = 1e5 + 5;
const int mod = 1e9 + 7;
const int MAXM = 5005;

/* Declaration */
int main();
void Init(int);
void Qsort(int, int);
void Swap(int&, int&);
bool Cmp(int, int);

/* Variable */
long long inv[3 * MAXN];
long long jc[3 * MAXN];
long long invc[3 * MAXN];
int x[MAXM];
int y[MAXM];
int z[MAXM];
long long f[MAXM];

/* Definition */
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    Init(3 * n);
    long long sum;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d%d", &x[i], &y[i], &z[i]);
    }
    Qsort(1, m);
    ++m;
    x[m] = y[m] = z[m] = n;
    for (int i = 1; i <= m; ++i)
    {
        sum = jc[x[i] + y[i] + z[i]] * invc[x[i]];
        sum %= mod;
        sum *= invc[y[i]];
        sum %= mod;
        sum *= invc[z[i]];
        sum %= mod;
        f[i] = sum;
        for (int j = 1; j < i; ++j)
        {
            if (x[j] <= x[i] && y[j] <= y[i] && z[j] <= z[i])
            {
                sum = f[j] * jc[x[i] - x[j] + y[i] - y[j] + z[i] - z[j]];
                sum %= mod;
                sum *= invc[x[i] - x[j]];
                sum %= mod;
                sum *= invc[y[i] - y[j]];
                sum %= mod;
                sum *= invc[z[i] - z[j]];
                sum %= mod;
                f[i] -= sum;
                f[i] = (f[i] % mod + mod) % mod;
            }
        }
    }
    printf("%lld", f[m]);
    return 0;
}
void Init(int n)
{
    inv[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        inv[i] = (mod - mod / i) % mod * (inv[mod % i]) % mod;
    }
    jc[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        jc[i] = jc[i - 1] * i;
        jc[i] %= mod;
    }
    invc[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        invc[i] = inv[i] * invc[i - 1];
        invc[i] %= mod;
    }
    return;
}
void Qsort(int l, int r)
{
    int mid = (l + r) >> 1, i = l, j = r;
    while (i <= j)
    {
        while (Cmp(i, mid))
            ++i;
        while (Cmp(mid, j))
            --j;
        if (i <= j)
        {
            if (mid == i)
                mid = j;
            else if (mid == j)
                mid = i;
            Swap(x[i], x[j]);
            Swap(y[i], y[j]);
            Swap(z[i], z[j]);
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
bool Cmp(int _a, int _b)
{
    if (x[_a] == x[_b])
    {
        if (y[_a] == y[_b])
        {
            if (z[_a] == z[_b])
            {
                return false;
            }
            return z[_a] < z[_b];
        }
        return y[_a] < y[_b];
    }
    return x[_a] < x[_b];
}
void Swap(int& _, int& __)
{
    int ___ = _;
    _ = __;
    __ = ___;
    return;
}
