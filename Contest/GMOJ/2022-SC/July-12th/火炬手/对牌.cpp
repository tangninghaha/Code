#include <stdio.h>
#include <stdlib.h>
#include <ctime>
int main()
{
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; ++i)
    {
        system("gen.exe > in.txt");
        system("�����.exe < in.txt > out1.txt");
        system("���.exe < in.txt > out2.txt");
        if (system("fc out1.txt out2.txt"))
        {
            printf("Wrong Answer!\n");
            system("pause");
            break;
        }
    }
    return 0;
}
