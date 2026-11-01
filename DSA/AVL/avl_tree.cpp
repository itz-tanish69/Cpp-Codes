#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    int height;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        height = 1;
        left = NULL;
        right = NULL;
    }
};

int nodeHeight(Node* node) {
    return node == NULL ? 0 : node->height;
}

int balanceFactor(Node* node) {
    return node == NULL ? 0 : nodeHeight(node->left) - nodeHeight(node->right);
}

void updateHeight(Node* node) {
    node->height = 1 + max(nodeHeight(node->left), nodeHeight(node->right));
}

Node* rotateRight(Node* root) {
    Node* newRoot = root->left;
    Node* movedSubtree = newRoot->right;

    newRoot->right = root;
    root->left = movedSubtree;

    updateHeight(root);
    updateHeight(newRoot);

    return newRoot;
}

Node* rotateLeft(Node* root) {
    Node* newRoot = root->right;
    Node* movedSubtree = newRoot->left;

    newRoot->left = root;
    root->right = movedSubtree;

    updateHeight(root);
    updateHeight(newRoot);

    return newRoot;
}

Node* rebalance(Node* root) {
    updateHeight(root);
    int balance = balanceFactor(root);

    // Left-heavy: perform an LL or LR rotation.
    if (balance > 1) {
        if (balanceFactor(root->left) < 0) {
            root->left = rotateLeft(root->left);
        }
        return rotateRight(root);
    }

    // Right-heavy: perform an RR or RL rotation.
    if (balance < -1) {
        if (balanceFactor(root->right) > 0) {
            root->right = rotateRight(root->right);
        }
        return rotateLeft(root);
    }

    return root;
}

Node* insert(Node* root, int value) {
    if (root == NULL) {
        return new Node(value);
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    } else {
        return root; // Ignore duplicate values.
    }

    return rebalance(root);
}

Node* findMin(Node* root) {
    while (root != NULL && root->left != NULL) {
        root = root->left;
    }

    return root;
}

Node* deleteNode(Node* root, int value) {
    if (root == NULL) {
        return NULL;
    }

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        if (root->left == NULL || root->right == NULL) {
            Node* child = root->left != NULL ? root->left : root->right;
            delete root;
            return child;
        }

        Node* successor = findMin(root->right);
        root->data = successor->data;
        root->right = deleteNode(root->right, successor->data);
    }

    return rebalance(root);
}

bool search(Node* root, int value) {
    while (root != NULL) {
        if (value == root->data) {
            return true;
        }

        root = value < root->data ? root->left : root->right;
    }

    return false;
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

    cout << "Inorder: ";
    inorder(root);
    cout << "\n";

    cout << "Preorder: ";
    preorder(root);
    cout << "\n";

    cout << "Height: " << nodeHeight(root) << "\n";

    int key;
    cout << "Enter key to search: ";
    cin >> key;

    if (search(root, key)) {
        cout << "Key Found\n";
    } else {
        cout << "Key Not Found\n";
    }

    cout << "Enter key to delete: ";
    cin >> key;
    root = deleteNode(root, key);

    cout << "Inorder after deletion: ";
    inorder(root);
    cout << "\n";

    deleteTree(root);
    return 0;
}
