#include <cstdio>

/* Constant */
const int MAXN = 1500;

/* Declaration */
int main();
bool Check(int);

/* Variable */
int a, b, c, d;

/* Definition */
int main()
{
    scanf("%d%d%d%d", &a, &b, &c, &d);
    int lbound = 0, rbound = 4 * MAXN;
    int sum;
    int ans = 0;
    while (lbound <= rbound)
    {
        sum = (lbound + rbound) >> 1;
        if (Check(sum))
        {
            ans = sum;
            rbound = sum - 1;
        }
        else
        {
            lbound = sum + 1;
        }
    }
    printf("%d", ans);
    return 0;
}
bool Check(int sum)
{
    int _a = 0, _b = 0, _c = 0, _d = 0;
    int lbound, rbound;
    int l2, l3;
    int more;
    for (int l1 = 0; l1 <= MAXN; ++l1)
    {
        for (int l4 = 0; l4 <= MAXN; ++l4)
        {
            if (l1 + l4 > sum)
                break;
            more = sum - l1 - l4;
            _a = l1 + l4 / 4 + more / 2;
            _d = l4 + l1 / 4 + more / 2;
            if (_a < a || _d < d)
                continue;
            lbound = 0;
            rbound = more;
            while (lbound <= rbound)
            {
                l2 = lbound + rbound >> 1;
                l3 = more - l2;
                _b = l1 / 2 + l2 + l3 / 4 + l4 / 2;
                _c = l1 / 2 + l2 / 4 + l3 + l4 / 2;
                if (_b < b)
                {
                    lbound = l2 + 1;
                }
                else
                {
                    if (_c >= c)
                    {
                        return true;
                    }
                    rbound = l2 - 1;
                }
            }
        }
    }
    return false;
}
