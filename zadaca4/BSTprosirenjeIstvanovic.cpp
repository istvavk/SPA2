#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Node
{
    int key;
    Node *left, *right, *parent;
};

class BST
{
public:
    Node *root;

    Node* insert(int key, Node *node)
    {
        if (node == NULL)
        {
            node = new Node;
            node->key = key;
            node->left = node->right = node->parent = NULL;
        } else if (key > node->key)
        {
            node->right = insert(key, node->right);
            node->right->parent = node;
        } else
        {
            node->left = insert(key, node->left);
            node->left->parent = node;
        }
        return node;

    }

    void inorder(Node *node, vector<int>& nodes)
    {
        if (node == nullptr)
            return;
        inorder(node->left, nodes);
        nodes.push_back(node->key);
        inorder(node->right, nodes);
    }

    Node* search(int key, Node *node)
    {
        if (node == NULL || key == node->key)
            return node;
        if (key > node->key)
            return search(key, node->right);
        return search(key, node->left);
    }

    Node* find_min(Node *node)
    {
        if (node == NULL)
            return NULL;
        if (node->left == NULL)
            return node;
        return find_min(node->left);
    }

    Node* find_max(Node *node)
    {
        if (node == NULL)
            return NULL;
        if (node->right == NULL)
            return node;
        return find_min(node->right);
    }

    Node* successor(Node *node)
    {
        if (node->right != NULL)
            return find_min(node->right);

        Node *parent = node->parent;
        while (parent != NULL && node == parent->right) {
            node = parent;
            parent = node->parent;
        }

        return parent;
    }

    Node* predecessor(Node *node)
    {
        if (node->left != NULL)
            return find_max(node->left);

        Node *parent = node->parent;
        while (parent != NULL && node == parent->left) {
            node = parent;
            parent = node->parent;
        }

        return parent;
    }

    BST() : root(NULL) {}

    void print()
    {
        vector<int> temp{};
        inorder(root, temp);
        for (int key : temp)
            cout << key << " ";
    }

    void insert(int key)
    {
        root = insert(key, root);
    }

    bool search(int key)
    {
        return search(key, root);
    }

    int find_min()
    {
        Node *node = find_min(root);
        if (node != NULL)
            return node->key;
        return -1;
    }

    int find_max()
    {
        Node *node = find_max(root);
        if (node != NULL)
            return node->key;
        return -1;
    }

    int successor(int key)
    {
        Node *node = search(key, root);
        if (node == NULL)
            return -1;
        node = successor(node);
        if (node == NULL)
            return -1;
        return node->key;
    }

    int predecessor(int key)
    {
        Node *node = search(key, root);
        if (node == NULL)
            return -1;
        node = predecessor(node);
        if (node == NULL)
            return -1;
        return node->key;
    }
};

// Zadatak1

int countNodes(Node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

bool structurallyEqual(BST T1, BST T2) {
    int count1 = countNodes(T1.root);
    int count2 = countNodes(T2.root);
    return count1 == count2;
}

// Zadatak2

void nthPower(Node *node, int n)
{
    if (node == NULL) {
        return;
    }
    node->key = pow(node->key, n);
    nthPower(node->left, n);
    nthPower(node->right, n);
}

BST nthPowerBST(BST T, int n)
{
    nthPower(T.root, n);
    return T;
}

int main() {
    cout << "Zadatak 1:" << endl;
    BST T1, T2;
    T1.insert(3);
    T1.insert(2);
    T1.insert(1);
                                    //TEST CASE1: NISU STRUKTURALNO JEDNAKI
    T2.insert(3);
    T2.insert(1);
    T2.insert(2);
    T2.insert(5);

    if (structurallyEqual(T1, T2))
        cout << "T1 i T2 su strukturalno jednaki" << endl;
    else
        cout << "T1 i T2 nisu strukturalno jednaki" << endl;

    BST T3, T4;
    T3.insert(3);
    T3.insert(2);
    T3.insert(1);
                                    //TEST CASE2: JESU STRUKTURALNO JEDNAKI
    T4.insert(3);
    T4.insert(2);
    T4.insert(1);

    if (structurallyEqual(T3, T4))
        cout << "T3 i T4 su strukturalno jednaki" << endl;
    else
        cout << "T3 i T4 nisu strukturalno jednaki" << endl;


    cout << "Zadatak 2:" << endl;
    BST T;
    T.insert(5);
    T.insert(3);
    T.insert(7);
    T.insert(1);
    T.insert(4);
    T.insert(9);

    BST BSTpow2 = nthPowerBST(T, 2);
    BSTpow2.print();
    cout << endl;
}
