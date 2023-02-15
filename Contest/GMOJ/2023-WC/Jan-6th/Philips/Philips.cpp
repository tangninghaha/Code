#include <cstdio>

/* Constant */
const int MAXP = 101;
const int PRIME[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
const int MAXS = 3e6 + 5;
const int INF = 1e8 + 5;

/* Declaration */
int main();
void Dfs(int, long long, bool);
int Min(int, int);
void Qsort(int, int);
void Swap(int&, int&);

/* Variable */
int l, r, p;
int s_tot;
int s[MAXS];
int f[MAXS];
bool pd[MAXS];

/* Definition */
int main()
{
    scanf("%d%d%d", &l, &r, &p);
    Dfs(0, 1, 1);
    ++s_tot;
    s[s_tot] = 1;
    int k = 1;
    int ans = 0;
    f[1] = 0;
    for (int i = 2; i <= s_tot; ++i)
    {
        f[i] = INF;
    }
    Qsort(1, s_tot);
    for (int i = 1; i <= p; ++i)
    {
        k = 1;
        for (int j = 1; j <= s_tot; ++j)
        {
//            if (pd[j])
//                continue;
            while (s[k] * i < s[j])
            {
                ++k;
            }
            if (s[k] * i == s[j])
            {
                f[j] = Min(f[j], f[k] + 1);
                if (f[j] + i <= p)
                {
//                    printf("%d\n", s[j]);
                    if (s[j] >= l && !pd[j])
                        ++ans;
                    pd[j] = true;
                }
            }
        }
    }
//    for (int i = 1; i <= s_tot; ++i)
//    {
//        if (!pd[i])
//        {
//            printf("%d\n", s[i]);
//        }
//    }
    printf("%d", ans);
    return 0;
}
void Dfs(int _x, long long num, bool flag)
{
    if (num > r)
    {
        return;
    }
    if (PRIME[_x] > p)
    {
        return;
    }
    if (!flag)
    {
        ++s_tot;
        s[s_tot] = num;
    }
    Dfs(_x, PRIME[_x] * num, 0);
    Dfs(_x + 1, num, 1);
    return;
}
int Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}
void Qsort(int _l, int _r)
{
    int i = _l, j = _r;
    int mid = s[(_l + _r) >> 1];
    while (i <= j)
    {
        while (s[i] < mid)
        {
            ++i;
        }
        while (s[j] > mid)
        {
            --j;
        }
        if (i <= j)
        {
            Swap(s[i], s[j]);
            ++i;
            --j;
        }
    }
    if (i < _r)
        Qsort(i, _r);
    if (_l < j)
        Qsort(_l, j);
    return;
}
void Swap(int& _a, int& _b)
{
    int t = _a;
    _a = _b;
    _b = t;
    return;
}
