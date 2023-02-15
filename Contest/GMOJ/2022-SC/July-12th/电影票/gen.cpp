#include <stdio.h>
#include <stdlib.h>
#include <ctime>

int main()
{
    srand(time(0));
    int a = rand() % 5000 + 1, b = rand() % 5000 + 1;
    if (b > a)
    {
        int t = b;
        b = a;
        a = t;
    }
    printf("%d %d", a, b);
}
