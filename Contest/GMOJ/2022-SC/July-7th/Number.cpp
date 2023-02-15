#include <stdio.h>

const int MAXP = 40010, MAXPNUM = 5010, MAXN = 16, MAXQ = 3e6 + 10;
const long long MAXANS = 1e15;

bool pd[MAXP];
int prime[MAXPNUM], tot_prime;
void Init();
long long a[MAXN];
struct PrimeSon
{
    int son[MAXPNUM];
    int spson;
    void GetSon(long long x);
};
PrimeSon ason[MAXN];
void Qsort(long long a[], int l, int r);
void swap(long long &a, long long &b);
void swap_int(int &a, int &b);
long long min(long long a, long long b);

const int mod = 19491001;
long long hash[mod];

int n, k;
struct Queue
{
    Queue();
    int size;
    long long num[MAXQ];
    int belong[MAXQ];
    void up(int x);
    void down(int x);
    bool empty();
    void push(long long &nums, int belongs);
    void pop();
    long long front();
    int front_belong();
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
//    Qsort(a, 1, n);
    for (int i = 1; i <= n; ++i)
    {
        ason[i].GetSon(a[i]);
    }
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
        swap_int(belong[x], belong[nxt]);
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
        swap_int(belong[nxt], belong[x]);
        x = nxt;
        nxt = x * 2;
    }
    return;
}
bool Queue::empty()
{
    return !size;
}
void Queue::push(long long &nums, int belongs)
{
    size++;
    num[size] = nums;
    belong[size] = belongs;
    up(size);
    return;
}
void Queue::pop()
{
    swap(num[1], num[size]);
    swap_int(belong[1], belong[size]);
    size--;
    down(1);
    return;
}
long long Queue::front()
{
    return num[1];
}
int Queue::front_belong()
{
    return belong[1];
}

void Bfs()
{
    bool pd = 0;
    int k_used = 0;
    for (int i = 1; i<= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (gcd(a[i], a[j]) == a[j] && i != j)
            {
                pd = 1;
                break;
            }
        }
        if (!pd)
        {
            q.push(a[i], i);
        }
    }
    long long now, nxt;
    int lbelong;
    while (!q.empty())
    {
        now = q.front();
        while (q.num[2] == now || q.num[3] == now)
        {
            q.pop();
            now = q.front();
        }
        lbelong = q.front_belong();
        ++k_used;
        // printf("%d %lld\n", k_used, now);
        if (k_used == k)
        {
            printf("%lld", now);
            return;
        }
        q.pop();
        for (int i = 1; i <= tot_prime; ++i)
        {
            nxt = now * prime[i];
            if (nxt > MAXANS) break;
            pd = 0;
            for (int j = 1; j <= n; ++j)
            {
                if (gcd(nxt, a[j]) == a[j] && j != lbelong)
                {
                    pd = 1;
                    break;
                }
            }
            if (!pd)
            {
                q.push(nxt, lbelong);
            }
        }
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

void PrimeSon::GetSon(long long x)
{
    spson = 0;
    for (int i = 1; i <= tot_prime; ++i)
    {
        while (!(x % prime[i]))
        {
            son[i]++;
            x /= prime[i];
        }
        if (x == 1)
            break;
    }
    if (x != 1)
    {
        spson = x;
    }
    return;
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

