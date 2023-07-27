#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <vector>

class BPlusTree {
public:
    BPlusTree();
    void insert(int key, int value);
    int search(int key);
    void print();

private:
    struct Node {
        bool is_leaf;
        std::vector<int> keys;
        std::vector<int> values;
        Node* parent;
        Node* next;

        Node();
        Node(bool is_leaf);
    };

    Node* root;
    int degree;
    int height;

    void insertNonFull(Node* node, int key, int value);
    void splitChild(Node* parent, int index, Node* child);
    Node* findLeaf(Node* node, int key);
    int searchInNode(Node* node, int key);
    void printRecursive(Node* node, int level);
};

#endif
