#include <stdlib.h>
#include <cstdio>
int main()
{
    int t;
    bool pd;
    scanf("%d", &t);
    for (int i = 1; i <= t; ++i)
    {
        printf("Test: %d/%d\n", i, t);
        system("gen.exe > in.txt");
        system("bf.exe < in.txt > out1.txt");
        system("loop.exe < in.txt > out2.txt");
        if (system("fc out1.txt out2.txt"))
        {
            pd = true;
            printf("Wrong Answer!\n");
            system("pause");
            break;
        }
    }
    if (!pd)
    {
        printf("AC");
    }
}
