#include <iostream>
#include <string>
using namespace std;
const int SIZE = 5;
struct Node {
    unsigned key; int count; Node* next;
    Node(unsigned k) : key(k), count(1), next(nullptr) {}
};
class HashTable {
    Node* table[SIZE] = {};
    int hash(unsigned k) { return k % SIZE; }
public:
    static unsigned toInt(const string& s) {
        unsigned k = 0;
        for (char c : s) k = k * 31 + c;
        return k;
    }
    void insert(const string& tag) {
        unsigned k = toInt(tag); int i = hash(k);
        for (Node* p = table[i]; p; p = p->next)
            if (p->key == k) { p->count++; return; }
        Node* n = new Node(k);
        n->next = table[i];
        table[i] = n;
    }
    int search(const string& tag) {
        unsigned k = toInt(tag);
        for (Node* p = table[hash(k)]; p; p = p->next)
            if (p->key == k) return p->count;
        return 0;
    }
    bool remove(const string& tag) {
        unsigned k = toInt(tag); int i = hash(k);
        Node* prev = nullptr;
        for (Node* p = table[i]; p; prev = p, p = p->next)
            if (p->key == k) {
                if (prev) prev->next = p->next;
                else table[i] = p->next;
                delete p;
                return true;
            }
        return false;
    }
    int longestChain() {
        int longest = 0;
        for (int i = 0; i < SIZE; i++) {
            int len = 0;
            for (Node* p = table[i]; p; p = p->next) len++;
            if (len > longest) longest = len;
        }
        if (longest > 5) cout << "SYSTEM OVERLOAD\n";
        return longest;
    }
};
int main() {
    HashTable h;
    string tags[] = {"#cs", "#dsa", "#fyp", "#exam", "#cs", "#dsa", "#cs"};
    for (string t : tags) h.insert(t);
    cout << h.search("#cs") << "\n";
    h.remove("#fyp");
    cout << h.longestChain() << "\n";
}
