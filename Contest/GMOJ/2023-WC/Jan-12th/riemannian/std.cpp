#include <cstdio>

/* Constant */
const int mod = 998244353;
const int BASIC[9] = {0, 1, 0, 2, 2, 0, 1, 2, 1};
const int N = 1e6 + 1;

/* Class */
class Matrix
{
    public:
        Matrix();
        Matrix(int, int, const int*);
        long long a[3][3];
        int n, m;
};
Matrix::Matrix(int _x, int _y, const int* _a)
{
    n = _x;
    m = _y;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            a[i][j] = 0;
        }
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            a[i][j] = _a[i * n + j];
        }
    }
    return;
}
Matrix::Matrix()
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            a[i][j] = 0;
        }
    }
    return;
}
Matrix operator*(const Matrix& _a, const Matrix& _b)
{
    Matrix ret;
    ret.n = _a.n;
    ret.m = _b.m;
    for (int i = 0; i < ret.n; ++i)
    {
        for (int j = 0; j < ret.m; ++j)
        {
            for (int k = 0; k < _a.m; ++k)
            {
                ret.a[i][j] += (_a.a[i][k] * _b.a[k][j]) % mod;
                ret.a[i][j] %= mod;
            }
        }
    }
    return ret;
}

/* Declaration */
int main();
Matrix qpow(Matrix, long long);
long long Read();

/* Variable */
Matrix basic_pow_n[N];
Matrix basic_pow[N]; 

/* Definition */
int main()
{
    freopen("riemannian.in", "r", stdin);
    freopen("riemannian.out", "w", stdout);
    int t;
    t = Read();
    long long n;
    Matrix basic(3, 3, BASIC);
    
    Matrix I;
    I.n = 3;
    I.m = 3;
    for (int i = 0; i < I.n; ++i)
    {
        I.a[i][i] = 1;
    }
    basic_pow[0] = I;
    for (int i = 1; i < N; ++i)
    {
        basic_pow[i] = basic_pow[i - 1] * basic;
    }
    basic_pow_n[0] = I;
    for (int i = 1; i < N; ++i)
    {
        basic_pow_n[i] = basic_pow_n[i - 1] * basic_pow[N - 1];
    }
    
    Matrix x;
    long long ans1 = 0, ans2 = 0;
    for (int i = 1; i <= t; ++i)
    {
        x.n = 1;
        x.m = 3;
        x.a[0][0] = 1;
        x.a[0][1] = 2;
        x.a[0][2] = 1;
        n = Read();
        x = x * basic_pow_n[(n - 1) / (N - 1)] * basic_pow[(n - 1) % (N - 1)];
        ans1 ^= x.a[0][0];
        ans2 ^= x.a[0][1];
    }
    printf("%lld %lld", ans1, ans2);
    return 0;
}
Matrix qpow(Matrix _a, long long k)
{
    Matrix ret;
    ret.n = _a.n;
    ret.m = _a.n;
    for (int i = 1; i <= ret.n; ++i)
    {
        ret.a[i][i] = 1;
    }
    while (k)
    {
        if (k & 1)
            ret = ret * _a;
        _a = _a * _a;
        k >>= 1;
    }
    return ret;
}
long long Read()
{
    long long ret = 0;
    char tmp = getchar();
    while (tmp < '0' || tmp > '9')
        tmp = getchar();
    while (tmp >= '0' && tmp <= '9')
    {
        ret = (ret << 1) + (ret << 3) + tmp - '0';
        tmp = getchar();
    }
    return ret;
}
