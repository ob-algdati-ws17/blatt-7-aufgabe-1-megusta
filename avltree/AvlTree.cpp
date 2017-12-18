//
// Created by soich on 18.12.2017.
//
# include AvlTree.h

using namespace ::std;

AvlTree::Node::Node(const int k ) : key(k) {};

AvlTree::Node::Node(const int k, Node *l, Node *r)
        : key(k), left(l), right(r) {};

AvlTree::Node::~Node(){
    delete left;
    delete rigth;
}

AvlTree::~AvlTree(){
    delete root;
}
