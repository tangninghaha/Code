#include <cstdio>

/* Constant */
const int MAXN = 1e6 + 5;
const long long T = 1e17;

/* Class */
class HighNum
{
    private: 
        long long num1;
        long long num2;
    public:
        void Print();
        HighNum();
        friend HighNum operator+(const HighNum& a, const HighNum &b);
        friend HighNum operator+(const HighNum& a, const long long &b);
        friend HighNum operator-(const HighNum& a, const HighNum &b);
        friend HighNum operator-(const HighNum& a, const long long &b);
        friend HighNum Max(const HighNum& a, const HighNum &b);
        void operator=(const long long &x_);
};

/* Declaration */
int main();
long long pow2(long long);
long long Max(long long a, long long b);
int Max(int a, int b);
int Min(int a, int b);
HighNum Max(const HighNum &a, const HighNum &b);
void FileIO();
void Write(__int128);
__int128 Max(__int128 x, __int128 y);

/* Variable */
int s[MAXN];
__int128 sum[MAXN];
__int128 sum_jsj2[MAXN];
__int128 sum_jsj[MAXN];

/* Definition */
HighNum Max(const HighNum &a, const HighNum &b)
{
    if (a.num2 == b.num2)
    {
        return a.num1 > b.num1 ? a : b;
    }
    return a.num2 > b.num2 ? a : b;
}
void HighNum::Print()
{
    if (num2)
    {
        printf("%lld%017lld", num2, num1);
    }
    else
    {
        printf("%lld", num1);
    }
}
HighNum::HighNum()
{
    num1 = 0;
    num2 = 0;
}
HighNum operator-(const HighNum& a, const long long &b)
{
    HighNum tmp;
    tmp = b;
    return a - tmp;
}
HighNum operator+(const HighNum& a, const long long &b)
{
    HighNum tmp;
    tmp = b;
    return a + tmp;
}
HighNum operator-(const HighNum& a, const HighNum &b)
{
    HighNum ret;
    ret = a;
    ret.num2 -= b.num2;
    ret.num1 -= b.num1;
    while (ret.num1 < 0)
    {
        --ret.num2;
        ret.num1 += T;
    }
    return ret;
}
void HighNum::operator=(const long long &x_)
{
    num2 = 0;
    num1 = x_;
    if (num1 >= T)
    {
        num2 += num1 / T;
        num1 %= T;
    }
}
HighNum operator+(const HighNum& a, const HighNum &b)
{
    HighNum ret;
    ret.num1 = a.num1 + b.num1;
    if (ret.num1 >= T)
    {
        ret.num2 += ret.num1 / T;
        ret.num1 %= T;
    }
    ret.num2 += a.num2 + b.num2;
    return ret;
}

int main()
{
    FileIO();
    int n, d;
    scanf("%d%d", &n, &d);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &s[i]);
        sum[i] = sum[i - 1] + s[i];
        sum_jsj[i] = sum_jsj[i - 1] + (long long)i * s[i];
        sum_jsj2[i] = sum_jsj2[i - 1] + (long long)i * i * s[i];
//        printf("%lld\n", sum_jsj[i]);
        // sum_jsj2[i].Print();
        Write(sum_jsj2[i]);
        printf("\n");
    }
    __int128 num;
    __int128 ans;
    int st, ed;
    for (int i = 1; i <= n; ++i)
    {
        st = Max(i - d, 1);
        ed = Min(n, i + d - 1);
        num = pow2(d - i + 1) * (sum[i - 1] - sum[st - 1]);
        num = num + (sum_jsj2[i - 1] - sum_jsj2[st - 1]);
        num = num + 2 * (d - i + 1) * (sum_jsj[i - 1] - sum_jsj[st - 1]);
        num = num + pow2(d + i) * (sum[ed] - sum[i - 1]);
        num = num + (sum_jsj2[ed] - sum_jsj2[i - 1]);
        num = num - 2 * (d + i) * (sum_jsj[ed] - sum_jsj[i - 1]);
        // for (int j = st; j < i; ++j)
        // {
        //     sum += pow2(d - (i - j - 1)) * s[j];
        // }
        // for (int j = i; j <= ed; ++j)
        // {
        //     sum += pow2(d - (j - i)) * s[j];
        // }
        ans = Max(ans, num);
    }
    // ans.Print();
    Write(ans);
    // printf("%lld", ans);
    return 0;
}
__int128 Max(__int128 x, __int128 y)
{
    return x > y ? x : y;
}
long long pow2(long long x_)
{
    return (long long)x_ * x_;
}
long long Max(long long a_, long long b_)
{
    return a_ > b_ ? a_ : b_;
}
int Max(int a_, int b_)
{
    return a_ > b_ ? a_ : b_;
}
int Min(int a_, int b_)
{
    return a_ < b_ ? a_ : b_;
}
void FileIO()
{
    freopen("weather.in", "r", stdin);
    freopen("weather128.out", "w", stdout);
    return;
}
void Write(__int128 x)
{
    static int sta[40];
    int top = 0;
    if (x < 0)
    {
        printf("-");
    }
    while (x)
    {
        sta[++top] = x % 10;
        x /= 10;
    }
    while (top)
    {
        putchar(sta[top--] + 48);
    }
    return;
}
