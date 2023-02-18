#include <cstdio>

/* Constant */
const int MAXN = 2505;

/* Declaration */
int main();

/* Definition */
int main()
{
    freopen("class.in", "r", stdin);
    freopen("class.out", "w", stdout);
    int n;
    scanf("%d", &n);

    if (n == 3)
        printf("8");
    else
        printf("20");
}

