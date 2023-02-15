#include <cstdio>
#include <cmath>

/* Constant */
const int MAXN = 1e5 + 5;

/* Class */
struct Node
{
    long long num;
    int st;
    int ed;
};

/* Declaration */
int main();
int Read();
void Print(long long);
long long Gcd(long long, long long);

/* Variable */
Node x[MAXN];
Node nxt_x[MAXN];
int a[MAXN];
int stack[31], top;

/* Definition */
int Read()
{
    int ret = 0;
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
int main()
{
    freopen("trafficlight.in", "r", stdin);
    freopen("trafficlight.out", "w", stdout);
    int n, m;
    n = Read();
    m = Read();
    for (register int i = 1; i <= m; ++i)
    {
        a[i] = Read();
    }
    int tot = n;
    int nxt_tot;
    int lbound, rbound, mid;
    int k;
    int last;
    long long gcd = 1e9 + 7;
    for (register int i = 1; i <= n; ++i)
    {
        x[i].num = i;
        x[i].st = i;
        x[i].ed = i;
    }
    for (register int i = 1; i <= m; ++i)
    {
        if (a[i] == 1)
            continue;
        if (a[i] == a[i - 1])
            continue;
        if (!(gcd % a[i]))
            continue;
        last = 0;
        nxt_tot = 0;
        while (nxt_x[nxt_tot].ed < n)
        {
            k = ceil(1.0 * x[last + 1].num / a[i]) * a[i];
            ++nxt_tot;
            nxt_x[nxt_tot].num = k;
            nxt_x[nxt_tot].st = last + 1;
            lbound = last + 1;
            rbound = tot;
            while (lbound <= rbound)
            {
                mid = (lbound + rbound) >> 1;
                if (x[mid].num <= k)
                {
                    last = mid;
                    lbound = mid + 1;
                }
                else
                {
                    rbound = mid - 1;
                }
            }
            nxt_x[nxt_tot].ed = x[last].ed;
        }
        gcd = x[1].num;
        for (register int j = 1; j <= nxt_tot; ++j)
        {
            x[j] = nxt_x[j];
            gcd = Gcd(x[j].num, gcd);
        }
        tot = nxt_tot;
    }
    int j = 1;
    for (register int i = 1; i <= n; ++i)
    {
        if (i > x[j].ed)
            ++j;
//        printf("%lld ", x[j].num);
        Print(x[j].num);
        putchar(' ');
    }
    return 0;
}
void Print(long long _x)
{
    top = 0;
    while (_x)
    {
        ++top;
        stack[top] = _x % 10;
        _x /= 10;
    }
    for (register int i = top; i >= 1; --i)
    {
        putchar(stack[i] + 48);
    }
    return;
}
long long Gcd(long long _a, long long _b)
{
    return !_b ? _a : Gcd(_b, _a % _b);
}
