#include <iostream>

using namespace std;

long dc(int n) {
    unsigned long sc;
    unsigned long cs;
    unsigned long r;

    for (int i = 1; i <= n; i ++) {
        sc += i * i;
        cs += i;
    }
    cs *= cs;

    return cs - sc;
}

int main()
{
    cout<<dc(100);
    return 0;
}