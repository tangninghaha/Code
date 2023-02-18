#include <cstdio>
#include <cstdlib>

/* Declaration */
int main();

/* Definition */
int main()
{
    int t;
    scanf("%d", &t);
    for (int fot = 1; fot <= t; ++fot)
    {
        system("gen.exe > in.txt");
        system("bf.exe < in.txt > out1.txt");
        system("road.exe < in.txt > out2.txt");
        if (system("fc out1.txt out2.txt"))
        {
            printf("Wrong Answer\n");
            system("pause");
            system("pause");
            return 0;
        }
    }
    printf("Accept");
    system("pause");
    return 0;
}
