#include <iostream>

using namespace std;

long npd() {
    
    long fin{2};
    long np{0};

    for (int i = 1; i < fin; i++) {

        int c{0};
        for (int j = 1; j <= 20; j ++) {
            if (i % j == 0) {
                c += 1;
            } else {
                break;
            }
        }

        if (c == 20) {
            np = i;
            break;
        }

        fin ++;
    }
    return np;
}

int main() {
    
    cout<<npd();

    return 0;
    
}