#include <cstdio>
#include <cstdlib>
#include <ctime>

/* Constant */
const int mod = 1e9;

/* Declaration */
int main();

/* Definition */
int main()
{
    int n = 1000;
    srand(time(0));
    printf("%d\n", n);
    int t;
    for (int i = 1; i <= n; ++i)
    {
        t = rand() % mod + 1;
        if (t < 1e5)
        {
            t = (t * 1000 + rand() % mod + 1) % mod;
        }
        printf("%d ", t);
    }
    return 0;
}
