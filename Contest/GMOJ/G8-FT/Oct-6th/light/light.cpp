#include <cstdio>

/* Constant */
const int N = 400;

/* Declaration */
int main();
bool Check(int, int, int, int);
int Min(int, int);

/* Variable */
int a, b, c, d;

/* Definition */
int main()
{
    freopen("light.in", "r", stdin);
    freopen("light.out", "w", stdout);

    scanf("%d%d%d%d", &a, &b, &c, &d);
    int lbound, rbound, l4;
    int ans = 5e8 + 5;
    for (int l1 = 0; l1 <= a; ++l1)
    {
        if (Check(l1, 0, 0, 0))
        {
            ans = Min(ans, l1);
            break;
        }
        for (int l2 = 0; l2 <= b; ++l2)
        {
            if (Check(l1, l2, 0, 0))
            {
                ans = Min(ans, l1 + l2);
                break;
            }
            for (int l3 = 0; l3 <= c; ++l3)
            {fda
                if (Check(l1, l2, l3, 0))
                {
                    ans = Min(ans, l1 + l2 + l3);
                    break;
                }
                lbound = 0;
                rbound = d;
                while (lbound <= rbound)
                {
                    l4 = (lbound + rbound) >> 1;
                    if (Check(l1, l2, l3, l4))
                    {
                        ans = Min(ans, l1 + l2 + l3 + l4);
//                        printf("%d %d %d %d %d\n", l1, l2, l3, l4, l1 + l2 + l3 + l4);
                        rbound = l4 - 1;
                    }
                    else
                    {
                        lbound = l4 + 1;
                    }
                }
            }
        }
    }
    printf("%d", ans);
    return 0;
}
bool Check(int l1, int l2, int l3, int l4)
{
    if (l1 + l2 / 2 + l3 / 2 + l4 / 4 >= a)
    {
        if (l1 / 2 + l2 + l3 / 4 + l4 / 2 >= b)
        {
            if (l1 / 2 + l2 / 4 + l3 + l4 / 2 >= c)
            {
                if (l1 / 4 + l2 / 2 + l3 / 2 + l4 >= d)
                {
                    return true;
                }
                return false;
            }
            return false;
        }
        return false;
    }
    return false;
}
int Min(int _a, int _b)
{
    return _a < _b ? _a : _b;
}
