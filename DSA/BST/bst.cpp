#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = NULL;
        right = NULL;
    }
};

Node* insert(Node* root, int value) {
    if (root == NULL) {
        return new Node(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    } // Duplicate values are ignored.

    return root;
}

bool search(Node* root, int key) {
    while (root != NULL) {
        if (root->data == key) {
            return true;
        }

        root = key < root->data ? root->left : root->right;
    }

    return false;
}

Node* findMin(Node* root) {
    while (root != NULL && root->left != NULL) {
        root = root->left;
    }

    return root;
}

Node* findMax(Node* root) {
    while (root != NULL && root->right != NULL) {
        root = root->right;
    }

    return root;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL) {
        return NULL;
    }

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            Node* child = root->right;
            delete root;
            return child;
        }

        if (root->right == NULL) {
            Node* child = root->left;
            delete root;
            return child;
        }

        Node* successor = findMin(root->right);
        root->data = successor->data;
        root->right = deleteNode(root->right, successor->data);
    }

    return root;
}

void inorder(Node* root) {
    if (root == NULL) {
        return;
    }

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(Node* root) {
    if (root == NULL) {
        return;
    }

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (root == NULL) {
        return;
    }

    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

void levelOrder(Node* root) {
    if (root == NULL) {
        return;
    }

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        cout << current->data << " ";

        if (current->left != NULL) q.push(current->left);
        if (current->right != NULL) q.push(current->right);
    }
}

int height(Node* root) {
    if (root == NULL) {
        return 0;
    }

    return 1 + max(height(root->left), height(root->right));
}

int countNodes(Node* root) {
    if (root == NULL) {
        return 0;
    }

    return 1 + countNodes(root->left) + countNodes(root->right);
}

int countLeafNodes(Node* root) {
    if (root == NULL) {
        return 0;
    }

    if (root->left == NULL && root->right == NULL) {
        return 1;
    }

    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

void printTraversals(Node* root) {
    cout << "Inorder: ";
    inorder(root);
    cout << "\nPreorder: ";
    preorder(root);
    cout << "\nPostorder: ";
    postorder(root);
    cout << "\nLevel Order: ";
    levelOrder(root);
    cout << "\n";
}

void printStats(Node* root) {
    cout << "Height: " << height(root) << "\n";
    cout << "Total Nodes: " << countNodes(root) << "\n";
    cout << "Leaf Nodes: " << countLeafNodes(root) << "\n";

    Node* minimum = findMin(root);
    Node* maximum = findMax(root);
    if (minimum != NULL) cout << "Minimum: " << minimum->data << "\n";
    if (maximum != NULL) cout << "Maximum: " << maximum->data << "\n";
}

void deleteTree(Node* root) {
    if (root == NULL) {
        return;
    }

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    Node* root = NULL;
    int n;

    cout << "Enter number of values: ";
    cin >> n;

    cout << "Enter values: ";
    for (int i = 0; i < n; i++) {
        int value;
        cin >> value;
        root = insert(root, value);
    }

    cout << "\nTree traversals:\n";
    printTraversals(root);
    printStats(root);

    int key;
    cout << "Enter key to search: ";
    cin >> key;
    cout << (search(root, key) ? "Key Found\n" : "Key Not Found\n");

    cout << "Enter key to delete: ";
    cin >> key;
    root = deleteNode(root, key);

    cout << "\nAfter deletion:\n";
    printTraversals(root);
    printStats(root);

    deleteTree(root);
    return 0;
}
