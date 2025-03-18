#include <iostream>
#include <algorithm>
#include <QApplication>
#include "mainwindow.h"
#include "BinarySearchTree.h"

int main(int argc, char *argv[] ) {
    QApplication a(argc, argv);
    MainWindow wnd;
    BinarySearchTree bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(20);
    bst.insert(3);
    bst.insert(7);

    std::cout << "In-order Traversal: "; // обход по порядку
    std::vector<int> res = bst.inOrderTraversal();

    auto print = [](int value) {
        std::cout << value << " ";
    };

    std::for_each(res.begin(), res.end(), print);
 
    std::cout << std::endl;
    wnd.show();
    return a.exec();
}
