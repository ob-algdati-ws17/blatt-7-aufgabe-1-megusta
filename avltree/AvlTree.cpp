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


void AvlTree::insert(const int value) {
    if (root == nullptr) {
        auto node = new Node(value, 0);
        root = node;
    } else {
        insert(value, root);
    }
}

void AvlTree::insert(const int value, Node *node) {
    if (node->key == value) {
        return;
    }

    if (value < node->key) {
        if (node->left == nullptr) {
            auto newNode = new Node(value, 0);
            node->left = newNode;
            node->left->previous = node;
            node->balance -= 1;
            if (node->balance != 0) {
                upIn(node);
            }
        } else {
            insert(value, node->left);
        }
    } else {
        if (node->right == nullptr) {
            auto newNode = new Node(value, 0);
            node->right = newNode;
            node->right->previous = node;
            node->balance += 1;
            if (node->balance != 0) {
                upIn(node);
            }
        } else {
            insert(value, node->right);
        }

    }
}


/********************************************************************
 * Remove
 *******************************************************************/

void AvlTree::remove(const int value) {
    bool found = false;
    found = root->search(value);
    if (found) {
        if (root != nullptr) {
            remove(value, root);
        }
    }
};

void AvlTree::remove(const int value, Node *node) {
    if (node->key == value) {
        if (node->left == nullptr && node->right == nullptr) {
            removeNodeNoChilds(node);
        } else if (node->left != nullptr && node->right == nullptr) {
            removeNodeOneChild(node);
        } else if (node->right != nullptr && node->left == nullptr) {
            removeNodeOneChild(node);
        } else if (node->right != nullptr && node->left != nullptr) {
            removeNodeTwoChilds(node);
        }
    } else if (node->key > value) {
        remove(value, node->left);
    } else if (node->key < value) {
        remove(value, node->right);
    }
}

void AvlTree::removeNodeNoChilds(Node *removeNode) {
    auto previous = removeNode->previous;

    if (previous != nullptr) {
        int balance = previous->balance;

        // remove the left or the right node
        if (previous->left == removeNode) {
            previous->left = nullptr;
            balance += 1;
        } else if (previous->right == removeNode) {
            previous->right = nullptr;
            balance -= 1;
        }


        // update the balance of the tree
        if (balance == 0) {
            previous->balance = balance;
            upOut(previous);

        } else if(balance == -1){
            previous->balance = balance;
            upOut(previous);
        } else if(balance == 1){
            previous->balance = balance;

        }
        else if (balance == 2) {
            auto otherTree = previous->right;
            if (otherTree->left == nullptr) {
                rotateLeft(previous);
            } else {
                rotateRight(otherTree);
                rotateLeft(previous);
            }

            if (previous->previous->balance == 0) {
                upOut(previous->previous);
            }
        } else if (balance == -2) {
            auto otherTree = previous->left;
            if (otherTree->right == nullptr) {
                rotateRight(previous);
            } else {
                rotateLeft(otherTree);
                rotateRight(previous);

            }

            if (previous->previous->balance == 0) {
                upOut(previous->previous);
            }
        }
    } else {
        root = nullptr;
    }
    delete removeNode;
}


void AvlTree::removeNodeOneChild(Node *node) {
    auto previous = node->previous;
    // child is left
    if (node->left != nullptr) {
        auto child = node->left;
        node->key = child->key;
        node->left = nullptr;
        node->balance = 0;
        if (previous != nullptr) {
            upOut(node);
        }
        delete child;
    }
        // child is right
    else {
        auto child = node->right;
        node->key = child->key;
        node->right = nullptr;
        node->balance = 0;
        if (previous != nullptr) {
            upOut(node);
        }
        delete child;
    }
}

void AvlTree::removeNodeTwoChilds(Node *removeNode) {
    auto symmetricPre = removeNode->left;
    while (symmetricPre->right != nullptr) {
        symmetricPre = symmetricPre->right;
    }

    int nodeKey = removeNode->key;
    removeNode->key = symmetricPre->key;
    symmetricPre->key = nodeKey;


    if (symmetricPre->left == nullptr && symmetricPre->right == nullptr) {
        removeNodeNoChilds(symmetricPre);
    } else {
        removeNodeOneChild(symmetricPre);
    }
}


/********************************************************************
 * Balance the Tree
 *******************************************************************/
void AvlTree::upIn(Node *node) {
    if (node != nullptr && node->previous != nullptr) {
        auto prev = node->previous;

        if (node == prev->left) {
            if (prev->balance == -1) {
                if (node->balance == -1) {
                    rotateRight(prev);
                } else {
                    rotateLeft(node);
                    rotateRight(prev);
                }
            } else if (prev->balance == 0) {
                prev->balance = -1;
                upIn(prev);
            } else {
                prev->balance = 0;
            }
        } else if (node == prev->right) {
            if (prev->balance == 1) {
                if (node->balance == 1) {
                    rotateLeft(prev);
                } else {
                    rotateRight(node);
                    rotateLeft(prev);
                }
            } else if (prev->balance == 0) {
                prev->balance = 1;
                upIn(prev);
            } else {
                prev->balance = 0;
            }
        }
    }
}


void AvlTree::upOut(Node *node) {
    if(node == root){
        return;
    }
    auto previous = node->previous;

    
    if (node == previous->left) {
        if (previous->balance == -1) {
            previous->balance = 0;
            upOut(previous);
        } else if (previous->balance == 0) {
            previous->balance = 1;
        } else {
            if (previous->right->balance == 0) {
                rotateLeft(previous);
                node->balance = 0;
                previous->balance = 1;
                previous->previous->balance = -1;
            } else if (previous->right->balance == 1) {
                rotateLeft(previous);
                node->balance = 0;
                previous->balance = 0;
                previous->previous->balance = 0;
                upOut(previous->previous);
            } else {
                int controlBalance = previous->right->left->balance;
                rotateRight(previous->right);
                rotateLeft(previous);
                root->balance = 0;
                root->left->left->balance = 0;
                root->left->balance = 0;
                root->right->balance = 0;
                if (controlBalance == 1) {
                    root->left->balance = -1;
                } else if (controlBalance == -1) {
                    root->right->balance = 1;
                }
                upOut(previous->previous);
            }
        }
        
        
    } else {
        if (previous->balance == 1) {
            previous->balance = 0;
            upOut(previous);
        } else if (previous->balance == 0) {
            previous->balance = -1;
        } else {
            if (previous->left->balance == 0) {
                rotateRight(previous);
                node->balance = 0;
                previous->balance = -1;
                previous->previous->balance = 1;
            } else if (previous->left->balance == -1) {
                rotateRight(previous);
                node->balance = 0;
                previous->balance = 0;
                previous->previous->balance = 0;
                upOut(previous->previous);
            } else {
                int controlBalance = previous->left->right->balance;
                rotateLeft(previous->left);
                rotateRight(previous);
                auto root = previous->previous;
                root->balance = 0;
                root->right->right->balance = 0;
                root->left->balance = 0;
                root->right->balance = 0;
                if (controlBalance == 1) {
                    root->left->balance = -1;
                } else if (controlBalance == -1) {
                    root->right->balance = 1;
                }
                upOut(previous->previous);
            }
        }
    }
}


int AvlTree::height() {
    return root->balance;
}


/********************************************************************
 * Rotate
 *******************************************************************/

void AvlTree::rotateRight(Node *unbalancedNode) {
    auto prev = unbalancedNode->previous;
    auto left = unbalancedNode->left;

    // unbalanced node is root
    if (prev == nullptr) {
        root = left;
        left->previous = nullptr;
    } else {
        if (prev->left == unbalancedNode) {
            prev->left = left;
        } else {
            prev->right = left;
        }
        left->previous = prev;
    }

    unbalancedNode->left = left->right;
    left->right = unbalancedNode;
    unbalancedNode->previous = left;

    left->balance += 1;
    unbalancedNode->balance += 1;

}

void AvlTree::rotateLeft(Node *unbalancedNode) {
    auto prev = unbalancedNode->previous;
    auto right = unbalancedNode->right;

    if (prev == nullptr) {
        root = right;
        right->previous = nullptr;
    } else {
        if (prev->right == unbalancedNode) {
            prev->right = right;
        } else {
            prev->left = right;
        }
        right->previous = prev;
    }


    unbalancedNode->right = right->left;
    right->left = unbalancedNode;
    unbalancedNode->previous = right;

    right->balance -= 1;
    unbalancedNode->balance -= 1;

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

