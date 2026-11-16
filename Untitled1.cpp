#include <iostream>
using namespace std;
class MaxHeap {
private:
int* arr;
int capacity;
int size;
public:
    MaxHeap(int c) {
        capacity = c;
        size = 0;
        arr = new int[capacity];
    }

int parent(int i) { return (i - 1) / 2; }
int leftChild(int i) { return (2 * i) + 1; }
int rightChild(int i) { return (2 * i) + 2; }
void swapVal(int& a, int& b) { int t = a; a = b; b = t; }
void buildHeap(int values[], int n) {
    for (int i = 0; i < n; i++) {
        arr[size] = values[i];
        int j = size;
        size++;

        while (j > 0 && arr[j] > arr[parent(j)]) {
            swapVal(arr[j], arr[parent(j)]);
            j = parent(j);
        }
    }
}
void display() {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void deleteheap(int deletedarray[], int& j) {
    if (size == 0) {
        cout << "Heap is empty!" << endl;
        return;
    }

    int top = arr[0];  

    arr[0] = arr[size - 1];  
    size--;

    int i = 0;

    while (i < size) {
        int left = leftChild(i);
        int right = rightChild(i);
        int largest = i;

        if (left < size && arr[left] > arr[largest]) {
            largest = left;
        }

        if (right < size && arr[right] > arr[largest]) {
            largest = right;
        }

        if (largest != i) {
            swapVal(arr[i], arr[largest]);
            i = largest;
        }
        else {
            break;
        }
}
    deletedarray[j] = top;  
    j++;                  
} };
int main() {
    MaxHeap h(10);
    int values[] = {20, 15, 30, 10, 40};
    h.buildHeap(values, 5);
    h.display();
    int deletedarray[5];
    int j = 0;
    for (int i = 0; i < 3; i++) {
        h.deleteheap(deletedarray, j);
    }
    for (int i = 0; i < j; i++) {
        cout << deletedarray[i] << " ";
    }
    cout << endl;

    return 0;
}


