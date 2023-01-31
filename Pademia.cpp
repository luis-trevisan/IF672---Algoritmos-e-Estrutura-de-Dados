#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct heap {
    int ID;
    int casos;
} heap;

heap *heap_extract(heap *, int, int &, int *);
heap *bublle_up(heap *, int, int *);
heap *bubble_down(heap *, int, int, int *);

int main(void)
{
    heap *c, aux;
    string input;
    int *posicao_c, size, heap_size, temp, aux_temp;

    cin >> size;

    c = (heap *) malloc(size * sizeof(heap));
    posicao_c = (int *) malloc(2 * size * sizeof(int));

    heap_size = size;

    for (int i = 0; i < size; i++) {
        c[i].ID = i;
        posicao_c[i] = i;
        cin >> c[i].casos;
    }

    for (int i = (size / 2) - 1; i >= 0; i--) {
        c = bubble_down(c, i, heap_size, posicao_c);
    }

    cin >> ws;

    while (input[0] != 'E') {
        getline(cin, input);

        if (input[0] == 'N') {
            if (size == heap_size) {
                size *= 2;
                c = (heap *) realloc(c, size * sizeof(heap));

                if(c == nullptr) {
                    exit(1);
                }

                posicao_c = (int *) realloc(posicao_c, 2 * size * sizeof(int));

                if(posicao_c == nullptr) {
                    exit(1);
                }
            }

            aux.ID = stoi(input.substr(4));
            aux.casos = stoi(input.substr(input.rfind(' ')));

            c[heap_size] = aux;
            posicao_c[aux.ID] = heap_size;
            heap_size++;

            c = bublle_up(c, heap_size - 1, posicao_c);

            if(heap_size != 0) {
                cout << c[0].ID << ' ' << c[0].casos << '\n';
            }
            else {
                cout << "-1 -1\n";
            }
        }
        else if (input[0] == 'D') {
            aux.ID = stoi(input.substr(4));

            c = heap_extract(c, posicao_c[aux.ID], heap_size, posicao_c);

            if(heap_size != 0) {
                cout << c[0].ID << ' ' << c[0].casos << '\n';
            }
            else {
                cout << "-1 -1\n";
            }
        }
        else if (input[0] == 'I') {
            aux.ID = stoi(input.substr(3));
            aux.casos = stoi(input.substr(input.rfind(' ')));

            c[posicao_c[aux.ID]].casos += aux.casos;
            cout <<  c[posicao_c[aux.ID]].casos << '\n';
            c = bublle_up(c, posicao_c[aux.ID], posicao_c);
        }
        else if (input[0] == 'O') {
            aux.ID = stoi(input.substr(4));
            aux.casos = stoi(input.substr(input.rfind(' ')));

            c[posicao_c[aux.ID]].casos -= aux.casos;
            cout <<  c[posicao_c[aux.ID]].casos << '\n';
            c = bubble_down(c, posicao_c[aux.ID], heap_size, posicao_c);
        }
        else if (input[0] == 'P') {
            temp = stoi(input.substr(4));
            aux_temp = 0;

            while(c[0].casos > 0 && temp > 0) {
                c[0].casos--;
                aux_temp++;

                if(c[0].casos <= c[1].casos || c[0].casos <= c[2].casos) {
                    c = bubble_down(c, 0, heap_size, posicao_c);
                }

                temp--;
            }

            cout << aux_temp << '\n';
        }
    }

    temp = 0;

    for (int i = 0; i < heap_size; i++) {
        temp += c[i].casos;
    }

    cout << temp << '\n';

    free(c);
    free(posicao_c);

    return 0;
}

heap *heap_extract(heap *h, int p, int &heap_size, int *posicao_c) {
    heap temp;
    int aux;

    aux = posicao_c[h[p].ID];
    posicao_c[h[p].ID] = posicao_c[h[heap_size - 1].ID];
    posicao_c[h[heap_size - 1].ID] = aux;

    temp = h[p];
    h[p] = h[heap_size - 1];
    h[heap_size - 1] = temp;

    heap_size--;

    h = bubble_down(h, p, heap_size, posicao_c);

    return h;
}

heap *bublle_up(heap *h, int p, int *posicao_c) {
    int i, aux, h_i, h_pai;
    heap temp;

    i = p;
    h_i = h[i].ID;
    h_pai = h[(i - 1) / 2].ID;

    while (i > 0 && h[i].casos >= h[(i - 1) / 2].casos) {
        aux = posicao_c[h_i];
        posicao_c[h_i] = posicao_c[h_pai];
        posicao_c[h_pai] = aux;

        temp = h[i];
        h[i] = h[(i - 1) / 2];
        h[(i - 1) / 2] = temp;

        i = (i - 1) / 2;
        h_i = h[i].ID;
        h_pai = h[(i - 1) / 2].ID;
    }

    return h;
}

heap *bubble_down(heap *h, int p, int heap_size, int *posicao_c) {
    int l, r, m, aux, h_p, h_m;
    heap temp;

    m = p;
    h_p = h[p].ID;
    h_m = h[m].ID;
    l = 2 * p + 1;
    r = 2 * p + 2;

    if (l < heap_size && (h[l].casos > h[m].casos || (h[l].casos == h[m].casos && h[l].ID > h[m].ID))) {
        m = l;
        h_m = h[l].ID;
    }
    if (r < heap_size && (h[r].casos > h[m].casos || (h[r].casos == h[m].casos && h[r].ID > h[m].ID))) {
        m = r;
        h_m = h[r].ID;
    }
    if (m != p) {
        aux = posicao_c[h_m];
        posicao_c[h_m] = posicao_c[h_p];
        posicao_c[h_p] = aux;

        temp = h[m];
        h[m] = h[p];
        h[p] = temp;

        return bubble_down(h, m, heap_size, posicao_c);
    }

    return h;
}
