#include <iostream>

using namespace std;

long fibonaci(long vm) {

    long long in{1};
    long long fin{2};
    long long s{0};
    long long c{2};

    for (long long i = 1; i < c; i ++) {
        if (fin < vm) {
            long long temp = in + fin;    
            in = fin;               
            fin = temp;
            if (in % 2 == 0) {
                s += in;
            }
        } else {
            break;
        }
        c += 1;
    }

    return s;
}

int main()
{
    cout << fibonaci(4000000);
    return 0;
}