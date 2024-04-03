#include <iostream>

using namespace std;

enum Color { RED, BLACK };

struct Node {
    int key;
    Color color;
    Node *left, *right, *parent;

    Node(int key) : key(key), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node *root, *NIL;

    void leftRotate(Node *x) {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != NIL)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == NIL)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node *y) {
        Node *x = y->left;
        y->left = x->right;
        if (x->right != NIL)
            x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == NIL)
            root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
        x->right = y;
        y->parent = x;
    }

    void fixInsert(Node *z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node *y = z->parent->parent->right;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                Node *y = z->parent->parent->left;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void transplant(Node *u, Node *v) {
        if (u->parent == NIL)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        v->parent = u->parent;
    }

    void fixRemove(Node *x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                Node *w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                Node *w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    Node *search(Node *node, int key) {
        if (node == NIL || key == node->key)
            return node;
        if (key < node->key)
            return search(node->left, key);
        return search(node->right, key);
    }

    Node *findSuccessor(Node *node) {
        while (node->left != NIL)
            node = node->left;
        return node;
    }

public:
    RedBlackTree() {
        NIL = new Node(0);
        NIL->color = BLACK;
        root = NIL;
    }

    void insert(int key) {
        Node *z = new Node(key);
        Node *y = NIL;
        Node *x = root;

        while (x != NIL) {
            y = x;
            if (z->key < x->key)
                x = x->left;
            else
                x = x->right;
        }

        z->parent = y;
        if (y == NIL)
            root = z;
        else if (z->key < y->key)
            y->left = z;
        else
            y->right = z;

        z->left = NIL;
        z->right = NIL;
        z->color = RED;

        fixInsert(z);
    }

    void remove(int key) {
        Node *z = search(root, key);
        if (z == NIL)
            return;
        Node *x, *y = z;
        Color originalColor = y->color;
        if (z->left == NIL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == NIL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = findSuccessor(z->right);
            originalColor = y->color;
            x = y->right;
            if (y->parent == z)
                x->parent = y;
            else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (originalColor == BLACK)
            fixRemove(x);
    }

    void inorderTraversal(Node *node) {
        if (node != NIL) {
            inorderTraversal(node->left);
            cout << node->key << " ";
            inorderTraversal(node->right);
        }
    }

    void inorderTraversal() {
        inorderTraversal(root);
    }

    int search(int key) {
        Node *result = search(root, key);
        if (result == NIL)
            return 0; // Not found
        else return 1;
        
    }
};

int main() {
    RedBlackTree rbt;
    rbt.insert(18);
    rbt.insert(14);
    rbt.insert(13);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(9);
    rbt.insert(11);

    cout << "Red-Black Tree inorder traversal: ";
    rbt.inorderTraversal();
    cout << endl;

    rbt.remove(11);
    cout << "Red-Black Tree inorder traversal after deletion of key 11: ";
    rbt.inorderTraversal();
    cout << endl;

    cout << "Search for key 18: " << (rbt.search(18)? "Found":"Not Found") << endl;  
    cout << "Search for key 9: " << (rbt.search(9) ? "Found":"Not Found") << endl;   
    cout << "Search for key 11: " <<  (rbt.search(11) ? "Found":"Not Found") << endl;    

    return 0;
}


// OUTPUT

// Red-Black Tree inorder traversal: 9 10 11 12 13 14 18 
// Red-Black Tree inorder traversal after deletion of key 11: 9 10 12 13 14 18 
// Search for key 18: Found
// Search for key 9: Found
// Search for key 11: Not Found

// This code is written by Aaryan Mori
// Reference : https://www.geeksforgeeks.org/introduction-to-red-black-tree/