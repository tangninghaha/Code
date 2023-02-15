#include <cstdio>

/* Constant */
const int MAXN = 1e6 + 5;
const long long T = 1e15;

/* Class */
class HighNum
{
    private: 
        long long num1;
        long long num2;
        bool fu;
    public:
        void Print();
        HighNum();
        friend HighNum operator+(const HighNum& a, const HighNum &b);
        friend HighNum operator+(const HighNum& a, const long long &b);
        friend HighNum operator-(const HighNum& a, const HighNum &b);
        friend HighNum operator-(const HighNum& a, const long long &b);
        friend HighNum Max(const HighNum& a, const HighNum &b);
        friend HighNum operator*(const long long &b, const HighNum& a);
        bool operator>(const HighNum& x);
        void operator=(const long long &x_);
        friend HighNum Abs(const HighNum& x);
};

/* Declaration */
int main();
long long pow2(long long);
long long Max(long long a, long long b);
int Max(int a, int b);
int Min(int a, int b);
HighNum Max(const HighNum &a, const HighNum &b);
void FileIO();

/* Variable */
int s[MAXN];
HighNum sum[MAXN];
HighNum sum_jsj2[MAXN];
HighNum sum_jsj[MAXN];

/* Definition */
HighNum Abs(const HighNum& x)
{
    HighNum ret;
    ret = x;
    ret.fu = 0;
    return ret;
}
bool HighNum::operator>(const HighNum& x)
{
    return num2 == x.num2 ? num1 > x.num1 : num2 > x.num2;
}
HighNum operator*(const long long &b, const HighNum& a)
{
    HighNum ret;
    ret = a;
    if (b < 0)
    {
        ret.fu = !ret.fu;
    }
    ret.num1 *= b;
    ret.num2 *= b;
    if (ret.num1 >= T)
    {
        ret.num2 += ret.num1 % T;
        ret.num1 %= T;
    }
    return ret;
}
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
    if (fu)
    {
        printf("-");
    }
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
    fu = 0;
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
    HighNum tmp = b;
    tmp.fu = !tmp.fu;
    ret = a + tmp;
    return ret;
}
void HighNum::operator=(const long long &x_)
{
    if (x_ < 0)
    {
        fu = 1;
    }
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
    bool pd = false;
    if (a.fu != b.fu)
    {
        if (Abs(a) > Abs(b))
        {
            pd = true;
            ret.fu = a.fu;
        }
        else
        {
            ret.fu = b.fu;
        }
    }
    else
    {
        ret.fu = a.fu;
    }
    if (a.fu == b.fu)
    {
        ret.num1 = a.num1 + b.num1;
        ret.num2 = a.num2 + b.num2;
        if (ret.num1 >= T)
        {
            ret.num2 += ret.num1 / T;
            ret.num1 %= T;
        }
    }
    else
    {
        if (pd)
        {
            ret.num1 = a.num1 - b.num1;
            ret.num2 = a.num2 - b.num2;
            if (ret.num1 < 0)
            {
                ret.num1 += T;
                --ret.num2;
            }
        }
        else
        {
            ret.num1 = b.num1 - a.num1;
            ret.num2 = b.num2 - a.num2;
            if (ret.num1 < 0)
            {
                ret.num1 += T;
                --ret.num2;
            }
        }
    }
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
        sum_jsj2[i].Print();
        printf("\n");
    }
    HighNum num;
    HighNum ans;
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
    ans.Print();
    // printf("%lld", ans);
    return 0;
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
    freopen("weather.out", "w", stdout);
    return;
}
