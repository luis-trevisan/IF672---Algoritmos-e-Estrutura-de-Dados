#include <iostream>

using namespace std;

int main()
{ 
    int n, lista_jogo_da_velha[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    cin >> n;

    string palavras[n], Q[n];

    for(int i = 0; i < n; i++)
        cin >> palavras[i];

    for(int i = 0; i < n; i++)
        cin >> Q[i];

    for(int aux = 0; aux < n; aux++) {
        for(int k = 0; k < Q[aux].length(); k++) {
            if(Q[aux].find("#", k) == 0)
                for(int i = 0; i < 10; i++)
                    for(int j = 0; j < n; j++)
                        cout << lista_jogo_da_velha[i] << palavras[j] << endl;

            if(Q[aux].find("X", k) == 0)
                for(int i = 0; i < n; i++)
                    for(int j = 0; j < 10; j++)
                        cout << palavras[i] << lista_jogo_da_velha[j] << endl;
        }
    }

    return 0;
}