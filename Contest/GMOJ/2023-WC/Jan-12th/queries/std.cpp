#include <cstdio>

/* Constant */
const int MAXN = 1e5 + 1;
const int mod = 1e9 + 7;

void Mod(long long& _x)
{
    _x = (_x % mod + mod) % mod;
}

/* Class */
class LineTree
{
    public:
        long long tr[MAXN << 2];
        long long lazy[MAXN << 2];
        long long i_sum[MAXN];
        bool ch_lazy[MAXN << 2];
        int type;
        
        void Init(int, int, int, int*);
        void Update(int, int, int, int, int, int);
        void DownLazy(int, int, int);
        long long GetSum(int, int, int, int, int);
};

void LineTree::Init(int l, int r, int k, int *a)
{
    if (l == r)
    {
        tr[k] = (i_sum[l] - i_sum[l - 1]) * a[l];
        Mod(tr[k]);
        return;
    }
    int mid = l + r >> 1;
    Init(l, mid, k * 2, a);
    Init(mid + 1, r, k * 2 + 1, a);
    tr[k] = tr[k * 2] + tr[k * 2 + 1];
    tr[k] %= mod;
    return;
}
void LineTree::Update(int l, int r, int x, int y, int k, int num)
{
    if (x <= l && r <= y)
    {
        tr[k] = (i_sum[r] - i_sum[l - 1]) * num;
        Mod(tr[k]);
        ch_lazy[k] = true; 
        lazy[k] = num;
        return;
    }
    if (ch_lazy[k])
        DownLazy(k, l, r);
    int mid = l + r >> 1;
    if (x <= mid)
        Update(l, mid, x, y, k * 2, num);
    if (y > mid)
        Update(mid + 1, r, x, y, k * 2 + 1, num);
    tr[k] = tr[k * 2] + tr[k * 2 + 1];
    tr[k] %= mod;
    return;
}
void LineTree::DownLazy(int _x, int l, int r)
{
    int mid = l + r >> 1;
    tr[_x * 2] = (i_sum[mid] - i_sum[l - 1]) * lazy[_x];
    Mod(tr[_x * 2]);
    tr[_x * 2 + 1] = (i_sum[r] - i_sum[mid]) * lazy[_x];
    Mod(tr[_x * 2 + 1]);
    lazy[_x * 2] = lazy[_x];
    lazy[_x * 2 + 1] = lazy[_x];
    lazy[_x] = 0;
    ch_lazy[_x] = false;
    ch_lazy[_x * 2] = true;
    ch_lazy[_x * 2 + 1] = true;
    return;
}
long long LineTree::GetSum(int l, int r, int x, int y, int k)
{
    if (x <= l && r <= y)
    {
        return tr[k];
    }
    if (ch_lazy[k])
        DownLazy(k, l, r);
    int mid = l + r >> 1;
    long long ret = 0;
    if (x <= mid)
        ret += GetSum(l, mid, x, y, k * 2);
    ret %= mod;
    if (y > mid)
        ret += GetSum(mid + 1, r, x, y, k * 2 + 1);
    ret %= mod;
    return ret;
}

/* Declaration */
int main();
long long qpow(long long, long long);

/* Variable */
int a[MAXN];
LineTree t[6];

/* Definition */
int main()
{
    freopen("queries.in", "r", stdin);
    freopen("queries.out", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i <= 5; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            t[i].i_sum[j] = t[i].i_sum[j - 1] + qpow(j, i);
            t[i].i_sum[j] %= mod;
        }
    }

    for (int i = 0; i <= 5; ++i)
        t[i].Init(1, n, 1, a);

    char cha;
    int l, r, x;
    long long ans;
    for (int i = 1; i <= m; ++i)
    {
        while (cha != '=' && cha != '?')
            cha = getchar();
        scanf("%d%d%d", &l, &r, &x);
        
        if (cha == '=')
        {
            for (int j = 0; j <= 5; ++j)
                t[j].Update(1, n, l, r, 1, x);
        }
        if (cha == '?')
        {
            if (x == 0)
            {
                ans = t[0].GetSum(1, n, l, r, 1);
                printf("%lld\n", ans);
            }
            else if (x == 1)
            {
                ans = t[1].GetSum(1, n, l, r, 1);
                ans -= (t[0].GetSum(1, n, l, r, 1) * (l - 1)) % mod;
                Mod(ans);
                printf("%lld\n", ans);
            }
            else if (x == 2)
            {
                ans = t[2].GetSum(1, n, l, r, 1);
                ans -= (((((t[1].GetSum(1, n, l, r, 1) * 2) % mod) * (l - 1)) % mod)) % mod;
                Mod(ans);
                ans += (t[0].GetSum(1, n, l, r, 1) * qpow(l - 1, 2)) % mod;
                Mod(ans);
                printf("%lld\n", ans);
            }
            else if (x == 3)
            {
                ans = t[3].GetSum(1, n, l, r, 1);
                ans -= (((3 * t[2].GetSum(1, n, l, r, 1)) % mod) * (l - 1)) % mod;
                Mod(ans);
                ans += (((3 * t[1].GetSum(1, n, l, r, 1)) % mod) * qpow(l - 1, 2)) % mod;
                Mod(ans);
                ans -= (t[0].GetSum(1, n, l, r, 1) * qpow(l - 1, 3)) % mod;
                Mod(ans);
                printf("%lld\n", ans);
            }
            else if (x == 4)
            {
                ans = t[4].GetSum(1, n, l, r, 1);
                ans -= (((4 * t[3].GetSum(1, n, l, r, 1)) % mod) * (l - 1))  % mod;
                Mod(ans);
                ans += (((6 * t[2].GetSum(1, n, l, r, 1)) % mod) * qpow(l - 1, 2)) % mod;
                Mod(ans);
                ans -= (((4 * t[1].GetSum(1, n, l, r, 1)) % mod) * qpow(l - 1, 3)) % mod;
                Mod(ans);
                ans += (t[0].GetSum(1, n, l, r, 1) * qpow(l - 1, 4)) % mod;
                Mod(ans);
                printf("%lld\n", ans);
            }
            else if (x == 5)
            {
                ans = t[5].GetSum(1, n, l, r, 1);
                ans -= (((5 * t[4].GetSum(1, n, l, r, 1)) % mod) * (l - 1)) % mod;
                Mod(ans);
                ans += (((10 * t[3].GetSum(1, n, l, r, 1)) % mod) * qpow(l - 1, 2)) % mod;
                Mod(ans);
                ans -= (((10 * t[2].GetSum(1, n, l, r, 1)) % mod) * qpow(l - 1, 3)) % mod;
                Mod(ans);
                ans += (((5 * t[1].GetSum(1, n, l, r, 1)) % mod) * qpow(l - 1, 4)) % mod;
                Mod(ans);
                ans -= (t[0].GetSum(1, n, l, r, 1) * qpow(l - 1, 5)) % mod;
                Mod(ans);
                printf("%lld\n", ans);
            }
        }
        cha = getchar();
    }
    return 0;
}
long long qpow(long long _a, long long _b)
{
    if (!_b)
        return 1;
    if (_b == 1)
        return _a;
    long long ret = qpow(_a, _b / 2);
    if (_b & 1)
        return (((ret * ret) % mod) * _a) % mod;
    else
        return (ret * ret) % mod;
    return 0;
}
