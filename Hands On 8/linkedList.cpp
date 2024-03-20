#include <iostream>
using namespace std;
#define sout(n) cout << (n)<< " ";

class Node {
public:
    int value;
    int next;

    Node() : value(0), next(-1) {} // Initialize with default values
};

class SinglyLinkedList {
private:
    Node* nodes; // Array of nodes
    int head;
    int* freeList;
    int freeListSize;
    int capacity; // Maximum size of the list

public:
    SinglyLinkedList(int size) : capacity(size), head(-1) {
        nodes = new Node[capacity];
        freeList = new int[capacity];
        freeListSize = capacity;
        for (int i = 0; i < capacity; ++i) {
            freeList[i] = i; // Initialize free list with indices
        }
    }

    ~SinglyLinkedList() {
        delete[] nodes;
        delete[] freeList;
    }

    int allocateNode(int value) {
        if (freeListSize == 0) {
            cout << "Out of memory" << endl;
            return -1;
        }
        int index = freeList[--freeListSize];
        nodes[index].value = value;
        nodes[index].next = -1;
        return index;
    }

    void freeNode(int index) {
        freeList[freeListSize++] = index;
    }

    void insert(int value) {
        int index = allocateNode(value);
        if (index == -1) return; // No space left

        if (head == -1) {
            head = index;
        } else {
            int current = head;
            while (nodes[current].next != -1) {
                current = nodes[current].next;
            }
            nodes[current].next = index;
        }
    }

    bool search(int value) {
        int current = head;
        while (current != -1) {
            if (nodes[current].value == value) {
                return true;
            }
            current = nodes[current].next;
        }
        return false;
    }

    void deleteValue(int value) {
        if (head == -1) return; // Empty list

        if (nodes[head].value == value) {
            int temp = head;
            head = nodes[head].next;
            freeNode(temp);
            return;
        }

        int current = head;
        while (nodes[current].next != -1) {
            int nextNode = nodes[current].next;
            if (nodes[nextNode].value == value) {
                nodes[current].next = nodes[nextNode].next;
                freeNode(nextNode);
                return;
            }
            current = nextNode;
        }
    }

    void display() {
        int current = head;
        while (current != -1) {
            cout << nodes[current].value << " ";
            current = nodes[current].next;
        }
        cout<< endl;
        
    }
};

int main() {
    SinglyLinkedList list(10); // List with capacity for 10 nodes

    list.insert(13);
    list.insert(5);
    list.insert(18);
    list.insert(7);

    cout << "Initial list: ";
    list.display();

    list.deleteValue(5);
    cout << "List after deleting 5: ";
    list.display();

    return 0;
}



// OUTPUT 
// Initial list: 13 5 18 7 
// List after deleting 5: 13 18 7 

// This code is written by Aaryan Mori
// Reference : https://www.geeksforgeeks.org/program-to-implement-singly-linked-list-in-c-using-class/