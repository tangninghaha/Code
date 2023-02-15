#include <cstdio>
#include <cstdlib>
#include <ctime>

/* Constant */
const int N = 1e5;
const int M = 1e5;
const int mod = 1e5;

/* Declaration */
int main();

/* Defintion */
int main()
{
    freopen("trafficlight.in", "w", stdout);
    srand(time(0));
    printf("%d %d\n", N, M);
    int t;
    for (int i = 1; i <= M; ++i)
    {
        t = rand() % mod + 1;
        printf("%d ", i + 1);
    }
}
