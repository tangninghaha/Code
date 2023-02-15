#include <cstdio>
#include <ctime>
#include <cstdlib>

/* Constant */
const int N = 1e6;

/* Declaration */
int main();

/* Variable */
int a[N + 5];

/* Definition */
int main()
{
    srand(time(0));
    freopen("interval.in", "w", stdout);
    printf("%d", N);
    for (int i = 1; i <= N; ++i)
    {
        a[i] = rand() % N;
    }
    Qsort(1, n);
}
