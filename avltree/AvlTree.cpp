//
// Created by soich on 18.12.2017.
//

#include "AvlTree.h"

using namespace ::std;

AvlTree::Node::Node(const int k, const int b) : key(k), balance(b), left(nullptr), right(nullptr) {};

AvlTree::Node::Node(const int k, const int b, Node *p, Node *l, Node *r)
        : key(k), balance(b), previous(p), left(l), right(r) {};

AvlTree::Node::~Node() {
    delete left;
    delete right;
}

AvlTree::~AvlTree() {
    delete root;
}


/********************************************************************
 * Search
 *******************************************************************/

bool AvlTree::search(const int value) const {
    if (root == nullptr) {
        return false;
    }
    return root->search(value);
}

bool AvlTree::Node::search(const int value) const {
    if (key == value) return true;
    if (value < key && left != nullptr) return left->search(value);
    if (value > key && right != nullptr) return right->search(value);
    return false;
}


/********************************************************************
 * Insert
 *******************************************************************/
void AvlTree::insert(int value) {
    auto position = root;
    if (root == nullptr) {
        auto node = new Node(value, 0);
        root = node;
        return;
    }
    while (true) {
        if (position == nullptr || position->key == value) {
            return;
        }
        if (position->key > value) {
            if (position->left == nullptr) {
                auto node = new Node(value, 0);
                node->previous = position;
                position->left = node;
                balanceIt(position->left);
            }
            position = position->left;
        }
        if (position->key < value) {
            if (position->right == nullptr) {
                auto node = new Node(value, 0);
                node->previous = position;
                position->right = node;
                balanceIt(position->right);
            }
            position = position->right;
        }
    }

}
/*
void AvlTree::Node::insert(int value) {
    if (value == key)
        return;
    if (value < key) {
        if (left == nullptr) {
            left = new Node(value, 0);
            // balance method
        } else {
            left->insert(value);
        }
    }
    if (value > key) {
        if (right == nullptr) {
            right = new Node(value, 0);

        } else {
            right->insert(value);
        }
    }
}
*/
/********************************************************************
 * Balance the Tree
 *******************************************************************/


void AvlTree::balanceIt(Node *node) {
    auto position = node;
    while (position != root) {
        if (position == position->previous->left) {
            position->previous->balance -= 1;
        } else {
            position->previous->balance += 1;
        }
        if (position->previous->balance == 0) {
            break;
        }
        position = position->previous;
    }
}

int AvlTree::height() {
    return root->balance;
}


/********************************************************************
 * Traversal
 *******************************************************************/

vector<int> *AvlTree::preorder() const {
    if (root == nullptr)
        return nullptr;
    return root->preorder();
}

vector<int> *AvlTree::Node::preorder() const {
    auto vec = new vector<int>();
    // Wurzel in vec
    vec->push_back(key);
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->preorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->preorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    return vec;
}

vector<int> *AvlTree::inorder() const {
    if (root == nullptr)
        return nullptr;
    return root->inorder();
}

vector<int> *AvlTree::Node::inorder() const {
    auto vec = new vector<int>();
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->inorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // Wurzel in vec
    vec->push_back(key);
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->inorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    return vec;
}

vector<int> *AvlTree::postorder() const {
    if (root == nullptr)
        return nullptr;
    return root->postorder();
}

vector<int> *AvlTree::Node::postorder() const {
    auto vec = new vector<int>();
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->postorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->postorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    // Wurzel in vec
    vec->push_back(key);
    return vec;
}

