#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename V>
struct node {
    int key;
    V value;
};

template <typename V>
class Dictionary {
private:
    vector<node<V>> data;
    int size;
public:
    // konstruktor
    Dictionary (int size) {
        this->size = size;
        this->data.resize(size);
    }

    // search
    node<V>* search(int key) {
        int i = 0;
        int h1 = key % size;
        int h2 = 1 + (key % (size - 1));
        while (i < size) {
            int h = (h1 + i * h2) % size;
            if (data[h].key == key) {
                return &data[h];
            } else if (data[h].key == 0) {
                return nullptr;
            }
            i++;
        }
        return nullptr;
    }

    // dodajemo par (k, v)
    void insert(int k, V v) {
        int i = 0;
        int h1 = k % size;
        int h2 = 1 + (k % (size - 1));
        while (i < size) {
            int h = (h1 + i * h2) % size;
            if (data[h].key == 0 || data[h].key == k) {
                data[h] = {k, v};
                return;
            }
            i++;
        }
    }

    // brisanje
    void remove(int k) {
        int i = 0;
        int h1 = k % size;
        int h2 = 1 + (k % (size - 1));
        while (i < size) {
            int h = (h1 + i * h2) % size;
            if (data[h].key == k) {
                data[h] = {0, V()};
                return;
            } else if (data[h].key == 0) {
                return;
            }
            i++;
        }
    }

    // ispis
    void print() {
        for (auto i : data) {
            if (i.key ==0 && i.value == 0) {
                cout << "nil ";
            } else {
                cout << "K:" << i.key << " V:" << i.value << " ";
            }
        }
    }
};

int main() {
    vector<int> keys(10);
    vector<float> values {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.f};
    Dictionary<float> dict(19);

    for (int i = 0; i < 10; i++) {
        cin >> keys[i];
    }

    for (int i = 0; i < 10; i++) {
        dict.insert(keys[i], values[i]);
    }

    dict.remove(keys[6]);
    dict.insert(keys[2], 1.1f);

    dict.print();

    return 0;
}