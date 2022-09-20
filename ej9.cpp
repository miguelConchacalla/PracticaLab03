#include <iostream>

using namespace std;


double tp()
{
    double a, b, c;
    double ce{0.02};
    double cm{0.02};
    double ci{0.02};

    for (a = 0.01; a < 12; a += 0.01) {
        for (b = 0.01; b < 12; b += 0.01) {
            for (c = 0.01; c < 12; c += 0.01) {
                if ((a + b + c) == 12) {
                    if (c = ((a * a) + (b * b))/ c) {
                        return a * b * c;
                    }
                }
                ci += 0.01;
            }
            cm += 0.01;
        }
        ce += 0.01;
    }
}

int main()
{
    cout<<tp();
    return 0;
}
