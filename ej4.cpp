#include <iostream>

using namespace std;

int palin(int n) {
    long pm = 0;
    for (long i = 1; i <= 99; i ++) {
        for (long j = 1; j <= 99; j ++) {
            long nm = i * j;

            int arreglo[10];
            int c{1};
            int i;
            for (i = 0; i < c; i ++) {
                if (nm > 0) {
                    arreglo[i] = nm % 10;
                    nm /= 10;
                    c ++;
                } else {
                    break;
                }
            }
            for (int j = i - 1; j >= 0; j --) {
                arreglo[j];
            }
        }
    }
    return pm;
}

int main()
{
    cout<<palin(9009);
    return 0;
}