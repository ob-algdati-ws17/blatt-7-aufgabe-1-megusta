// Created by soich on 18.12.2017.
//
#ifndef BLATT_7_AUFGABE_1_MEGUSTA_AVLTREE_H
#define BLATT_7_AUFGABE_1_MEGUSTA_AVLTREE_H

#include <iostream>
#include <vector>

using namespace std;

class AvlTree {

private:

    struct Node {
        const int key;
        Node *left = nullptr;
        Node *right = nullptr;
        Node(const int);
        Node(const int, Node *, Node *);
        ~Node();
        bool search(const int) const;
        void insert(const int);
        Node *remove(const int);
        vector<int> *preorder() const; // (Hauptreihenfolge)
        vector<int> *inorder() const; // (Symmetrische Reihenfolge)
        vector<int> *postorder() const; // (Nebenreihenfolge)
    };

    Node *root = nullptr;

public:

    ~AvlTree();

    bool search(const int) const;

    void insert(const int);

    void remove(const int);

    vector<int> *preorder() const; // (Hauptreihenfolge)
    vector<int> *inorder() const; // (Symmetrische Reihenfolge)
    vector<int> *postorder() const; // (Nebenreihenfolge)

    friend Node *findSymSucc(Node *);
    friend ostream &operator<<(ostream &, const AvlTree &);

};



#endif //BLATT_7_AUFGABE_1_MEGUSTA_AVLTREE_H
