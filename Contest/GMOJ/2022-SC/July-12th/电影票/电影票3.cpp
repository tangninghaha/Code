#include <stdio.h>
#include <cmath>
#include <cstring>

const int kP = 10000;
const int kMAXP = 7000;
/* 质因子 */
struct tPrimeSon
{
    int a[kMAXP]; /* 对于每个素因子, 表示为 prime[i]^a[i] */
    
    // int sp_prime[55][2]; /* 第一维是 sp 的值, 第二维表示指数 */
    // int sp_prime_tot;

    void Init(int x); /* 对数字 x 分解质因数 */
    void Init_JC(int x); /* 处理 x! */
    tPrimeSon();
};
tPrimeSon operator/(const tPrimeSon &a, const tPrimeSon &b);
tPrimeSon operator*(const tPrimeSon &a, const tPrimeSon &b);

/* 质数表 */
int prime[kMAXP], prime_tot;
bool pd[kP + 1];
void InitPrime();
/* 高精度 */
const int kMAXLEN = 1e5;
struct tHighNum
{
    int num[kMAXLEN];
    int len;
    void write();
    void operator=(int x);
    tHighNum();
};
tHighNum operator*(const tHighNum &a, const int &b);

/* 主函数 */
int main()
{
    InitPrime();
    int n, m;
    scanf("%d%d", &n, &m);
    tPrimeSon num1, num2, num3, num4;
    num1.Init_JC(n + m);
    num2.Init_JC(m);
    num3.Init_JC(n + 1);
    num4.Init(n - m + 1);
    num1 = num1 * num4;
    num1 = num1 / num2;
    num1 = num1 / num3;
    tHighNum ans;
    ans = 1;
    for (int i = 1; i <= prime_tot; ++i)
    {
        if (num1.a[i] > 0)
        {
            for (int j = 1; j <= num1.a[i]; ++j)
            {
                ans = ans * prime[i];
            }
        }
    }
    ans.write();
}

/* 质因子 */
tPrimeSon::tPrimeSon()
{
    // sp_prime_tot = 0;
    memset(a, 0, sizeof(a));
    return;
}
void tPrimeSon::Init(int x)
{
    for (int i = 1; i <= prime_tot; ++i)
    {
        while (!(x % prime[i]))
        {
            ++a[i];
            x /= prime[i];
        }
    }
    // if (x != 1)
    // {
        // ++sp_prime_tot;
        // sp_prime[sp_prime_tot][0] = x;
        // sp_prime[sp_prime_tot][1] = 1;
    // }
    return;
}
tPrimeSon operator/(const tPrimeSon &a, const tPrimeSon &b)
{
    tPrimeSon ret;
    for (int i = 1; i <= prime_tot; ++i)
    {
        ret.a[i] = a.a[i] - b.a[i];
    }
    return ret;
}
tPrimeSon operator*(const tPrimeSon &a, const tPrimeSon &b)
{
    tPrimeSon ret;
    for (int i = 1; i <= prime_tot; ++i)
    {
        ret.a[i] = a.a[i] + b.a[i];
    }
    return ret;
}
void tPrimeSon::Init_JC(int x)
{
    int k;
    for (int i = 1; i <= prime_tot; ++i)
    {
        k = prime[i];
        while (k <= x)
        {
            a[i] += x / k;
            k *= prime[i];
        }
    }
    return;
}
/* 质数表 */
void InitPrime()
{
    int nxt_num;
    for (int i = 2; i <= kP; ++i)
    {
        if (!pd[i])
        {
            prime[++prime_tot] = i;
        }
        for (int j = 1; j <= prime_tot; ++j)
        {
            nxt_num = prime[j] * i;
            if (nxt_num > kP)
                break;
            pd[nxt_num] = true;
            if (!(i % prime[j]))
                break;
        }
    }
    return;
}
/* 高精度 */
tHighNum::tHighNum()
{
    memset(num, 0, sizeof(num));
    len = 0;
    return;
}
void tHighNum::write()
{
    for (int i = len; i >= 1; --i)
    {
        printf("%d", num[i]);
    }
    return;
}
void tHighNum::operator=(int x)
{
    int tmp = x;
    while (tmp)
    {
        ++len;
        num[len] = tmp % 10;
        tmp /= 10;
    }
    return;
}
tHighNum operator*(const tHighNum &a, const int &b)
{
    tHighNum ret;
    ret.len = a.len;
    for (int i = 1; i <= a.len; ++i)
    {
        ret.num[i] += a.num[i] * b;
        if (ret.num[i] >= 10)
        {
            ret.num[i + 1] += ret.num[i] / 10;
            ret.num[i] %= 10;
            if (i == a.len)
            {
                ++ret.len;
            }
        }
    }
    while (ret.num[ret.len] >= 10)
    {
        ret.num[ret.len + 1] += ret.num[ret.len] / 10;
        ret.num[ret.len] %= 10;
        ++ret.len;
    }
    return ret;
}
