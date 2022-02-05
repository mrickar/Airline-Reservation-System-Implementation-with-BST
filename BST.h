#ifndef BST_H
#define BST_H

#include <iostream>

#include "BSTNode.h"

enum TraversalPlan
{
    preorder,
    inorder,
    postorder
};

template <class T>
class BST
{
public: // DO NOT CHANGE THIS PART.
    BST();
    BST(const BST<T> &obj);

    ~BST();

    BSTNode<T> *getRoot() const;
    bool isEmpty() const;
    bool contains(BSTNode<T> *node) const;

    void insert(const T &data);

    void remove(const T &data);
    void removeAllNodes();

    BSTNode<T> *search(const T &data) const;
    BSTNode<T> *getSuccessor(BSTNode<T> *node, TraversalPlan tp) const;

    void print(TraversalPlan tp = inorder) const;

    BST<T> &operator=(const BST<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(BSTNode<T> *node, TraversalPlan tp) const;
    BSTNode<T> *copyHelper(BSTNode<T> *tmp);
    BSTNode<T> *getSuccessorHelper(BSTNode<T> *curNode, BSTNode<T> *wanted, TraversalPlan tp, bool chc) const;
    void removeAllNodes(BSTNode<T> *curNode);
    BSTNode<T> *findMin(BSTNode<T> *curNode) const;
    BSTNode<T> *findParent(BSTNode<T> *curNode, BSTNode<T> *child, bool &isRight) const;

private: // DO NOT CHANGE THIS PART.
    BSTNode<T> *root;
};

#endif // BST_H

template <class T>
BST<T>::BST()
{
    /* TODO */
    root = NULL;
}

template <class T>
BST<T>::BST(const BST<T> &obj)
{
    /* TODO */
    root = copyHelper(obj.root);
}

template <class T>
BST<T>::~BST()
{
    /* TODO */
    removeAllNodes(root);
}

template <class T>
BSTNode<T> *BST<T>::getRoot() const
{
    /* TODO */
    return root;
}

template <class T>
bool BST<T>::isEmpty() const
{
    /* TODO */
    return root ? false : true;
}

template <class T>
bool BST<T>::contains(BSTNode<T> *node) const
{
    /* TODO */
    BSTNode<T> *cur = root;
    while (cur)
    {
        if (cur == node)
            return true;
        if (node->data > cur->data)
            cur = cur->right;
        else
            cur = cur->left;
    }
    return false;
}

template <class T>
void BST<T>::insert(const T &data)
{
    /* TODO */
    BSTNode<T> *cur = root;
    BSTNode<T> *newNode = new BSTNode<T>(data, NULL, NULL);
    if (root == NULL)
    {
        root = newNode;
        return;
    }
    while (cur)
    {
        if (data > cur->data)
        {
            if (cur->right)
            {
                cur = cur->right;
            }
            else
            {
                cur->right = newNode;
                break;
            }
        }
        else
        {
            if (cur->left)
            {
                cur = cur->left;
            }
            else
            {
                cur->left = newNode;
                break;
            }
        }
    }
}

template <class T>
void BST<T>::remove(const T &data)
{
    /* TODO */
    BSTNode<T> *delNode = search(data);
    if (delNode == NULL)
    {
        return;
    }

    BSTNode<T> *minOfRight = findMin(delNode);
    bool minNodeIsRight = false;

    BSTNode<T> *minOfRightParent = findParent(root, minOfRight, minNodeIsRight);

    if (root == delNode)
    {
        if (!delNode->left)
        {
            root = delNode->right;
        }
        else if (minOfRight)
        {
            minOfRightParent->left = minOfRight->right;
            minOfRight->left = root->left;
            minOfRight->right = root->right;
            root = minOfRight;
        }
        else
        {
            root = delNode->left;
        }
    }
    else
    {
        bool delNodeIsRight = false;
        BSTNode<T> *delNodeParent = findParent(root, delNode, delNodeIsRight);

        if (delNodeIsRight)
        {
            if (!delNode->left)
            {
                delNodeParent->right = delNode->right;
            }
            else if (minOfRight)
            {
                delNodeParent->right = minOfRight;
                minOfRight->left = delNode->left;

                if (minOfRightParent != delNode)
                {
                    minOfRightParent->left = minOfRight->right;
                    minOfRight->right = delNode->right;
                }
            }
            else
            {
                delNodeParent->right = delNode->left;
            }
        }
        else
        {
            if (!delNode->left)
            {
                delNodeParent->left = delNode->right;
            }
            else if (minOfRight)
            {
                delNodeParent->left = minOfRight;
                minOfRight->left = delNode->left;

                if (minOfRightParent != delNode)
                {
                    minOfRightParent->left = minOfRight->right;
                    minOfRight->right = delNode->right;
                }
            }
            else
            {
                delNodeParent->left = delNode->left;
            }
        }
    }
    delete delNode;
}
template <class T>
void BST<T>::removeAllNodes()
{
    /* TODO */
    removeAllNodes(root);
    root = NULL;
}

template <class T>
BSTNode<T> *BST<T>::search(const T &data) const
{
    /* TODO */
    BSTNode<T> *cur = root;
    while (cur)
    {
        if (data == cur->data)
        {
            return cur;
        }
        else if (data > cur->data)
        {
            cur = cur->right;
        }
        else
        {
            cur = cur->left;
        }
    }
    return NULL;
}

template <class T>
BSTNode<T> *BST<T>::getSuccessor(BSTNode<T> *node, TraversalPlan tp) const
{
    if (contains(node) == false)
    {
        return NULL;
    }
    BSTNode<T> *tmp = node;
    if (tp == inorder)
    {
        tmp = findMin(node);

        if (tmp)
        {

            return tmp;
        }
        else
        {
            bool isRight = true;
            tmp = node;
            while (tmp && isRight)
            {
                tmp = findParent(root, tmp, isRight);
            }

            return tmp;
        }
    }
    else if (tp == preorder)
    {
        if (node->left)
        {
            return node->left;
        }
        else if (node->right)
        {
            return node->right;
        }
        else
        {
            bool isRight = true;
            while (tmp && isRight)
            {
                tmp = findParent(root, tmp, isRight);
                if (!isRight)
                {
                    if (!tmp->right)
                    {
                        isRight = true;
                    }
                }
            }
            if (tmp)
            {
                return tmp->right;
            }
            return tmp;
        }
    }
    else if (tp == postorder)
    {
        if (node == root)
        {
            return NULL;
        }
        bool isRight = false;
        tmp = findParent(root, tmp, isRight);
        while (tmp && isRight == false)
        {
            if (tmp == root)
            {
                break;
            }
            if (tmp->right == NULL)
            {
                return tmp;
            }
            tmp = findParent(root, tmp, isRight);
        }
        if (isRight)
        {
            return tmp;
        }
        else
        {
            BSTNode<T> *tmp2 = tmp;
            while (tmp)
            {
                tmp2 = tmp;
                tmp = findMin(tmp);
            }
            return tmp2;
        }
    }
}

template <class T>
void BST<T>::print(TraversalPlan tp) const
{

    if (tp == inorder)
    {
        // check if the tree is empty?
        if (isEmpty())
        {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, inorder);
        std::cout << std::endl
                  << "}" << std::endl;
    }
    else if (tp == preorder)
    {
        /* TODO */
        if (isEmpty())
        {
            // the tree is empty.
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }
        std::cout << "BST_preorder{" << std::endl;
        print(root, preorder);
        std::cout << std::endl
                  << "}" << std::endl;
    }
    else if (tp == postorder)
    {
        /* TODO */
        if (isEmpty())
        {
            // the tree is empty.
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }
        std::cout << "BST_postorder{" << std::endl;
        print(root, postorder);
        std::cout << std::endl
                  << "}" << std::endl;
    }
}

template <class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs)
{
    /* TODO */
    if (this == &rhs)
        return *this;
    removeAllNodes();
    root = copyHelper(rhs.root);
    return *this;
}

template <class T>
void BST<T>::print(BSTNode<T> *node, TraversalPlan tp) const
{

    // check if the node is NULL?
    if (node == NULL)
        return;

    if (tp == inorder)
    {
        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left)
        {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->data;

        // finally, output comma (if needed) and the right subtree.
        if (node->right)
        {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    }
    else if (tp == preorder)
    {
        /* TODO */
        std::cout << "\t" << node->data;
        if (node->left)
        {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);
        if (node->right)
        {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);
    }
    else if (tp == postorder)
    {
        /* TODO */
        print(node->left, postorder);
        if (node->left)
        {
            std::cout << "," << std::endl;
        }
        print(node->right, postorder);
        if (node->right)
        {
            std::cout << "," << std::endl;
        }

        std::cout << "\t" << node->data;
    }
}
template <class T>
BSTNode<T> *BST<T>::copyHelper(BSTNode<T> *tocopy)
{
    if (!tocopy)
        return NULL;
    BSTNode<T> *newNode = new BSTNode<T>(tocopy->data, copyHelper(tocopy->left), copyHelper(tocopy->right));
    return newNode;
}
template <class T>
void BST<T>::removeAllNodes(BSTNode<T> *curNode)
{
    if (!curNode)
        return;
    removeAllNodes(curNode->left);
    removeAllNodes(curNode->right);
    delete curNode;
}
template <class T>
BSTNode<T> *BST<T>::findMin(BSTNode<T> *curNode) const
{
    if (curNode->right == NULL)
    {
        return NULL;
    }
    curNode = curNode->right;
    while (curNode->left)
    {
        curNode = curNode->left;
    }
    return curNode;
}
template <class T>
BSTNode<T> *BST<T>::findParent(BSTNode<T> *curNode, BSTNode<T> *child, bool &isRight) const
{
    if (child == root || child==NULL || curNode==NULL)
    {
        return NULL;
    }

    if (curNode->right == child)
    {
        isRight = true;
        return curNode;
    }
    else if (curNode->left == child)
    {
        isRight = false;
        return curNode;
    }
    if (child->data > curNode->data)
    {
        return findParent(curNode->right, child, isRight);
    }
    else
    {
        return findParent(curNode->left, child, isRight);
    }
}
