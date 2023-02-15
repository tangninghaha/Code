#include <cstdio>
#include <cstdlib>
#include <ctime>

/* Declaration */
int main();

/* Definition */
int main()
{
    int t;
    scanf("%d", &t);
    clock_t t1, t2, t3;
    double time1, time2;
    for (int i = 1; i <= t; ++i)
    {
        printf("%d/%d\n\n", i, t);
        system("gen.exe > in.txt");
        t1 = clock();
        system("way1.exe < in.txt > out1.txt");
        t2 = clock();
        system("way2.exe < in.txt > out2.txt");
        t3 = clock();
        time1 = (double)(t2 - t1) / CLOCKS_PER_SEC;
        time2 = (double)(t3 - t2) / CLOCKS_PER_SEC;
        printf("Program 1 used: %.2lf\n", time1);
        printf("Program 2 used: %.2lf\n", time2);
        if (time1 > 1.0)
        {
            printf("Time Limit Exceeded!\n");
            system("pause");
            system("pause");
            return 1;
        }
        if (system("fc out1.txt out2.txt"))
        {
            printf("Oh SAD!\n");
            system("pause");
            system("pause");
            return 1;
        }
    }
    printf("Accept");
    return 0;
}
