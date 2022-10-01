#include <iostream>
using namespace std;

int esPrimo(int n) {
	for (int x = 2; x < n / 2; x++) {
		if (n % x == 0) {
			return 0;
		}
	}
	return n;
}

long mill(unsigned long mill) {

    long long s{2};
    int i = 3;

    for (i; i < mill; i++) {
        esPrimo(i);
    }

}

int main()
{
    cout<<mill(10);
    return 0;
}
