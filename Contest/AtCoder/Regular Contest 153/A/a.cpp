#include <cstdio>

/* Constant */
const int N = 10;

/* Declaration */
int main();

/* Variable */
int s[N];

/* Definition */

int main()
{
    int n;
    scanf("%d", &n);
    s[1] = 1;
    s[2] = 1;
    for (int i = 2; i <= n; ++i)
    {
        ++s[8];
        if (s[8] == 10)
        {
            ++s[9];
            ++s[7];
            s[8] = 0;
            if (s[9] == 10)
            {
                s[9] = s[7] = 0;
                ++s[6];
                ++s[5];
                if (s[6] == 10)
                {
                    s[6] = 0;
                    s[5] = 0;
                    ++s[4];
                    if (s[4] == 10)
                    {
                        s[4] = 0;
                        ++s[3];
                        if (s[3] == 10)
                        {
                            s[3] = 0;
                            ++s[1];
                            ++s[2];
                        }
                    }
                }
            }
        }
    }
    for (int i = 1; i <= 9; ++i)
        printf("%d", s[i]);
}
