#include <iostream>
using namespace std;
const int SIZE = 11;
enum State { EMPTY, FULL, DELETED };
struct Seat {
    int id = 0;
    State state = EMPTY;
};
class Theater {
    Seat table[SIZE];
    int count = 0;
public:
    double loadFactor() { return (double)count / SIZE; }
    bool book(int id) {
        if (loadFactor() > 0.5) {
            cout << "Rehash needed\n";
            return false;
        }
        int base = id % SIZE;
        for (int j = 0; j < SIZE; j++) {
            int i = (base + j * j) % SIZE;
            if (table[i].state != FULL) {
                table[i].id = id;
                table[i].state = FULL;
                count++;
                return true;
            }
            if (table[i].id == id) return false;
        }
        return false;
    }
    int search(int id) {
        int base = id % SIZE;
        for (int j = 0; j < SIZE; j++) {
            int i = (base + j * j) % SIZE;
            if (table[i].state == EMPTY) return -1;
            if (table[i].state == FULL && table[i].id == id) return i;
        }
        return -1;
    }
    bool cancel(int id) {
        int i = search(id);
        if (i == -1) return false;
        table[i].state = DELETED;
        count--;
        return true;
    }
};
int main() {
    Theater t;
    int ids[] = {5, 16, 27, 38, 49, 60, 71};
    for (int id : ids) t.book(id);
    cout << t.loadFactor() << "\n";
    cout << t.search(27) << "\n";
}
