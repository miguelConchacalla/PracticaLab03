#include <stdio.h>
#include <iostream>

using namespace std;

int esPrimo(int n) {
	for (int x = 2; x < n / 2; x++) {
		if (n % x == 0) {
			return 0;
		}
	}
	if (n % 2 != 0)
		return n;
}

int main()
{
	cout<<esPrimo(4);

	return 0;
}





















