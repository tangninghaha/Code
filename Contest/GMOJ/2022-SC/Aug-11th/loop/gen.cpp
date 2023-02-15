#include <cstdio>
#include <stdlib.h>
#include <ctime>
int main()
{
    srand(time(0));
    long long n, m;
    n = rand() % 2000 + 1001;
    m = rand() % 2000 + 1001;
    printf("%lld %lld", n, m);
    return 0;
}
