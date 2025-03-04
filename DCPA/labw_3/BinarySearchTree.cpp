#include <iostream>
#include <vector>
#include "BinarySearchTree.h"
#include "basicactions.h"
void BinarySearchTree::insert(int value) {
	root = insertNode(std::move(root), value);
}

std::vector<int> BinarySearchTree::inOrderTraversal() const {
	std::vector<int> list;
	inOrderTraversalNode(root.get(), list);
	return list;
}

std::vector<int> BinarySearchTree::preOrderTraversal() const {
    std::vector<int> list;
    preOrderTraversalNode(root.get(), list);
    return list;
}
std::vector<int> BinarySearchTree::postOrderTraversal() const {
    std::vector<int> list;
    postOrderTraversalNode(root.get(), list);
    return list;
}
bool BinarySearchTree::findNode (int value) {
    std::vector <int> list;
    list = inOrderTraversal();
    try{
        arrayAriphmetics::findFirstLooked<std::vector<int>, int>(list, value, list.size());
    }
    catch(std::exception){
        return 0;
    }
    return 1;
}


std::unique_ptr<Node> BinarySearchTree::insertNode(std::unique_ptr<Node> node, int value) {
	if (!node) {
		return std::make_unique<Node>(value);
	}
	if (value < node->data) {
		node->left = insertNode(std::move(node->left), value);
	}
	else if (value > node->data) {
		node->right = insertNode(std::move(node->right), value);
	}
	return node;
}

void BinarySearchTree::deleteNode (int value) {
    BinarySearchTree temp;
    if(findNode(value)){
        std::vector <int> list;
        list = inOrderTraversal();
        for (auto current : list) {
            if(current != value)
            temp.insert(current);
        }
        root = std::move(temp.root);
    }
}
void BinarySearchTree::inOrderTraversalNode(Node* node, std::vector<int> &list) const {
	if (!node) {
		return;
	}
	
	inOrderTraversalNode(node->left.get(), list);
	list.push_back(node->data);
	inOrderTraversalNode(node->right.get(), list);

}

void BinarySearchTree::preOrderTraversalNode(Node* node, std::vector<int> &list) const {
    if (!node) {
        return;
    }
    list.push_back(node->data);
    inOrderTraversalNode(node->left.get(), list);
    inOrderTraversalNode(node->right.get(), list);

}
void BinarySearchTree::postOrderTraversalNode(Node* node, std::vector<int> &list) const {
    if (!node) {
        return;
    }
    inOrderTraversalNode(node->left.get(), list);
    inOrderTraversalNode(node->right.get(), list);
    list.push_back(node->data);
}
