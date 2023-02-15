#include <stdio.h>
const int MAXN = 1e5 + 5;
int num[MAXN * 2];
int sum_0[MAXN * 2], sum_1[MAXN * 2];

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= 2 * n; ++i)
    {
        scanf("%d", num[i]);
        if (num[i] == 1)
            sum_0[i] = sum_0[i - 1] + 1;
        else 
            sum_1[i] = sum_1[i - 1] + 1;
    }
    int sum_q, sum_h;
    for (int i = 1; i <= n; ++i)
    {
        if (num[i] == 1)
            sum_q += sum0[n] - sum0[i];
    }
    for (int i = n + 1; i <= 2 * n; ++i)
    {
        if (num[i] == 1)
            sum_h += sum0[2 * n] - sum0[i];
    }
    long long ed;
    ed = (long long) n * n;
    for (long long i = 0; i <= ed; ++i)
    {
        if (sum_q < i)
        {
            for (int j = 1; j <= n; ++j)
            {
            }
        }
    }
}
