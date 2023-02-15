#include <stdio.h>
#include <ctime>
#include <stdlib.h>

int main()
{
    freopen("report_travel.txt", "w", stdout);
    clock_t t_start, t1, t2;
    int t, wrongtest = 0;
    scanf("%d", &t);
    for (int i = 1; i <= t; ++i)
    {
        system("gen3.exe > in.txt");
        t_start = clock();
        system("Travel.exe < in.txt > out1.txt");
        t1 = clock();
        system("Travel2.exe < in.txt > out2.txt");
        t2 = clock();
        printf("Test: %d/%d\n", i, t);
        printf("Program1 Time: %.2lf\n", (double) (t1 - t_start) / 1000.0);
        printf("Program2 Time: %.2lf\n", (double) (t2 - t1) / 1000.0);
        if (system("fc out1.txt out2.txt"))
        {
            printf("Wrong Answer!\n");
            wrongtest++;
//            system("pause");
//            break;
        }
        if ((t2 - t1) / 1000.0 > 1)
        {
            printf("Time Limit!\n");
            system("pause");
            break;
        }
    }
    printf("Wrong Test: %d\n", wrongtest);
    printf("%.2lf", (1 - (1.0 * wrongtest / t)) * 100);
}
