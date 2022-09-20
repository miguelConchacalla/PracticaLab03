#include <iostream>

using namespace std;

long lp(int n) {

    unsigned long pos;
    int ce{3};
    long i{2};
    for (i = 2; i < ce; i ++) {
        int ci{0};
        for (long j = 1; j <= i; j ++) {
            if (i % j == 0) {
                ci += 1;
            }
        }
        if (ci == 2) {
            pos += 1;
        }
        if (pos == n) {
            break;
        }
        ce++;
    }

    return i;

}

int main()
{
    cout<<lp(10001);
    return 0;
}