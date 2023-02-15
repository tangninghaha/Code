#include <cstdio>

/* Constant */
const int MAXN = 1e5 + 5;
const int MAXM = 1e5 + 5;

/* Declaration */
int main();
void FileIO();
int Check(int n, int t);
int Abs(int x_);

/* Variable  */
int p[MAXN];

/* Defintion */
int main()
{
    FileIO();
    int n, m;
    scanf("%d%d", &n, &m);
    char cha;
    for (int i = 1; i <= n; ++i)
    {
        cha = getchar();
        while (cha != '0' && cha != '1')
        {
            cha = getchar();
        }
        p[i] = cha - '0';
    }
    int lbound = 0, rbound = n;
    int mid, ret;
    int ans = 0;
    while (lbound <= rbound)
    {
        mid = (lbound + rbound) >> 1;
        ret = Check(n, mid);
        if (ret > m)
        {
            lbound = mid + 1;
        }
        else
        {
            ans = mid;
            rbound = mid - 1;
        }
    }
    int nan = 0, nv = 0;
    int last = 0;
    for (int i = n; i >= 1; --i)
    {
        if (p[i] == 0)
        {
            ++nv;
        }
        else
        {
            ++nan;
        }
        if (Abs(nan - nv) == ans)
        {
            printf("%d ", i - last);
            if (nan > nv + ans)
            {
                nan -= nv + ans;
            }
            else
            {
                nv -= nan + ans;
            }
        }
    }
    printf("\n");
    nan = 0;
    nv = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (p[i] == 0)
        {
            ++nv;
        }
        else
        {
            ++nan;
        }
        if (Abs(nan - nv) == ans)
        {
            printf("%d ", i - last);
            if (nan > nv + ans)
            {
                nan -= nv + ans;
            }
            else
            {
                nv -= nan + ans;
            }
        }
    }
    return 0;
}
int Check(int n, int t)
{
    int ret = 0;
    int nan = 0, nv = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (p[i] == 0)
        {
            ++nv;
        }
        else
        {
            ++nan;
        }
        if (Abs(nan - nv) >= t)
        {
            ++ret;
            if (nan > nv + t)
            {
                nan -= nv + t;
            }
            else
            {
                nv -= nan + t;
            }
        }
    }
    return ret;
}
int Abs(int x_)
{
    return x_ > 0 ? x_ : -x_;
}
void FileIO()
{
    freopen("villa.in", "r", stdin);
    freopen("villa.out", "w", stdout);
    return;
}
