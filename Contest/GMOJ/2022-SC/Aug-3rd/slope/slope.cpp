#include <stdio.h>
const int MAXN = 1e3 + 5;
struct Q
{
    long long p;
    long long q;
    void Smpl();
};
bool operator< (const Q &a, const Q &b);
bool operator> (const Q &a, const Q &b);
bool operator== (const Q &a, const Q &b);
Q operator- (const Q &a, const Q &b);
struct Point
{
    int x;
    int y;
};

Point pnt[MAXN];

void FileIO();
long long Gcd(long long a, long long b);
long long Lcm(long long a, long long b);
int main();
void Qsort(int l, int r);
Q Sovle(int n, Q x);
void Swap(Q &a, Q &b);

void Q::Smpl()
{
    long long g = Gcd(p, q);
    p /= g;
    q /= g;
    return;
}
bool operator< (const Q &a, const Q &b)
{
    return a.p * b.q < a.q * b.p;
}
bool operator> (const Q &a, const Q &b)
{
    return a.p * b.q > a.q * b.p;
}
bool operator== (const Q &a, const Q &b)
{
    return a.p == b.p && a.q == b.q;
}
Q operator- (const Q &a, const Q &b)
{
    long long l = Lcm(a.q, b.q);
    Q ret;
    ret.q = l;
    ret.p = l / a.q * a.p - l / b.q * b.p;
    return ret;
}

void FileIO()
{
    freopen("slope.in", "r", stdin);
    freopen("slope.out", "w", stdout);
    return;
}
long long Gcd(long long a, long long b)
{
    if (!b)
        return a;
    return Gcd(b, a % b);
}
long long Lcm(long long a, long long b)
{
    return a / Gcd(a, b) * b;
}
int main()
{
    FileIO();
    int n, p, q;
    scanf("%d%d%d", &n, &p, &q);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d", &pnt[i].x, &pnt[i].y);
    }
    Q ans = Sovle(n, (Q){p, q});
    printf("%lld/%lld", ans.p, ans.q);
    return 0;
}
Q Sovle(int n, Q x)
{
    x.Smpl();
    Q ret = (Q){0, 0};
    Q ret_c = x;
    Q c;
    Q tmp;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = i + 1; j <= n; ++j)
        {
            tmp = (Q){pnt[i].y - pnt[j].y, pnt[i].x - pnt[j].x};
            tmp.Smpl();
            if (tmp == x)
            {
                return tmp;
            }
            if (tmp > x)
            {
                c = tmp - x;
                if (c < ret_c)
                {
                    ret = tmp;
                    ret_c = c;
                }
            }
            if (tmp < x)
            {
                c = x - tmp;
                if (c < ret_c || c == ret_c)
                {
                    ret = tmp;
                    ret_c = c;
                }
            }
        }
    }
    return ret;
}
