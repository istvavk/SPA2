#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class HashTable {
private:
    int size;
    vector<string>* table;

    int h1(string s);
    int h2(string s);
    int h3(string s);
    int h4(string s);

public:
    HashTable(int n);
    ~HashTable();

    void insert(string s);
    string search(string s);
};
// konstruktor
HashTable::HashTable(int n) {
    size = n;
    table = new vector<string>[n];
}
// destruktor
HashTable::~HashTable() {
    delete[] table;
}

int HashTable::h1(string s) {
    int hash_val = 0;
    for (char c : s) {
        hash_val += int(c);
    }
    return hash_val % size;
}

int HashTable::h2(string s) {
    int hash_val = 1;
    for (int i = 0; i < s.length(); i++) {
        hash_val += (int(s[i]) * pow(19, i));
    }
    return hash_val % size;
}

int HashTable::h3(string s) {
    int hash_val = 7;
    for (int i = 0; i < s.length(); i++) {
        hash_val += (int(s[i]) * pow(30, i));
    }
    return hash_val % size;
}

int HashTable::h4(string s) {
    int hash_val = 3;
    int p = 7;
    for (int i = 0; i < s.length(); i++) {
        hash_val += (int(s[i]) * pow(3, i) * pow(p, i));
    }
    return hash_val % size;
}

void HashTable::insert(string s) {
    int hashvals[] = {h1(s), h2(s), h3(s), h4(s)};
    for (int h : hashvals) {
        table[h].push_back(s);
    }
}

string HashTable::search(string s) {
    int hashvals[] = {h1(s), h2(s), h3(s), h4(s)};
    for (int h : hashvals) {
        for (string t : table[h]) {
            if (s == t) {
                return "Element je u tablici";
            }
        }
    }
    return "Element nije u tablici";
}

int main(){
    HashTable table (100);

    vector<string> s = {
            "jopis107", "hstranput", "Matej293", "MateaCucman", "JosipCestar",
            "lanamak", "DanijelaValjak", "filipuranjek", "domagojziros", "lsanic",
            "TomislavVinkovic", "IvoSusac", "matej2810", "KresimirSecan",
            "inespejic", "InesSimunovic", "IvanFrantal", "Frle001", "inesstrapac",
            "mkolak", "Dpritisa", "istvavk", "mtoldi", "lbrodar5", "mkristic",
            "andreamatasovic", "balentovicanja", "IvanaVinkovic", "prakidzija",
            "DMV1204", "JMesaric", "KarloKampic", "jurick1910", "LarisaDarojkovic"
    };

    for(auto i : s) {
        table.insert(i);
    }


    cout << table.search("domagojziros") << endl;
    cout << table.search("KresimirSecan") << endl;

    cout<<table.search("Zir")<<endl;
    cout << table.search("AdrianC") << endl;

    cout<<table.search("istvavk")<<endl;

    return 0;
}
