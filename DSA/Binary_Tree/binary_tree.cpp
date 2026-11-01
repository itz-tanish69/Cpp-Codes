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

// Insert into the first open position in level order.
Node* insert(Node* root, int value) {
    if (root == NULL) {
        return new Node(value);
    }

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        if (current->left == NULL) {
            current->left = new Node(value);
            return root;
        }
        q.push(current->left);

        if (current->right == NULL) {
            current->right = new Node(value);
            return root;
        }
        q.push(current->right);
    }

    return root;
}

bool search(Node* root, int key) {
    if (root == NULL) {
        return false;
    }

    if (root->data == key) {
        return true;
    }

    return search(root->left, key) || search(root->right, key);
}

// Delete the first level-order match by replacing it with the deepest,
// rightmost node, then removing that deepest node.
bool deleteNode(Node*& root, int key) {
    if (root == NULL) {
        return false;
    }

    queue<pair<Node*, Node*> > q;
    q.push(make_pair(root, (Node*)NULL));

    Node* target = NULL;
    Node* deepest = NULL;
    Node* deepestParent = NULL;

    while (!q.empty()) {
        Node* current = q.front().first;
        Node* parent = q.front().second;
        q.pop();

        if (target == NULL && current->data == key) {
            target = current;
        }

        deepest = current;
        deepestParent = parent;

        if (current->left != NULL) {
            q.push(make_pair(current->left, current));
        }
        if (current->right != NULL) {
            q.push(make_pair(current->right, current));
        }
    }

    if (target == NULL) {
        return false;
    }

    target->data = deepest->data;

    if (deepestParent == NULL) {
        root = NULL;
    } else if (deepestParent->left == deepest) {
        deepestParent->left = NULL;
    } else {
        deepestParent->right = NULL;
    }

    delete deepest;
    return true;
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

Node* findMin(Node* root) {
    if (root == NULL) {
        return NULL;
    }

    Node* minimum = root;
    Node* leftMinimum = findMin(root->left);
    Node* rightMinimum = findMin(root->right);

    if (leftMinimum != NULL && leftMinimum->data < minimum->data) {
        minimum = leftMinimum;
    }
    if (rightMinimum != NULL && rightMinimum->data < minimum->data) {
        minimum = rightMinimum;
    }

    return minimum;
}

Node* findMax(Node* root) {
    if (root == NULL) {
        return NULL;
    }

    Node* maximum = root;
    Node* leftMaximum = findMax(root->left);
    Node* rightMaximum = findMax(root->right);

    if (leftMaximum != NULL && leftMaximum->data > maximum->data) {
        maximum = leftMaximum;
    }
    if (rightMaximum != NULL && rightMaximum->data > maximum->data) {
        maximum = rightMaximum;
    }

    return maximum;
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

    cout << "Enter values (inserted in level order): ";
    for (int i = 0; i < n; i++) {
        int value;
        cin >> value;
        root = insert(root, value);
    }

    cout << "\nBinary tree traversals:\n";
    printTraversals(root);
    printStats(root);

    int key;
    cout << "Enter key to search: ";
    cin >> key;
    cout << (search(root, key) ? "Key Found\n" : "Key Not Found\n");

    cout << "Enter key to delete: ";
    cin >> key;
    if (!deleteNode(root, key)) {
        cout << "Key Not Found; tree unchanged\n";
    }

    cout << "\nAfter deletion:\n";
    printTraversals(root);
    printStats(root);

    deleteTree(root);
    return 0;
}
