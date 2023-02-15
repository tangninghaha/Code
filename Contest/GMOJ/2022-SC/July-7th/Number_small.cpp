#include <stdio.h>

const int MAXP = 32768, MAXPNUM = 5010, MAXN = 16, MAXQ = 3e7 + 10;
const long long MAXANS = 1e5;

bool pd[MAXP];
int prime[MAXPNUM], tot_prime;
void Init();
long long a[MAXN];
void Qsort(long long a[], int l, int r);
void swap(long long &a, long long &b);
void swap_int(int &a, int &b);
long long min(long long a, long long b);

int n, k;
struct Queue
{
    Queue();
    int size;
    long long num[MAXQ];
    void up(int x);
    void down(int x);
    bool empty();
    void push(long long &nums);
    void pop();
    long long front();
};
void Bfs();
long long gcd(long long a, long long b);
Queue q;

int main()
{
    Init();
    scanf("%d%d", &n, &k);
    long long ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", &a[i]);
    }
    // Qsort(a, 1, n);
    Bfs();
    return 0;
}

Queue::Queue()
{
    size = 0;
}
void Queue::up(int x)
{
    int nxt = x / 2;
    while (nxt >= 1 && num[nxt] > num[x])
    {
        swap(num[x], num[nxt]);
        x = nxt;
        nxt = x / 2;
    }
    return;
}
void Queue::down(int x)
{
    int nxt = x * 2;
    while ((nxt <= size && num[nxt] < num[x]) || (nxt + 1 <= size && num[nxt + 1] < num[x]))
    {
        if (num[nxt + 1] < num[nxt] && nxt + 1 <= size) ++nxt;
        swap(num[nxt], num[x]);
        x = nxt;
        nxt = x * 2;
    }
    return;
}
bool Queue::empty()
{
    return !size;
}
void Queue::push(long long &nums)
{
    size++;
    num[size] = nums;
    up(size);
    return;
}
void Queue::pop()
{
    swap(num[1], num[size]);
    size--;
    down(1);
    return;
}
long long Queue::front()
{
    return num[1];
}

void Bfs()
{
    bool pd = 0;
    int k_used = 0;
    long long nxt = 0;
    for (int i = 1; i<= n; ++i)
    {
        for (int j = 1; j <= MAXANS; ++j)
       {
            pd = 0;
            nxt = a[i] * j;
            if (nxt > MAXANS) break;
            for (int k = 1; k <= n; ++k)
            {
                if (gcd(nxt, a[k]) == a[k] && i != k)
                {
                    pd = 1;
                    break;
                }
            }
            if (!pd)
            {
                q.push(nxt);
            }
        }
    }
    long long now;
    int lbelong;
    while (!q.empty())
    {
        now = q.front();
        while (q.num[2] == now || q.num[3] == now)
        {
            q.pop();
            now = q.front();
        }
        ++k_used;
        // printf("%d %lld\n", k_used, now);
        if (k_used == k)
        {
            printf("%lld", now);
            return;
        }
        q.pop();
    }
}
void Init()
{
    for (int i = 2; i <= MAXP; ++i)
    {
        if (!pd[i])
        {
            ++tot_prime;
            prime[tot_prime] = i;
        }
        for (int j = 1; j <= tot_prime; ++j)
        {
            if (prime[j] * i >= MAXP)
                break;
            pd[prime[j] * i] = 1;
            if (!(i % prime[j]))
                break;
        }
    }
}

void Qsort(long long a[], int l, int r)
{
    int i = l, j = r;
    long long mid = a[(l + r) >> 1];
    while (i < j)
    {
        while (a[i] < mid) i++;
        while (a[j] > mid) j--;
        if (i <= j)
        {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }
    if (i < r) Qsort(a, i, r);
    if (l < j) Qsort(a, l, j);
    return;
}
void swap(long long &a, long long &b)
{
    long long t = a;
    a = b;
    b = t;
    return;
}
long long min(long long a, long long b)
{
    return a < b ? a : b;
}
long long gcd(long long a, long long b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
void swap_int(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
    return;
}

