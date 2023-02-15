#include <cstdio>
#include <cstring>
const long long mod = 998244353, MOD = 998244352;

/* declaration */
long long b[201];
long long f[201];
long long tmp[201][201];

class Matrix
{
    private:
        int N;
        int M;
        long long a[201][201];
    public:
        Matrix();
        void Init(long long _a[201][201], int n, int m);
        long long GetNum(int x, int y);
    friend Matrix operator*(const Matrix& A, const Matrix& b);
    friend Matrix operator^(const Matrix& A, long long x);
};
Matrix X;

int main();

/* definition */
long long Matrix::GetNum(int x, int y)
{
    return a[x][y];
}
Matrix::Matrix()
{
    memset(a, 0, sizeof(a));
    N = 0;
    M = 0;
    return;
}
Matrix operator^(const Matrix& A, long long x)
{
    Matrix res, bas;
    for (int i = 1; i <= A.M; ++i)
    {
        res.a[i][i] = 1;
    }
    res.N = A.M;
    res.M = A.M;
    bas = A;
    while (x)
    {
        if (x & 1)
            res = res * bas;
        bas = bas * bas;
        x >>= 1;
    }
    return res;
}
Matrix operator*(const Matrix& A, const Matrix &B)
{
    Matrix res;
    res.N = A.N;
    res.M = B.M;
    int n = res.N, m = res.M, p = A.M;
    long long t;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            t = 0;
            for (int k = 1; k <= p; ++k)
            {
                t += A.a[i][k] * B.a[k][j];
                t %= MOD;
            }
            res.a[i][j] = t;
        }
    }
    return res;
}
void Matrix::Init(long long _a[201][201], int n, int m)
{
    N = n;
    M = m;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            a[i][j] = _a[i][j];
        }
    }
    return;
}
long long qpow(long long x, long long y)
{
    long long ret = 1;
    while (y)
    {
        if (y & 1)
            ret *= x;
        ret %= mod;
        x *= x;
        x %= mod;
        y >>= 1;
    }
    return ret;
}

int main()
{
//    freopen("seq.in", "r", stdin);
//    freopen("seq.out", "w", stdout);
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= k; ++i)
    {
        scanf("%lld", &b[i]);
    }
    for (int i = 1; i <= k; ++i)
    {
        scanf("%lld", &f[i]);
    }
    if (n <= k)
    {
        printf("%lld", f[n]);
        return 0;
    }
    for (int i = 1; i <= k; ++i)
    {
        tmp[i][1] = b[i];
    }
    for (int i = 1; i < k; ++i)
    {
        tmp[i][i + 1] = 1;
    }
    X.Init(tmp, k, k);
    X = X ^ (n - k);
    long long ans = 1;
    for (int i = k; i >= 1; --i)
    {
        ans *= qpow(f[i], X.GetNum(k - i + 1, 1));
        ans %= mod;
    }
    printf("%lld", ans);
    return 0;
}
