#include <cstdio>
#include <cstdlib>

int main()
{
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; ++i)
    {
        printf("Test: %d/%d\n", i, t);
        system("gen.exe > in.txt");
        system("history.exe < in.txt > out1.txt");
        system("bf.exe < in.txt > out2.txt");
        if (system("fc out1.txt out2.txt"))
        {
            printf("Wrong Answer!\n");
            system("pause");
            return 0;
        }
    }
    printf("Accepted\n");
    system("pause");
    return 0;
}
