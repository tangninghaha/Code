#include <cstdio>
#include <cstdlib>

int main()
{
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; ++i)
    {
        printf("%d/%d\n", i, t);
        system("gen.exe > in.txt");
        system("string.exe < in.txt > out.txt");
        system("bf.exe < in.txt > out2.txt");
        if (system("fc out.txt out2.txt"))
        {
            system("pause");
            break;
        }
    }
    return 0;
}
