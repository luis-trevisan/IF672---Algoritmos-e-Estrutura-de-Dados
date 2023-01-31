#include <iostream>

using namespace std;

int main()
{
    int n, a = 0, b = 1, aux;

    cin >> n;

    while(n > 1) {
        aux = a + b;
        a = b;
        b = aux;
        n--;
    }

    cout << a << endl;

    return 0;
}

