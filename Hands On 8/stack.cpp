#include <iostream>
using namespace std;

class Stack {
private:
    int* stack;
    int size;
    int top;

public:
    Stack(int size) {
        this->size = size;
        stack = new int[size];
        top = -1;
    }

    ~Stack() {
        delete[] stack;
    }

    void push(int value) {
        if (top == size - 1) {
            cout << "Stack Overflow" << endl;
            return;
        }
        stack[++top] = value;
    }

    int pop() {
        if (top == -1) {
            cout << "Stack Underflow" << endl;
            return -1; // Indicating underflow.
        }
        return stack[top--];
    }

    bool isempty() {
        return top == -1;
    }
};

int main() {
    Stack stack(18);

    stack.push(5);
    stack.push(13);
    stack.push(7);
    stack.push(3);

    cout << "Is the stack empty? " << (stack.isempty() ? "Yes" : "No") << endl;

    cout << "Popped element: " << stack.pop() << endl;
    cout << "Popped element: " << stack.pop() << endl;
    cout << "Popped element: " << stack.pop() << endl;
    cout << "Is the stack empty? " << (stack.isempty() ? "Yes" : "No") << endl;
    cout << "Popped element: " << stack.pop() << endl;
    cout << "Is the stack empty? " << (stack.isempty() ? "Yes" : "No") << endl;

    return 0;
}


// OUTPUT
// Is the stack empty? No
// Popped element: 3
// Popped element: 7
// Popped element: 13
// Is the stack empty? No
// Popped element: 5
// Is the stack empty? Yes

// This code is written by Aaryan Mori
// Reference : https://www.geeksforgeeks.org/introduction-to-stack-data-structure-and-algorithm-tutorials/