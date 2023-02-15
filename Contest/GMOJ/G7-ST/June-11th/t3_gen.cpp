#include <stdio.h>
#include <ctime>
#include <stdlib.h>

int main()
{
    srand((unsigned) time(0));
    int n = 16;
    printf("%d\n", n);
    for (int i = 1; i <= n; i++)
    {
        int t = rand() % 15 + 1;
        printf("%d ", t);
    }
}
