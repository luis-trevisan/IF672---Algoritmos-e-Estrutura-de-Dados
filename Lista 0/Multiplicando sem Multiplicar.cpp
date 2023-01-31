#include <iostream>


using namespace std;

int main()
{
    int a=-2, b=-2, aux;

    cin >> a;
    cin >> b;

    if(a == 0 || b == 0)
        cout << "0\n";
    else {
        if(b < 0) {
            b = b - b - b;
            a = a - a - a;
        }

        aux = a;

        while(b > 1) {
            a += aux;
            b--;
        }

        cout << a << endl;
    }

    return 0;
}
