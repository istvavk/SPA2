#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
#include <list>

using namespace std;

typedef vector<pair<int, float>> Chain;

vector<int> PullDigits(int value){
    vector<int> digits;
    
    if(value == 0){
        return {0};
    }
    while(value > 0){
        digits.push_back(value % 10);
        value /= 10;
    }
    return digits;
}

template<typename V>
class HashTable {
public:
    HashTable();

    void insert(int key, V value);
    pair<int, V> search(int key);

private:
    vector<list<pair<int, V>>> container;
    vector<int> randNums;

    int hash(int key);

};

template<typename V>
HashTable<V>::HashTable() {
    default_random_engine generator(time(0));
    uniform_int_distribution<int> distribute(0, 6);

    for (int i = 0; i < 7; ++i)
        randNums.push_back(distribute(generator));

    container.resize(7);
}

template<typename V>
int HashTable<V>::hash(int key) {
    vector<int> digits = PullDigits(key);
    int sum = 0;

    for (int i = 0; i < digits.size(); ++i)
        sum += randNums[i] * digits[i];

    return sum % 7;
}

template<typename V>
void HashTable<V>::insert(int key, V value) {
    int h = hash(key);

    auto it = find_if(container[h].begin(), container[h].end(), [&key](const auto &p){ return p.first == key; });
    if (it != container[h].end())
        it->second = value;
    else
        container[h].push_front({key, value});
}

template<typename V>
pair<int, V> HashTable<V>::search(int key) {
    int h = hash(key);

    auto it = find_if(container[h].begin(), container[h].end(), [&key](const auto &p){ return p.first == key; });
    if (it == container[h].end()) {
        cout << "Element s ključem " << key << " nije pronađen";
        return {};
    }
    else
        return *it;
}

int main() {
    HashTable<float> hashTable;

    vector<int> keys = {57, 84, 301, 11, 200, 99, 30, 8, 72, 150, 4, 2};

    float value = 0.0f;
    for (auto key : keys) {
        hashTable.insert(key, value);
        value += 0.1f;
    }

    pair<int, float> p = hashTable.search(4);

    cout << p.first << ", " << p.second << endl;


    return 0;
}
