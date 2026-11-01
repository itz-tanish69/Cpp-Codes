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

Node* createTree() {
    int data;
    cin >> data;

    if (data == -1) {
        return NULL;
    }

    Node* root = new Node(data);
    root->left = createTree();
    root->right = createTree();

    return root;
}

void preorder(Node* root) {
    if (root == NULL) {
        return;
    }

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node* root) {
    if (root == NULL) {
        return;
    }

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
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

        if (current->left != NULL) {
            q.push(current->left);
        }

        if (current->right != NULL) {
            q.push(current->right);
        }
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

bool searchNode(Node* root, int key) {
    if (root == NULL) {
        return false;
    }

    if (root->data == key) {
        return true;
    }

    return searchNode(root->left, key) || searchNode(root->right, key);
}

int main() {
    Node* root = createTree();

    cout << "Preorder: ";
    preorder(root);
    cout << "\n";

    cout << "Inorder: ";
    inorder(root);
    cout << "\n";

    cout << "Postorder: ";
    postorder(root);
    cout << "\n";

    cout << "Level Order: ";
    levelOrder(root);
    cout << "\n";

    cout << "Height: " << height(root) << "\n";
    cout << "Total Nodes: " << countNodes(root) << "\n";
    cout << "Leaf Nodes: " << countLeafNodes(root) << "\n";

    int key;
    cout << "Enter key to search: ";
    cin >> key;

    if (searchNode(root, key)) {
        cout << "Node Found\n";
    } else {
        cout << "Node Not Found\n";
    }

    return 0;
}
