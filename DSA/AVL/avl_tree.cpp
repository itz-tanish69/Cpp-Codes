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

int height(Node* node) {
    return node == NULL ? 0 : node->height;
}

int balanceFactor(Node* node) {
    return node == NULL ? 0 : height(node->left) - height(node->right);
}

void updateHeight(Node* node) {
    node->height = 1 + max(height(node->left), height(node->right));
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

    if (balance > 1) {
        if (balanceFactor(root->left) < 0) {
            root->left = rotateLeft(root->left);
        }
        return rotateRight(root);
    }

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

Node* findMax(Node* root) {
    while (root != NULL && root->right != NULL) {
        root = root->right;
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

    cout << "\nAVL tree traversals:\n";
    printTraversals(root);
    printStats(root);

    int key;
    cout << "Enter key to search: ";
    cin >> key;
    cout << (search(root, key) ? "Key Found\n" : "Key Not Found\n");

    cout << "Enter key to delete: ";
    cin >> key;
    root = deleteNode(root, key);

    cout << "\nAfter deletion and rebalancing:\n";
    printTraversals(root);
    printStats(root);

    deleteTree(root);
    return 0;
}
