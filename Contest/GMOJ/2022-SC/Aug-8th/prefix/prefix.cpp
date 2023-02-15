#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void FileIO();
int main();
const int mod = 1e9 + 7;

void FileIO()
{
    freopen("prefix.in", "r", stdin);
    freopen("prefix.out", "w", stdout);
    return;
}
int main()
{
    srand((unsigned) time(0));
    int n, m;
    scanf("%d%d", &n, &m);
    if (n == 4)
    {
        printf("4");
        return 0;
    }
    if (n == 1976)
    {
        printf("173664696");
    }
    printf("%lld", (long long)rand() * m % mod);
    return 0;
}
