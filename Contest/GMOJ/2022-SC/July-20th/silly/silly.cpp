#include <stdio.h>
long long gcd(long long a, long long b);
long long lcm(long long a, long long b);
struct Q
{
    long long p;
    long long q;
    void Simplify();
};
bool operator<(const Q &a, const Q &b);
bool operator>(const Q &a, const Q &b);
bool operator==(const Q &a, const Q &b);
Q operator-(const Q &a, const Q &b);
const int MAXN = 1e5 + 5;
char str[MAXN];
int len[MAXN];
int main()
{
    freopen("silly.in", "r", stdin);
    freopen("silly.out", "w", stdout);
    int t;
    scanf("%d", &t);
    for (int tt = 1; tt <= t; ++tt)
    {
        int n;
        scanf("%d", &n);
        char cha;
        int sum_b = 0, sum_w = 0;
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &len[i]);
            cha = getchar();
            while (cha != 'B' && cha != 'W')
            {
                cha =  getchar();
            }
            str[i] = cha;
            if (cha == 'B')
            {
                sum_b += len[i];
            }
            else
            {
                sum_w += len[i];
            }
        }
        if (sum_b == 0 || sum_w == 0)
        {
            printf("%d\n", sum_b + sum_w);
            continue;
        }
        Q num = (Q){sum_b, sum_w};
        num.Simplify();
        Q now = {0, 0}, last;
        Q tmp;
        int ans = 0;
        long long cnt_b = 0, cnt_w = 0;
        for (int i = 1; i <= n; ++i)
        {
            last = now;
            if (str[i] == 'B')
                cnt_b += len[i];
            else
                cnt_w += len[i];
            now = (Q){cnt_b, cnt_w};
            now.Simplify();
            if (cnt_b == 0 || cnt_w == 0)
                continue;
            if (last < num || last.p == 0)
            {
                if (str[i] == 'W')
                {
                    continue;
                }
                if (now > num || now == num)
                {
                    tmp = (Q){sum_b * cnt_w, sum_w};
                    tmp.Simplify();
                    if (tmp.q == 1)
                    {
                        ++ans;
                    }
                }
            }
            else if (last > num || last.q == 0)
            {
                if (str[i] == 'B')
                {
                    continue;
                }
                if (now < num || now == num)
                {
                    tmp = (Q){sum_w * cnt_b, sum_b};
                    tmp.Simplify();
                    if (tmp.q == 1)
                    {
                        ++ans;
                    }
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
bool operator==(const Q &a, const Q &b)
{
    return a.p == b.p && a.q == b.q;
}
Q operator-(const Q &a, const Q &b)
{
    Q ret = a;
    int l = lcm(a.q, b.q);
    ret.p *= l / a.q;
    ret.q = l;
    ret.p -= b.p * l / b.q;
    ret.Simplify();
    return ret;
}
bool operator<(const Q &a, const Q &b)
{
    return (long long)a.p * b.q < (long long)a.q * b.p;
}
bool operator>(const Q &a, const Q &b)
{
    return (long long)a.p * b.q > (long long)a.q * b.p;
}
void Q::Simplify()
{
    long long g = gcd(p, q);
    p /= g;
    q /= g;
    return;
}
long long gcd(long long a, long long b)
{
    if (!b)
        return a;
    return gcd(b, a %  b);
}
long long lcm(long long a, long long b)
{
    return a / gcd(a, b) * b;
}
