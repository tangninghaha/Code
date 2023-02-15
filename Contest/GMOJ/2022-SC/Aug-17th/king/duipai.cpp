#include <cstdio>
#include <stdlib.h>

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        printf("Test: %d/%d\n", i, n);
        system("gen.exe > in.txt");
        system("king.exe < in.txt > out1.txt");
        system("bf.exe < in.txt > out2.txt");
        if (system("fc out1.txt out2.txt"))
        {
            printf("Wrong Answer!\n\n");
            system("pause");
            break;
        }
    }
}
