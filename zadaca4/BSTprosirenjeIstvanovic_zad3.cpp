#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node
{
    int key;
    Node *left, *right, *parent;
};

class BST
{
    Node* root;

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

    bool nodesEqual(Node *node1, Node *node2) {
        if (node1 == nullptr && node2 == nullptr)
            return true;

        if (node1 != nullptr && node2 != nullptr) {
            return (nodesEqual(node1->left, node2->left) && nodesEqual(node1->right, node2->right));
        }

        return false;
    }

    void NodeAdd(Node *node1, Node *node2) {
        if (node1 == nullptr || node2 == nullptr) {
            return;
        }
        NodeAdd(node1->left, node2->left);
        node1->key += node2->key;
        NodeAdd(node1->right, node2->right);
    }

    Node* buildTree(vector<int>& nodes, int start, int end, Node* parent) {
        if (start > end)
            return nullptr;
        int mid = (start + end) / 2;
        Node* node = new Node{nodes[mid], nullptr, nullptr, nullptr};
        node->parent = parent;
        node->left = buildTree(nodes, start, mid - 1, node);
        node->right = buildTree(nodes, mid + 1, end, node);
        return node;
    }

public:
    BST() : root(NULL) {}

    BST(const BST &T) : BST{} {
        vector<int> copy {};
        inorder(T.root, copy);
        for (int i : copy)
            insert(i);
    }

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

    bool structurallyEqual(BST T1, BST T2) {
        return nodesEqual(T1.root, T2.root);
    }


    BST BSTadd(BST T1, BST T2) {
        if (structurallyEqual(T1, T2)) {
            BST T3(T1);
            NodeAdd(T3.root, T2.root);
            return T3;
        } else {
            if (T1.root == nullptr) {
                return T2;
            } else {
                return T1;
            }
        }
    }
};

int main()
{
    BST T1;
    T1.insert(5);
    T1.insert(3);
    T1.insert(1);
    T1.insert(4);
    T1.insert(7);
    T1.insert(9);

    T1.print();

    cout << endl;

    BST T2;
    T2.insert(10);
    T2.insert(5);
    T2.insert(2);
    T2.insert(8);
    T2.insert(14);
    T2.insert(16);

    T2.print();

    cout << endl;

    cout << T2.structurallyEqual(T1, T2) << endl;

    // zbroj
    T1.BSTadd(T1, T2).print();
    
    // nisu strukturalno jednaki
    
    BST T3;
    T3.insert(5);
    T3.insert(3);
    T3.insert(1);
    T3.insert(4);
    T3.insert(7);
    T3.insert(9);

    T3.print();

    cout << endl;

    BST T4;
    T4.insert(10);
    T4.insert(5);
    T4.insert(2);
    T4.insert(8);
    T4.insert(14);

    T4.print();

    cout << endl;

    cout << T3.structurallyEqual(T3, T4) << endl;

    BST T5 = T3.BSTadd(T3, T4);

    T5.print();
}

