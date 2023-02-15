#include <cstdio>
#include <stdlib.h>

/* Declaration */
int main();

/* Definition */
int main()
{
    int t;
    scanf("%d", &t);
    bool pd = false;
    for (int i = 1; i <= t; ++i)
    {
        printf("Test %d/%d:\n", i, t);
        system("gen.exe > in.txt");
        system("agnus.exe < in.txt > out1.txt");
        system("bf.exe < in.txt > out2.txt");
        if (system("fc out1.txt out2.txt"))
        {
            pd = true;
            printf("Wrong Answer!\n");
            system("pause");
            break;
        }
    }
    if (!pd)
        printf("Accept");
}
