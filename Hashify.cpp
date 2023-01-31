#include <iostream>
#include <string>

using namespace std;

class hash_table {
    public:
        void set_name(string name) {
            this -> music_name = name;
        }

        string get_name(void) {
            return this -> music_name;
        }

        void set_time(int time) {
            this -> music_time = time;
        }

        int get_time(void) {
            return this -> music_time;
        }

        void set_repeat(int value) {
            this -> number_of_repeat = value;
        }

        int get_repeat(void) {
            return this -> number_of_repeat;
        }

        void add_repeat(void) {
            this -> number_of_repeat += this -> music_time;
        }

    private:
        string music_name;
        int music_time;
        int number_of_repeat = -1;
};

int key(string &);
int hash_function(hash_table *, string &, int &, int &, int &);
int search(hash_table *, string &,int &, int &);
void rehash(hash_table **, int &);

int main(void)
{
    int m, time, c, h, aux;
    float n = 0.0;
    hash_table *music_playlist;
    string input, music_name;

    cin >> m;
    music_playlist = new hash_table[m];

    while(input[0] != 'E') {
        getline(cin, input);

        if(input[0] == 'A') {
            if(n / m >= 0.5) {
                rehash(&music_playlist, m);
            }

            music_name = input.substr(4, input.rfind(' ') - 4);
            time = stoi(input.substr(input.rfind(' ')));

            c = key(music_name);
            h = hash_function(music_playlist, music_name, time, c, m);

            cout << music_name << ' ' << h << '\n';
            n++;
        }
        else if(input[0] == 'P' || input[0] == 'T') {
            music_name = input.substr(5);

            c = key(music_name);
            aux = search(music_playlist, music_name, c, m);

            if(music_playlist[aux].get_name() == music_name) {
                if(input[0] == 'P') {
                    music_playlist[aux].add_repeat();
                }

                cout << music_name << ' ' << music_playlist[aux].get_repeat() << '\n';
            }
        }
    }

    return 0;
}

int key(string &music_name) {
    int temp = 0;

    for(int i = 1; i < music_name.size(); i++) {
        temp += (int) music_name[i] * i;
    }

    return temp;
}

int hash_function(hash_table *music_playlist, string &music_name, int &time, int &c, int &m) {
    int h;

    for(int i = 0; i < m; i++) {
        h = (c + i) % m;

        if(music_playlist[h].get_repeat() == -1) {
            music_playlist[h].set_name(music_name);
            music_playlist[h].set_time(time);
            music_playlist[h].set_repeat(0);
            i = m;
        }
    }

    return h;
}

void rehash(hash_table **music_playlist, int &m) {
    int c, temp_time, temp_tam, h;
    hash_table *temp_music_playlist;
    string temp_name;

    temp_tam = (m * 2) + 1;
    temp_music_playlist =  new hash_table[temp_tam];

    for(int i = 0; i < m; i++) {
        if((*music_playlist)[i].get_repeat() != -1) {
            temp_name = (*music_playlist)[i].get_name();
            temp_time = (*music_playlist)[i].get_time();

            c = key(temp_name);
            h = hash_function(temp_music_playlist, temp_name, temp_time, c, temp_tam);
            temp_music_playlist[h].set_repeat((*music_playlist)[i].get_repeat());
        }
    }

    m = temp_tam;

    delete [] *music_playlist;

    *music_playlist = temp_music_playlist;
}

int search(hash_table *music_playlist, string &music_name,int &c, int &m) {
    int h;

    for(int i = 0; i < m; i++) {
        h = (c + i) % m;

        if(music_playlist[h].get_name() == music_name) {
            return h;
        }
    }
}
