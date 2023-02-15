#include <cstdio>
#define Max(a, b) a > b ? a : b
#define Min(a, b) a < b ? a : b

/* Constant */
const int mod = 998244353;
const int MAXN = 1e7 + 5;

/* Declaration */
int main();
bool Add(int);

/* Variable */
int x[MAXN];
int tot;

/* Definition */
int main()
{
    int n;
    scanf("%d", &n);
    int cnt = 1;
    int t = n;
    while (1)
    {
        if(Add(t % mod))
        {
            printf("%d", cnt);
            return 0;
        }
        ++cnt;
        t *= n;
        t %= mod;
    }
}
bool Add(int _x)
{
    int lbound = 0, rbound = tot - 1;
    int mid;
    int bg = 0;
    while (lbound <= rbound)
    {
        mid = (lbound + rbound) >> 1;
        if (x[mid] < _x)
        {
            lbound = mid + 1;
            bg = Max(mid + 1, bg);
        }
        else if (x[mid] == _x)
        {
            return true;
        }
        else
        {
            rbound = mid - 1;
            bg = Min(bg, mid);
        }
    }
    for (int i = tot; i >= bg; --i)
    {
        x[i + 1] = x[i];
    }
    ++tot;
    x[bg] = _x;
    return false;
}
