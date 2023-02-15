#include <stdio.h>
#include <stdlib.h>
int main()
{
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; ++i)
    {
        printf("Test: %d/%d\n", i, t);
        system("gen.exe > in.txt");
        system("happiness_force.exe < in.txt > out1.txt");
        system("happiness.exe < in.txt > out2.txt");
        if (system("fc out1.txt out2.txt"))
        {
            printf("Wrong Answer!\n");
            system("pause");
            return 1;
        }
    }
    printf("No Different Found\n");
    system("pause");
    return 0;
}
