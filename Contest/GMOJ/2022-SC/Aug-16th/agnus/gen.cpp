#include <cstdio>
#include <stdlib.h>
#include <ctime>

/* Declaration */
int main();

/* Definition */
int main()
{
    srand((unsigned)time(0));
    bool pd = false;
    int ed = rand() % 2000 + 1000;
    for (int i = 1; i < ed; ++i)
    {
        if (!(rand() % 5))
        {
            pd = true;
            printf("agnus");
        }
        else
        {
            printf("%c", rand() % 26 + 'a');
        }
    }
    if (!pd)
    {
        printf("agnus");
    }
    return 0;
}
