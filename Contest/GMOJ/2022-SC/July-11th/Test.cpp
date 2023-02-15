#include <stdio.h>
const unsigned long long N = 1e17;
int main()
{
    unsigned long long ans2 = 0;
    for (unsigned long long i = 1; i <= 200000; ++i)
    {
        ans2 += i * i;
//        if (ans2 >= N)
//        {
//            ans1 += ans2 / N;
//            ans2 %= N;
//        }
        printf("%d: %017llu\n", i, ans2);
    }
}
