struct Q
{
    long long q;
    long long p; /* q/p */
    void Simplifcation();
};
bool operator<(Q &a, Q &b);
bool operator>(Q &a, Q &b);
template <typename Type> void Qsort(int l, int r, Type *a);

template <typename Type> void Qsort(int l, int r, Type *a)
{
    int i = l, j = r;
    Type mid = a[(l + r) >> 1];
    while (i <= j)
    {
        while (a[i] < mid)
            ++i;
        while (a[j] > mid)
            --j;
        if (i <= j)
        {
            swap(a[i], a[j]);
            ++i;
            --j;
        }
    }
    if (i < r)
        Qsort<Type>(i, r, a);
    if (l < j)
        Qsort<Type>(l, j, a);
    return;
}
void Q::Simplifcation()
{
    int t1 = q, t2 = p, t3 = q % p;
    while (t3)
    {
        t1 = t2;
        t2 = t3;
        t3 = t1 % t2;
    }
    q /= t2;
    p /= t2;
    return;
}
bool operator<(Q &a, Q &b)
{
    return a.q * b.p < b.q * a.p;
}
bool operator>(Q &a, Q &b)
{
    return a.q * b.p > b.q * a.p;
}
