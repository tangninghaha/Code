#include <cstdio>
#include <cstdlib>

/* Declaration */
int main();

/* Definition */
int main()
{
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; ++i)
    {
        printf("Test: %d/%d\n", i, t);
        system("gen.exe");
        system("A1.exe");
        system("bf.exe");
        if (system("fc trafficlight.out bf.out"))
        {
            printf("Wrong Answer!\n");
            system("pause");
            break;
        }
    }
}
