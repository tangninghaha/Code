#include <bits/stdc++.h>
template <typename T>
T read() {  // ���� template ��,Ҫ���ṩ���������T,���Դ����Ͷ����������� read()
  T sum = 0, fl = 1;  // �� sum,fl �� ch ����������Ͷ���
  int ch = getchar();
  for (; !isdigit(ch); ch = getchar())
    if (ch == '-') fl = -1;
  for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
  return sum * fl;
}
int main()
{
    int a;
    a = read<int>();
}
