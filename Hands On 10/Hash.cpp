#include <iostream>
#include <vector>
#define sout(n) cout << (n)<< " ";
using namespace std;

class Node {
public:
    int key;
    int value;
    Node* next;
    Node* prev;

    Node(int key, int value) {
        this->key = key;
        this->value = value;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

class DoublyLinkedList {
public:
    Node* head;
    Node* tail;

    DoublyLinkedList() {
        this->head = nullptr;
        this->tail = nullptr;
    }

    void insert(int key, int value) {
        Node* new_node = new Node(key, value);
        if (!this->head) {
            this->head = this->tail = new_node;
        } else {
            this->tail->next = new_node;
            new_node->prev = this->tail;
            this->tail = new_node;
        }
    }

    void remove(Node* node) {
        if (node->prev) {
            node->prev->next = node->next;
        } else {
            this->head = node->next;
        }

        if (node->next) {
            node->next->prev = node->prev;
        } else {
            this->tail = node->prev;
        }

        delete node;
    }
};

class HashTable {
public:
    int capacity;
    int size;
    vector<DoublyLinkedList*> table;
    int threshold;
    int shrink_threshold;

    HashTable(int initial_capacity = 10) {
        this->capacity = initial_capacity;
        this->size = 0;
        this->table.resize(this->capacity);
        for (int i = 0; i < this->capacity; ++i) {
            this->table[i] = new DoublyLinkedList();
        }
        this->threshold = int(this->capacity * 0.75);
        this->shrink_threshold = int(this->capacity * 0.25);
    }

    int hash_function(int key) {
        return (key * 2654435761) % this->capacity;
    }

    void insert(int key, int value) {
        int index = this->hash_function(key);
        DoublyLinkedList* list_at_index = this->table[index];
        Node* current_node = list_at_index->head;

        while (current_node) {
            if (current_node->key == key) {
                current_node->value = value;
                return;
            }
            current_node = current_node->next;
        }

        list_at_index->insert(key, value);
        this->size++;

        if (this->size >= this->threshold) {
            resize(this->capacity * 2);
        }
    }

    int get(int key) {
        int index = this->hash_function(key);
        DoublyLinkedList* list_at_index = this->table[index];
        Node* current_node = list_at_index->head;

        while (current_node) {
            if (current_node->key == key) {
                return current_node->value;
            }
            current_node = current_node->next;
        }

        return -1;
    }

    bool search(int key) {
        int index = this->hash_function(key);
        DoublyLinkedList* list_at_index = this->table[index];
        Node* current_node = list_at_index->head;

        while (current_node) {
            if (current_node->key == key) {
                return true;
            }
            current_node = current_node->next;
        }

        return false;
    }

    void remove(int key) {
        int index = this->hash_function(key);
        DoublyLinkedList* list_at_index = this->table[index];
        Node* current_node = list_at_index->head;

        while (current_node) {
            if (current_node->key == key) {
                list_at_index->remove(current_node);
                this->size--;

                if (this->size <= this->shrink_threshold) {
                    resize(max(this->capacity / 2, 1));
                }
                return;
            }

            current_node = current_node->next;
        }
    }

    void resize(int new_capacity) {
        vector<DoublyLinkedList*> new_table(new_capacity);
        for (int i = 0; i < new_capacity; ++i) {
            new_table[i] = new DoublyLinkedList();
        }

        for (DoublyLinkedList* list_at_index : this->table) {
            Node* current_node = list_at_index->head;
            while (current_node) {
                int new_index = this->hash_function(current_node->key);
                new_table[new_index]->insert(current_node->key, current_node->value);
                current_node = current_node->next;
            }
        }

        this->capacity = new_capacity;
        this->table = new_table;
        this->threshold = int(this->capacity * 0.75);
        this->shrink_threshold = int(this->capacity * 0.25);
    }

    void print_table() {
        for (int i = 0; i < this->capacity; ++i) {
            cout << "Index " << i << ": ";
            DoublyLinkedList* linked_list = this->table[i];
            Node* current_node = linked_list->head;
            while (current_node) {
                cout << "(" << current_node->key << ", " << current_node->value << ") ";
                current_node = current_node->next;
            }
            cout << endl;
        }
    }
};

int main() {

    HashTable hash_table;
    hash_table.insert(0, 15);
    hash_table.insert(2, 20);
    hash_table.insert(4, 18);
    hash_table.insert(5, 34);
    hash_table.insert(8, 27);
 
   

    hash_table.print_table();

    cout << "Value for key 8: " << hash_table.get(8) << endl;

    hash_table.remove(8);

    cout << "Search for key 8: " << (hash_table.search(8) ? "Exist" : "Does not exist") << endl;
    cout << "Search for key 5: " << (hash_table.search(5) ? "Exist" : "Does not exist") << endl;
    cout << "Search for key 0: " << (hash_table.search(0) ? "Exist" : "Does not exist") << endl;
    cout << "Search for key 2: " << (hash_table.search(2) ? "Exist" : "Does not exist") << endl;

    

    hash_table.print_table();


    return 0;
}


// OUTPUT
// Index 0: (0, 15) 
// Index 1: 
// Index 2: (2, 20) 
// Index 3: 
// Index 4: (4, 18) 
// Index 5: (5, 34) 
// Index 6: 
// Index 7: 
// Index 8: (8, 27) 
// Index 9: 
// Value for key 8: 27
// Search for key 8: Does not exist
// Search for key 5: Exist
// Search for key 0: Exist
// Search for key 2: Exist
// Index 0: (0, 15) 
// Index 1: 
// Index 2: (2, 20) 
// Index 3: 
// Index 4: (4, 18) 
// Index 5: (5, 34) 
// Index 6: 
// Index 7: 
// Index 8: 
// Index 9: 

// This code is written by Aaryan Mori
// References : https://www.geeksforgeeks.org/introduction-and-insertion-in-a-doubly-linked-list/

