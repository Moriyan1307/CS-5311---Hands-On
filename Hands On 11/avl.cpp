#include <iostream>
using namespace std;

class Node {
public:
    int key;
    Node *left, *right;
    int height;

    Node(int d) : key(d), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
public:
    Node* root;

    AVLTree() : root(nullptr) {}

    // Utility function to get the height of the tree
    int height(Node *N) {
        if (N == nullptr) return 0;
        return N->height;
    }

    // Utility function to get maximum of two integers
    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    // Right rotate utility
    Node* rightRotate(Node *y) {
        Node *x = y->left;
        Node *T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        // Return new root
        return x;
    }

    // Left rotate utility
    Node* leftRotate(Node *x) {
        Node *y = x->right;
        Node *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        // Return new root
        return y;
    }

    // Get Balance factor of node N
    int getBalance(Node *N) {
        if (N == nullptr) return 0;
        return height(N->left) - height(N->right);
    }

    // Recursive function to insert a key in the subtree rooted with node and returns the new root of the subtree.
    Node* insert(Node* node, int key) {
        /* 1. Perform the normal BST insertion */
        if (node == nullptr) return(new Node(key));

        if (key < node->key) node->left = insert(node->left, key);
        else if (key > node->key) node->right = insert(node->right, key);
        else return node; // Duplicate keys not allowed

        /* 2. Update height of this ancestor node */
        node->height = 1 + max(height(node->left), height(node->right));

        /* 3. Get the balance factor of this ancestor node to check whether this node became unbalanced */
        int balance = getBalance(node);

        // If this node becomes unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && key < node->left->key) return rightRotate(node);

        // Right Right Case
        if (balance < -1 && key > node->right->key) return leftRotate(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        /* return the (unchanged) node pointer */
        return node;
    }

    // A utility function to print inorder traversal of the tree.
    void inOrder(Node *root) {
        if (root != nullptr) {
            inOrder(root->left);
            cout << root->key << " ";
            inOrder(root->right);
        }
    }

    // Function to search a given key in a given BST
    Node* search(Node* root, int key) {
        // Base Cases: root is null or key is present at root
        if (root == nullptr || root->key == key) return root;

        // Key is greater than root's key
        if (root->key < key) return search(root->right, key);

        // Key is smaller than root's key
        return search(root->left, key);
    }

    // Recursive function to delete a node with given key from subtree with given root. It returns root of the modified subtree.
    Node* deleteNode(Node* root, int key) {
        // STEP 1: PERFORM STANDARD BST DELETE
        if (root == nullptr) return root;

        // If the key to be deleted is smaller than the root's key, then it lies in left subtree
        if ( key < root->key ) root->left = deleteNode(root->left, key);

        // If the key to be deleted is greater than the root's key, then it lies in right subtree
        else if( key > root->key ) root->right = deleteNode(root->right, key);

        // if key is same as root's key, then this is the node to be deleted
        else {
            // node with only one child or no child
            if( (root->left == nullptr) || (root->right == nullptr) ) {
                Node *temp = root->left ? root->left : root->right;

                // No child case
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                }
                else // One child case
                *root = *temp; // Copy the contents of the non-empty child
                delete temp;
            }
            else {
                // node with two children: Get the inorder successor (smallest in the right subtree)
                Node* temp = minValueNode(root->right);

                // Copy the inorder successor's data to this node
                root->key = temp->key;

                // Delete the inorder successor
                root->right = deleteNode(root->right, temp->key);
            }
        }

        // If the tree had only one node then return
        if (root == nullptr) return root;

        // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
        root->height = 1 + max(height(root->left), height(root->right));

        // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether this node became unbalanced)
        int balance = getBalance(root);

        // If this node becomes unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);

        // Left Right Case
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Right Case
        if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);

        // Right Left Case
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr) current = current->left;
        return current;
    }

    void insert(int key) {
        root = insert(root, key);
    }

    void deleteKey(int key) {
        root = deleteNode(root, key);
    }

    bool searchKey(int key) {
        Node* result = search(root, key);
        return result != nullptr;
    }
};

int main() {
    AVLTree tree;
    
    tree.insert(9);
    tree.insert(5);
    tree.insert(10);
    tree.insert(0);
    tree.insert(6);
    tree.insert(11);
    tree.insert(1);
    tree.insert(2);

    cout << "Inorder traversal of the constructed AVL tree is:\n";
    tree.inOrder(tree.root);
    cout << "\n";

    cout << "Deleting 10\n";
    tree.deleteKey(10);
    cout << "Inorder traversal after deletion of 10:\n";
    tree.inOrder(tree.root);
    cout << "\n";

    cout << "Search for key 6 " << (tree.searchKey(6)? "found":"not found");
   

    return 0;
}

// OUtPUT

// Inorder traversal of the constructed AVL tree is:
// 0 1 2 5 6 9 10 11 
// Deleting 10
// Inorder traversal after deletion of 10:
// 0 1 2 5 6 9 11 
// Search for key 6 found

// This code is written by Aaryan Mori
// Reference : https://www.geeksforgeeks.org/insertion-in-an-avl-tree/
