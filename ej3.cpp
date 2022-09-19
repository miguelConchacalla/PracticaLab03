#include <iostream>

using namespace std;

long factorm(long long n) {

    long long prod {1};
    long long may {0};

    for (long long i = 2; i <= n; i ++) {
        if (n % i == 0) {
            int c {0};

            if (i % 2 != 0) {
                for (long long j = 1; j <= i; j ++) {
                    if (i % j == 0) {
                        c += 1;
                    }
                }

                if (c == 2) {
                    may = i;
                    prod *= i;
                }
            }
            if (prod == n) {
                break;
            }
        }
    }
    return may;
}
int main()
{
    cout<<factorm(48);
    return 0;
}