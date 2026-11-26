#include <iostream>
using namespace std;
const int SIZE = 10;
const int PRIME = 7;
enum State { EMPTY, FULL, DELETED };
struct Vault {
    int key = 0;
    State state = EMPTY;
};
class Bank {
    Vault table[SIZE];
    int h1(int k) { return k % SIZE; }
    int h2(int k) { return PRIME - (k % PRIME); }
public:
    bool insert(int k) {
        for (int j = 0; j < SIZE; j++) {
            int i = (h1(k) + j * h2(k)) % SIZE;
            if (table[i].state == FULL && table[i].key == k) return false;
            if (table[i].state != FULL) {
                table[i].key = k;
                table[i].state = FULL;
                return true;
            }
        }
        cout << "Vault Full\n";
        return false;
    }
    int search(int k) {
        for (int j = 0; j < SIZE; j++) {
            int i = (h1(k) + j * h2(k)) % SIZE;
            if (table[i].state == EMPTY) return -1;
            if (table[i].state == FULL && table[i].key == k) return i;
        }
        return -1;
    }
    bool remove(int k) {
        int i = search(k);
        if (i == -1) return false;
        table[i].state = DELETED;
        return true;
    }
};
int main() {
    Bank b;
    int keys[] = {15, 25, 35, 45, 55, 65, 75, 85, 95, 105, 115, 125};
    for (int k : keys) b.insert(k);
    cout << b.search(45) << "\n";
}
