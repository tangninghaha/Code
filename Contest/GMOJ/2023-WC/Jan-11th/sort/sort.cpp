#include <cstdio>

/* Constant */
const int MAXN = 2049;

/* Class */
class Set
{
    public: 
        int num1;
        int num2;
};

/* Declaration */
int main();
void Sovle(int, int, int);
bool Check(int, int);
void Init(int, int);
template <typename T> void Swap(T&, T&);

/* Variable */
Set a[MAXN][65];
long long ans;
int twom[13];
long long jc[65];

/* Definition */
int main()
{
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);
    twom[0] = 1;
    for (int i = 1; i <= 12; ++i)
    {
        twom[i] = twom[i - 1] << 1;
    }
    jc[0] = 1;
    for (int i = 1; i <= 64; ++i)
    {
        jc[i] = jc[i - 1] * i;
    }
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= twom[n - 1]; ++i)
    {
        scanf("%d%d", &a[i][0].num1, &a[i][0].num2);
    }
    Sovle(0, twom[n - 1], 0);
    printf("%lld", ans);
    return 0;
}
void Sovle(int dep, int num, int cnt)
{
    if (!num)
    {
        ans += jc[cnt];
        return;
    }
    int k1 = 0, k2 = 0;
    for (int i = 1; i <= num; ++i)
    {
        if (Check(i, dep))
            continue;
        if (!k1)
            k1 = i;
        else if (!k2)
            k2 = i;
        else
            return;
    }
    if (k1 == 0)
    {
        Init(dep, num);
        Sovle(dep + 1, num / 2, cnt);
        return;
    }
    if (k2 == 0)
    {
        Swap(a[k1][dep].num1, a[k1][dep].num2);
        Init(dep, num);
        Sovle(dep + 1, num / 2, cnt + 1);
        return;
    }
    int _a = a[k1][dep].num1, _b = a[k1][dep].num2;
    int _c = a[k2][dep].num1, _d = a[k2][dep].num2;
    Swap(a[k1][dep].num1, a[k2][dep].num1);
    if (Check(k1, dep) && Check(k2, dep))
    {
        Init(dep, num);
        Sovle(dep + 1, num / 2, cnt + 1);
    }
    a[k1][dep].num1 = _a;
    a[k2][dep].num1 = _c;

    Swap(a[k1][dep].num1, a[k2][dep].num2);
    if (Check(k1, dep) && Check(k2, dep))
    {
        Init(dep, num);
        Sovle(dep + 1, num / 2, cnt + 1);
    }
    a[k1][dep].num1 = _a;
    a[k2][dep].num2 = _d;

    Swap(a[k1][dep].num2, a[k2][dep].num1);
    if (Check(k1, dep) && Check(k2, dep))
    {
        Init(dep, num);
        Sovle(dep + 1, num / 2, cnt + 1);
    }
    a[k1][dep].num2 = _b;
    a[k2][dep].num1 = _c;

    Swap(a[k1][dep].num2, a[k2][dep].num2);
    if (Check(k1, dep) && Check(k2, dep))
    {
        Init(dep, num);
        Sovle(dep + 1, num / 2, cnt + 1);
    }
    a[k1][dep].num2 = _b;
    a[k2][dep].num2 = _d;

    return;
}
bool Check(int _x, int _dep)
{
    if (a[_x][_dep].num2 - a[_x][_dep].num1 == 1 && a[_x][_dep].num1 & 1)
        return true;
    return false;
}
void Init(int dep, int num)
{
    for (int i = 1; i <= num / 2; ++i)
    {
        a[i][dep + 1].num1 = a[i * 2 - 1][dep].num1 / 2 + 1;
        a[i][dep + 1].num2 = a[i * 2][dep].num1 / 2 + 1;
    }
    return;
}
template <typename T> void Swap(T& _a, T& _b)
{
    T _t = _a;
    _a = _b;
    _b = _t;
    return;
}
