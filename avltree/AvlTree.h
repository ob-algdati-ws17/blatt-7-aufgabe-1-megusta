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
        int balance;
        Node *left = nullptr;
        Node *right = nullptr;
        Node *previous = nullptr;

        Node(const int, int);
        Node(const int, int, Node *, Node *, Node *);
        ~Node();

        vector<int> *preorder() const; // (Hauptreihenfolge)
        vector<int> *inorder() const; // (Symmetrische Reihenfolge)
        vector<int> *postorder() const; // (Nebenreihenfolge)

        bool search(const int) const;
        void insert(const int);
        Node *remove(const int);
    };

    Node *root = nullptr;

public:

    ~AvlTree();

    void upIn(Node *);

    void upOut(Node *);

    int height();

    bool search(const int) const;

    void insert(const int);

    void insert(const int, Node *);

    void remove(const int);

    void remove(const int, Node *);

    void removeNodeBothLeafs(Node *);

    void rotateRight(Node *);

    void rotateLeft(Node *);

    vector<int> *preorder() const; // (Hauptreihenfolge)
    vector<int> *inorder() const; // (Symmetrische Reihenfolge)
    vector<int> *postorder() const; // (Nebenreihenfolge)

    friend Node *findSymSucc(Node *);
    friend ostream &operator<<(ostream &, const AvlTree &);

};



#endif //BLATT_7_AUFGABE_1_MEGUSTA_AVLTREE_H
