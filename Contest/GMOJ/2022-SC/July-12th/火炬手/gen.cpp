#include <stdio.h>
#include <stdlib.h>
#include <ctime>

int main()
{
    srand(time(0));
    printf("%d", rand() % 100000);
}
