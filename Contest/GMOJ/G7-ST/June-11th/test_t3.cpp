#include <stdio.h>
#include <ctime>
#include <stdlib.h>

int main()
{
    int t;
    scanf ("%d", &t);
    clock_t a, b;
    for (int i = 1; i <= t; i++)
    {
        printf ("Test: %d / %d\n", i, t);
        system("t3_gen.exe > in.txt");
        a = clock();
        system("t3.exe < in.txt > out.txt");
        b = clock();
        printf("%lf\n", (b - a) / 1500.0);
        if ((b - a) / 1000.0 > 1.0)
        {
            printf ("TLE!\n\n");
            system("pause");
            break;
        }
    }
}
