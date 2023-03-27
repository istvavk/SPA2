#include <iostream>
#include <algorithm>

using namespace std;

struct Node {
    int key;
    int h;
    Node *left, *right, *parent;

    Node(int key) : key(key), h(1), left(nullptr), right(nullptr), parent(nullptr) {}
};

int height(Node *node) {
    if (node == nullptr) {
        return 0;
    }
    return node->h;
}

int balanceOfNode(Node *node) {
    if (node == nullptr) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

void updateHeight(Node *node) {
    node->h = 1 + max(height(node->left), height(node->right));
}

Node* rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    if (T2 != nullptr) {
        T2->parent = y;
    }

    x->parent = y->parent;
    y->parent = x;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node* leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    if (T2 != nullptr) {
        T2->parent = x;
    }

    y->parent = x->parent;
    x->parent = y;

    updateHeight(x);
    updateHeight(y);

    return y;
}

Node* insert(Node *node, int key) {
    if (node == nullptr) {
        return new Node(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
        node->left->parent = node;
    } else {
        node->right = insert(node->right, key);
        node->right->parent = node;
    }

    updateHeight(node);

    int balance = balanceOfNode(node);

    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }

    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inorder(Node *node) {
    if (node == nullptr) {
        return;
    }

    inorder(node->left);
    cout << node->key << " ";
    inorder(node->right);
}

int main() {
    Node *root = nullptr;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    inorder(root);
    cout << endl;

    return 0;
}

