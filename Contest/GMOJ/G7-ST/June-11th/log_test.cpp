#include <stdio.h>
#include <cmath>

int main()
{
    int num = 1000000, ans;
    while (num != 1)
    {
        num /= 2;
        ans++;
    }
    printf("%d %d", ans, (int)pow(2, ans));
}
