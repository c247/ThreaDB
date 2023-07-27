#include "BPlusTree.h"
#include <iostream>

BPlusTree::Node::Node() : is_leaf(false), parent(nullptr), next(nullptr) {}

BPlusTree::Node::Node(bool is_leaf) : is_leaf(is_leaf), parent(nullptr), next(nullptr) {}

BPlusTree::BPlusTree() : root(nullptr), degree(3), height(0) {}

void BPlusTree::insert(int key, int value) {
    if (root == nullptr) {
        root = new Node(true);
        root->keys.push_back(key);
        root->values.push_back(value);
    } else {
        if (root->keys.size() == 2 * degree - 1) {
            Node* new_root = new Node(false);
            new_root->next = root;
            splitChild(new_root, 0, root);
            root = new_root;
        }
        insertNonFull(root, key, value);
    }
}

void BPlusTree::insertNonFull(Node* node, int key, int value) {
    int i = node->keys.size() - 1;
    if (node->is_leaf) {
        node->keys.push_back(0);
        node->values.push_back(0);
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            node->values[i + 1] = node->values[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->values[i + 1] = value;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        if (node->keys[i] == key) {
            return;
        }
        if (node->next->keys.size() == 2 * degree - 1) {
            splitChild(node, i, node->next);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->next, key, value);
    }
}

void BPlusTree::splitChild(Node* parent, int index, Node* child) {
    Node* new_child = new Node(child->is_leaf);
    for (int j = 0; j < degree - 1; j++) {
        new_child->keys.push_back(child->keys[j + degree]);
        new_child->values.push_back(child->values[j + degree]);
    }
    if (!child->is_leaf) {
        for (int j = 0; j < degree; j++) {
            new_child->next = child->next;
            child->keys.pop_back();
            child->values.pop_back();
        }
    }
    child->keys.push_back(0);
    child->values.push_back(0);
    for (int j = parent->keys.size(); j > index; j--) {
        parent->keys[j] = parent->keys[j - 1];
        parent->values[j] = parent->values[j - 1];
    }
    parent->keys[index] = child->keys[degree - 1];
    parent->values[index] = child->values[degree - 1];
    parent->keys.push_back(0);
    parent->values.push_back(0);
    parent->next = new_child;
}

BPlusTree::Node* BPlusTree::findLeaf(Node* node, int key) {
    int i = 0;
    while (!node->is_leaf) {
        while (i < node->keys.size() && key >= node->keys[i]) {
            i++;
        }
        node = node->next ? node->next : node;
    }
    return node;
}

int BPlusTree::searchInNode(Node* node, int key) {
    int i = 0;
    while (i < node->keys.size() && key > node->keys[i]) {
        i++;
    }
    return i;
}

int BPlusTree::search(int key) {
    if (root == nullptr) {
        return -1;
    }
    Node* leaf = findLeaf(root, key);
    int index = searchInNode(leaf, key);
    if (index < leaf->keys.size() && leaf->keys[index] == key) {
        return leaf->values[index];
    }
    return -1;
}

void BPlusTree::printRecursive(Node* node, int level) {
    if (node == nullptr) {
        return;
    }
    std::cout << "Level " << level << ": ";
    for (int i = 0; i < node->keys.size(); i++) {
        std::cout << node->keys[i] << " ";
    }
    std::cout << std::endl;
    if (!node->is_leaf) {
        printRecursive(node->next, level + 1);
    }
}

void BPlusTree::print() {
    if (root == nullptr) {
        std::cout << "The B+ tree is empty." << std::endl;
    } else {
        printRecursive(root, 0);
    }
}
