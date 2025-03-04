#pragma once

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <memory>
#include <vector>
#include "basicactions.h"
// Узел дерева
struct Node {
    int data;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Класс бинарного поискового дерева
class BinarySearchTree {
public:
    void insert(int value);
    bool findNode (int value);
    void deleteNode (int value);
    std::vector<int> inOrderTraversal() const; // обход по порядку
    std::vector<int> preOrderTraversal() const;
    std::vector<int> postOrderTraversal() const;
private:
    std::unique_ptr<Node> root;

    std::unique_ptr<Node> insertNode(std::unique_ptr<Node> node, int value);
    void preOrderTraversalNode(Node* node, std::vector<int> &list) const;
     void postOrderTraversalNode(Node* node, std::vector<int>&) const;
    void inOrderTraversalNode(Node* node, std::vector<int>&) const;
};

#endif // !BINARY_TREE_H

