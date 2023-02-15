#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    int t;
    scanf("%d", &t);
    clock_t x, a, b, c;
    bool pd = false;
    for (int i = 1; i <= t; ++i)
    {
        printf("Test: %d\n", i);
        x = clock();
        system("gen.exe > in.txt");
        a = clock();
        system("≈≈–Ú.exe < in.txt > out1.txt");
        b = clock();
        system("±©¡¶.exe < in.txt > out2.txt");
        c = clock();
        printf("Gen: Used Time: %.2lf\n", (a - x) / 1000.0);
        printf("Progrme 1: Used Time: %.2lf\n", (b - a) / 1000.0);
        printf("Progrme 2: Used Time: %.2lf\n", (c - b) / 1000.0);
        if (system("fc out1.txt out2.txt"))
        {
            printf("Wrong Answer\n");
            system("pause");
            pd = true;
            break;
        }
    }
    if (!pd)
    {
        printf("Accepted\n");
        system("pause");
    }
    return 0;
}
