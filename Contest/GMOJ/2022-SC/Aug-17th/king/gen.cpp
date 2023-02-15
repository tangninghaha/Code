#include <cstdio>
#include <stdlib.h>
#include <ctime>
int main()
{
    srand(time(0));
    printf("%d %d", rand() % 10 + 1, rand() % 25 + 1);
    return 0;
}
