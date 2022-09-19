#include <iostream>

using namespace std;

int mul(int n, int m, int ult) {
    
    int s;

    for (int i = 0; i < ult; i ++) {
        if (i % n == 0 || i % m == 0) {
            s += i;
        }
    }

    return s;
}

int main()
{
    cout<<mul(3, 5, 1000);
    return 0;
}
