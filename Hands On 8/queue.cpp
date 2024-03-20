#include <iostream>

using namespace std;

class Queue {
private:
    int* queue;
    int size;
    int front, rear, count;

public:
    Queue(int size) : size(size), front(0), rear(-1), count(0) {
        queue = new int[size];
    }

    ~Queue() {
        delete[] queue;
    }

    void enqueue(int value) {
        if (count == size) {
            cout << "Queue Overflow" << endl;
            return;
        }
        rear = (rear + 1) % size;
        queue[rear] = value;
        count++;
    }

    int dequeue() {
        if (count == 0) {
            cout << "Queue Underflow" << endl;
            return -1; // Using -1 to indicate underflow/error.
        }
        int value = queue[front];
        front = (front + 1) % size;
        count--;
        return value;
    }

    bool isEmpty() {
        return count == 0;
    }
};

int main() {
    Queue queue(8);

    queue.enqueue(5);
    queue.enqueue(20);
    queue.enqueue(13);
    queue.enqueue(18);

    cout << "Is queue empty? " << (queue.isEmpty() ? "Yes" : "No") << endl;

    cout << "Dequeued element: " << queue.dequeue() << endl;
    cout << "Dequeued element: " << queue.dequeue() << endl;
    cout << "Dequeued element: " << queue.dequeue() << endl;
    cout << "Is queue empty? " << (queue.isEmpty() ? "Yes" : "No") << endl;
    cout << "Dequeued element: " << queue.dequeue() << endl;
    cout << "Is queue empty? " << (queue.isEmpty() ? "Yes" : "No") << endl;


    return 0;
}


// OUTPUT 
// Is queue empty? No
// Dequeued element: 5
// Dequeued element: 20
// Dequeued element: 13
// Is queue empty? No
// Dequeued element: 18
// Is queue empty? Yes

// This code is written by Aaryan Mori
// Reference : https://www.geeksforgeeks.org/introduction-and-array-implementation-of-queue/