#include <iostream>

#include "BST.h"
using namespace std;
int main()
{
    BST<float> tree;

    // tree.print(inorder);
    // tree.print(preorder);
    // tree.print(postorder);
    /*
        tree.insert(3);
        tree.insert(1);
        tree.insert(5);
        tree.insert(0);
        tree.insert(2);
        tree.insert(4);
        tree.insert(8);
        tree.insert(6);
        tree.insert(7);
        tree.insert(9);
    */
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(7);
    tree.insert(6);
    tree.insert(13);
    tree.insert(14);

    // BSTNode<float> *tmp = tree.search(5);
    tree.remove(5);
    tree.print(inorder);
    tree.print(preorder);
    tree.print(postorder);

    /*
        BSTNode<float> *tmp = tree.search(15);
        BSTNode<float> *tmp2 = tree.getSuccessor(tmp, inorder);
        cout<<"INORDER\n";
        if (tmp2 == NULL)
        {
            cout << "\tNULL\n";
        }
        else
        {
            cout << "\t"<<tmp2->data<<"\n";
        }
        tmp2 = tree.getSuccessor(tmp, preorder);
        cout<<"PREORDER\n";
        if (tmp2 == NULL)
        {
            cout << "\tNULL\n";
        }
        else
        {
            cout << "\t"<<tmp2->data<<"\n";
        }
        tmp2 = tree.getSuccessor(tmp, postorder);
        cout<<"POSTORDER\n";
        if (tmp2 == NULL)
        {
            cout << "\tNULL\n";
        }
        else
        {
            cout << "\t"<<tmp2->data<<"\n";
        }
    */
    return 0;
}
