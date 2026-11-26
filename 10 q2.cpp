#include <iostream>
using namespace std;
const int SIZE = 7;
enum State { EMPTY, FULL, DELETED };
struct Slot {
    int id = 0;
    State state = EMPTY;
};
class Lockers {
    Slot table[SIZE];
    int totalProbes = 0;
public:
    bool insert(int id) {
        int i = id % SIZE, probes = 0, firstDel = -1;
        while (probes < SIZE) {
            if (table[i].state == FULL && table[i].id == id) return false;
            if (table[i].state == DELETED && firstDel == -1) firstDel = i;
            if (table[i].state == EMPTY) break;
            i = (i + 1) % SIZE;
            probes++;
        }
        if (firstDel != -1) i = firstDel;
        else if (probes == SIZE) return false;
        table[i].id = id;
        table[i].state = FULL;
        totalProbes += probes;
        cout << "ID " << id << " probes: " << probes << "\n";
        return true;
    }
    int search(int id) {
        int i = id % SIZE;
        for (int c = 0; c < SIZE; c++) {
            if (table[i].state == EMPTY) return -1;
            if (table[i].state == FULL && table[i].id == id) return i;
            i = (i + 1) % SIZE;
        }
        return -1;
    }
    bool remove(int id) {
        int i = search(id);
        if (i == -1) return false;
        table[i].state = DELETED;
        return true;
    }
    int getTotalProbes() { return totalProbes; }
};
int main() {
    Lockers l;
    int ids[] = {10, 17, 24, 3, 5};
    for (int id : ids) l.insert(id);
    l.remove(17);
    cout << l.search(24) << "\n";
    cout << l.search(17) << "\n";
    l.insert(31);
    cout << l.getTotalProbes() << "\n";
}
