#include <iostream>
using namespace std;

class TreeNode {
public:
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : value(value), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    TreeNode* root;

    TreeNode* insertRecursive(TreeNode* node, int value) {
        if (!node) {
            return new TreeNode(value);
        }
        if (value < node->value) {
            node->left = insertRecursive(node->left, value);
        } else if (value > node->value) {
            node->right = insertRecursive(node->right, value);
        }
        return node;
    }

    TreeNode* searchRecursive(TreeNode* node, int value) {
        if (!node || node->value == value) {
            return node;
        }
        if (value < node->value) {
            return searchRecursive(node->left, value);
        } else {
            return searchRecursive(node->right, value);
        }
    }

    TreeNode* deleteRecursive(TreeNode* node, int value) {
        if (!node) return node;

        if (value < node->value) {
            node->left = deleteRecursive(node->left, value);
        } else if (value > node->value) {
            node->right = deleteRecursive(node->right, value);
        } else {
            if (!node->left) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            TreeNode* temp = minValueNode(node->right);
            node->value = temp->value;
            node->right = deleteRecursive(node->right, temp->value);
        }
        return node;
    }

    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void inorderTraversal(TreeNode* node) {
        if (node) {
            inorderTraversal(node->left);
            cout << node->value << " ";
            inorderTraversal(node->right);
        }
    }

    void preorderTraversal(TreeNode* node) {
        if (node) {
            cout << node->value << " ";
            preorderTraversal(node->left);
            preorderTraversal(node->right);
        }
    }

    void postorderTraversal(TreeNode* node) {
        if (node) {
            postorderTraversal(node->left);
            postorderTraversal(node->right);
            cout << node->value << " ";
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int value) {
        root = insertRecursive(root, value);
    }

    bool search(int value) {
        return searchRecursive(root, value) != nullptr;
    }

    void deleteValue(int value) {
        root = deleteRecursive(root, value);
    }

    bool isEmpty() {
        return root == nullptr;
    }

    void displayInorder() {
        cout << "Inorder Traversal: ";
        inorderTraversal(root);
        cout << "\n";
    }

    void displayPreorder() {
        cout << "Preorder Traversal: ";
        preorderTraversal(root);
        cout << "\n";
    }

    void displayPostorder() {
        cout << "Postorder Traversal: ";
        postorderTraversal(root);
        cout << "\n";
    }
};

int main() {
    BinarySearchTree bst;
    bst.insert(15);
    bst.insert(13);
    bst.insert(12);
    bst.insert(14);
    bst.insert(17);
    bst.insert(16);
    bst.insert(18);

     cout << "After insertion, BST is empty? " << (bst.isEmpty() ? "Yes" : "No") << endl;

    cout << "BST Traversals\n";
    bst.displayInorder();
    bst.displayPreorder();
    bst.displayPostorder();

    if (bst.search(12)) {
        cout << "Found 12 in BST.\n";
    } else {
        cout << "12 not found in BST.\n";
    }

    bst.deleteValue(12); // Deleting leaf node
    bst.deleteValue(13); // Deleting node with one child
    bst.deleteValue(15); // Deleting node with two children
    cout << "BST Traversals after deletions\n";
    bst.displayInorder();
    bst.displayPreorder();
    bst.displayPostorder();

    


    if (bst.search(12)) {
        cout << "Found 12 in BST." << endl;
    } else {
        cout << "12 not found in BST, deletion confirmed." << endl;
    }

   

    return 0;
}


// OUTPUT

// After insertion, BST is empty? No
// BST Traversals
// Inorder Traversal: 12 13 14 15 16 17 18 
// Preorder Traversal: 15 13 12 14 17 16 18 
// Postorder Traversal: 12 14 13 16 18 17 15 
// Found 12 in BST.
// BST Traversals after deletions
// Inorder Traversal: 14 16 17 18 
// Preorder Traversal: 16 14 17 18 
// Postorder Traversal: 14 18 17 16 
// 12 not found in BST, deletion confirmed.

// Reference : https://www.geeksforgeeks.org/introduction-to-binary-search-tree-data-structure-and-algorithm-tutorials/