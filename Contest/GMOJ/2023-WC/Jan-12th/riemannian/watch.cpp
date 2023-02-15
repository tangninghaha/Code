#include <cstdio>

/* Constant */
const int a[] = {0, 1, 5, 15, 43, 119, 327, 895, 2447, 6687, 18271, 49919, 136383, 372607, 1017983, 2781183};
const int b[] = {0, 2, 7, 21, 59, 163, 447, 1223, 3343, 9135, 24959, 68191, 186303,  508991, 1390591, 3799167};
const int P = 998244353;

/* Declaration */
int main()
{
    freopen("riemannian.in", "r", stdin);
    freopen("riemannian.out", "w", stdout);
    int t, n;
    scanf("%d", &t);
    int ans1 = 0, ans2 = 0;
    for (int i = 1; i <= t; ++i)
    {
        scanf("%d", &n);
        ans1 ^= (a[n] % P);
        ans2 ^= (b[n] % P);
    }
    printf("%d %d", ans1, ans2);
    return 0;
}
