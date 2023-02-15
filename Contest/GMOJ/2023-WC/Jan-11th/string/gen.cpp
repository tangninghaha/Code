#include <ctime>
#include <cstdlib>
#include <cstdio>

/* Declaration */
int main();

/* Definition */
int main()
{
    srand(time(0));
    int n = 20;
    int t = 0;
    for (int i = 1; i <= n; i += t)
    {
        t = rand() % 5 + 1;
        if (rand() % 2 == 0)
            t = 1;
        char x = 'a' + rand() % 26;
        for (int j = 1; j <= t; ++j)
        {
            printf("%c", x);
        }
    }
    return 0;
}
