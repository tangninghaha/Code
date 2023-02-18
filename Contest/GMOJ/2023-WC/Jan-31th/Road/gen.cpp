#include <cstdio>
#include <cstdlib>
#include <ctime>

/* Variable */
const int C = 5e4;

/* Declaration */
int main();

/* Definition */
int main()
{
    srand(time(0));
    int n = 10;
    int q = 10;
    
    printf("%d\n", n);
    for (int i = 1; i <= n; ++i)
    {
        printf("%d ", rand() % C + 1); 
    }
    printf("\n");
    int x;
    for (int i = 2; i <= n; ++i)
    {
        x = rand() % (i - 1) + 1;
        printf("%d %d\n", x, i);
    }
    printf("%d\n", q);
    for (int i = 1; i <= q; ++i)
    {
        printf("%d %d\n", rand() % n + 1, rand() % n + 1);
    }
    return 0;
}

