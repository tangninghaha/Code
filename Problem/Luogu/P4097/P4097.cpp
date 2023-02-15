#include <cstdio>

/* Constant */
const int MAXN = 4e4 +5;
const int mod = 39989;
const double exp = 1e-10;
const int mod2 = 1e9;
const int MAXQ = 1e5 + 5;

int Cmp(double _a, double _b)
{
    if (_a < _b)
    {
        if (_b - _a <= exp)
            return 0;
        return -1;
    }
    else
    {
        if (_a - _b <= exp)
            return 0;
        return 1;
    }
}

/* Class */
class analysis_formula
{
    public:
        double k;
        double b;
        double F(int);
};
double analysis_formula::F(int x)
{
    return k * x + b;
}
class segement
{
    public:
        int l;
        int r;
        int num;
        analysis_formula a;
};
class Ans
{
    public:
        double x;
        int num;
};
class LCT
{
    public:
        int tr[MAXN << 2];
        void Update(int, int, int, segement);
        void DownLazy(int, int, int, segement);
        Ans GetMax(int, int, int, int);
};
bool operator>(const Ans& _a, const Ans& _b)
{
    if (!Cmp(_a.x, _b.x))
    {
        return _a.num < _b.num;
    }
    return Cmp(_a.x, _b.x) > 0;
}

/* Declaration */
int main();
double GetHigh(int);
template<typename T> T Max(T, T);
template<typename T> void Swap(T&, T&); 

/* Variable */
segement input[MAXQ];
LCT T;

/* Definition */
void LCT::Update(int l, int r, int k, segement a)
{
    if (a.l <= l && r <= a.r)
    {
        DownLazy(l, r, k, a);
        return;
    }
    int mid = l + r >> 1;
    if (a.l <= mid)
        Update(l, mid, k * 2, a);
    if (a.r > mid)
        Update(mid + 1, r, k * 2 + 1, a);
    return;
}
void LCT::DownLazy(int l, int r, int k, segement a)
{
    int mid = l + r >> 1;
    if (Cmp(a.a.F(mid), input[tr[k]].a.F(mid)) > 0)
    {
        int tmp = a.num;
        a = input[tr[k]];
        tr[k] = tmp;
    }
    int lb = Cmp(a.a.F(l), input[tr[k]].a.F(l));
    int rb = Cmp(a.a.F(r), input[tr[k]].a.F(r));
    if (lb == 1 || (!lb && a.num < tr[k]))
        DownLazy(l, mid, k * 2, a);
    if (rb == 1 || (!rb && a.num < tr[k]))
        DownLazy(mid + 1, r, k * 2 + 1, a);
    return;
}
Ans LCT::GetMax(int l, int r, int k, int x)
{
    Ans ret = {-1000000, MAXQ};
    if (l == x && r == x)
    {
        return (Ans){input[tr[k]].a.F(x), tr[k]};
    }
    int mid = l + r >> 1;
    if (x <= mid)
        ret = Max(ret, GetMax(l, mid, k * 2, x));
    else
        ret = Max(ret, GetMax(mid + 1, r, k * 2 + 1, x));
    ret = Max(ret, (Ans){input[tr[k]].a.F(x), tr[k]});
    return ret;
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int n;
    scanf("%d", &n);
    int op;
    int k;
    int x1, y1, x2, y2;
    segement tmp;
    int num = 0;
    int last_ans = 0;
    input[0].a.b = -1e9 + 7;
    input[0].a.k = -1;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &op);
        if (!op)
        {
            scanf("%d", &k);
            last_ans = T.GetMax(1, mod, 1, (k + last_ans - 1) % mod + 1).num;
            if (last_ans == MAXQ)
                last_ans = 0;
            printf("%d\n", last_ans);
        }
        else
        {
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            x1 = (x1 + last_ans - 1) % mod + 1;
            x2 = (x2 + last_ans - 1) % mod + 1;
            y1 = (y1 + last_ans - 1) % mod2 + 1;
            y2 = (y2 + last_ans - 1) % mod2 + 1;
            if (x1 == x2)
            {
                tmp.l = x1;
                tmp.r = x1;
                tmp.a.k = 0;
                tmp.a.b = Max(y1, y2);
            }
            else
            {
                if (x1 > x2)
                {
                    Swap(x1, x2);
                    Swap(y1, y2);
                }
                tmp.l = x1;
                tmp.r = x2;
                tmp.a.k = (double)(y2 - y1) / (x2 - x1);
                tmp.a.b = (double)(y1 + y2 - tmp.a.k * (x1 + x2)) / 2;
            }
            tmp.num = ++num;
            input[num] = tmp;
//            printf("%d Update\n", i);
            T.Update(1, mod, 1, input[num]);
        }
    }
    return 0;
}
template<typename T> T Max(T _a, T _b)
{
    return _a > _b ? _a : _b;
}
template<typename T> void Swap(T& _a, T& _b)
{
    int t = _a;
    _a = _b;
    _b = t;
    return;
}
