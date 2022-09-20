#include <iostream>

using namespace std;


long mill(unsigned long mill)
{
    unsigned long long i;
    unsigned long long j;
    unsigned long long s;

    for (i = 1; i < mill; i ++) {
        unsigned long long ci{0};
        for (j = 1; j <= i; j ++) {
            if (i % j == 0) {
                ci += 1;
            }
        }
        if (ci == 2) {
            s += i;
        } 
    }
    return s;
}

int main()
{
    cout<<mill(1000000);
    return 0;
}
