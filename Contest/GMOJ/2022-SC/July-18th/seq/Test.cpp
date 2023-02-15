#include <stdio.h>
void GetF(int x, int k, int nk)
{
    if (x <= k)
    {
        printf("+(f[%d])", x);
        return;
    }
    for (int i = 1; i <= nk; ++i)
    {
        GetF(x - i, k, nk - 1);
        printf("^b[%d]", nk);
    }
}
int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    GetF(n, k, k);
    return 0;
}
