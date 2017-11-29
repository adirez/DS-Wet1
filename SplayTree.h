//
// Created by adire on 27-Nov-17.
//

#ifndef WET1_SPLAYTREE_H
#define WET1_SPLAYTREE_H

#include <assert.h>
#include "Exceptions.h"

template<class T>
class SplayTree {
private:

    class Node {
    private:
        T *data;
        Node *parent;
        Node *right_son;
        Node *left_son;

        friend class SplayTree;

    public:
        Node(T data, Node *parent);

        ~Node();
    };

    Node *root;
    Node *min;
    Node *max;
    int size;

    void splay(Node *node);

    void zig(Node *node);

    void zigZag(Node *node);

    void zigZig(Node *node);

    template<class function>
    void inOrderAux(Node *cur_node, const function &func) const;

    void postOrderAuxRemoval(Node *cur_node);

    Node *findAux(Node *cur_node, const T &key);

public:
    SplayTree();

    SplayTree(const SplayTree &splay_tree) = delete;

    SplayTree &operator=(const SplayTree &splay_tree) = delete;

    ~SplayTree();

    T &find(const T &key);

    void insert(const T &key);

    void remove(const T &key);

    template<class function>
    void inOrder(const function &func) const;
};

/**
 * Public functions
 */

template<class T>
SplayTree<T>::SplayTree() : root(nullptr), min(nullptr), max(nullptr), size(0) {}

template<class T>
SplayTree<T>::~SplayTree() {
    postOrderAuxRemoval(root);
}

template<class T>
T &SplayTree<T>::find(const T &key) {
    if (key == nullptr) {
        throw NullParameter();
    }
    Node *found_node = findAux(root, key);
    splay(found_node);
    if (found_node->data != key) {
        return nullptr;
    }
    return found_node->data;
}

template<class T>
void SplayTree<T>::insert(const T &key) {
    Node *found_node = findAux(root, key);
    if (found_node != nullptr && key == *found_node->data) {
        throw KeyAlreadyExists();
    }
    auto *to_insert = new Node(key, found_node);
    if (found_node != nullptr) {
        if(key < *found_node->data){
            found_node->left_son = to_insert;
        } else {
            found_node->right_son = to_insert;
        }
    }
    splay(to_insert);
    if (found_node == nullptr) {
        root = to_insert;
    }
    //updating min/max of the tree
    if (root->right_son == nullptr) {
        max = root;
    }
    if (root->left_son == nullptr) {
        min = root;
    }
    size++;
}

template<class T>
void SplayTree<T>::remove(const T &key) {
    if (root == nullptr) {
        throw EmptyTree();
    }
    Node *found_node = findAux(root, key);
    if (key != root->data) {
        throw KeyNotFound();
    }
    splay(found_node);
    Node *left_son = root->left_son;
    Node *right_son = root->right_son;
    delete root;
    size--;

    if (size == 0) {
        //if the tree is empty we're done
        root = nullptr;
        max = nullptr;
        min = nullptr;
        return;
    } else if (left_son == nullptr) {

        //if there's no left son then the tree is the right son
        root = right_son;
        min = root;
        //in this case max won't change
        return;
    }
    //finding the max node of the left son and making it the new root
    Node *max_left = left_son;
    while (max_left->right_son != nullptr) {
        max_left = max_left->right_son;
    }
    root = max_left;
    if (right_son == nullptr) {
        max = root;
    }

    root->left_son = left_son;
    root->right_son = right_son;
    root->parent = nullptr;
}

template<class T>
template<class function>
void SplayTree<T>::inOrder(const function &func) const {
    inOrderAux(root, func);
}

/**
 * private functions
 */

template<class T>
void SplayTree<T>::splay(SplayTree::Node *node) {
    while (node != root && node->parent != root) {
        Node *p = node->parent;
        Node *g = p->parent;
         if ((node->data < p->data && node->data > g->data) ||
             (node->data > p->data && node->data < g->data)) {
            zigZag(node);
        } else {
            zigZig(node);
        }
    }
    if(node->parent == root && node->parent != nullptr){
        zig(node);
    }
}

template<class T>
void SplayTree<T>::zig(SplayTree::Node *node) {
    assert(node->parent == root);
    if (root->left_son == node) {
        if(node->right_son != nullptr){
            root->left_son->parent = root;
        }
        root->left_son = node->right_son;
        node->right_son = root;
    } else {
        if(node->left_son != nullptr){
            root->right_son->parent = root;
        }
        root->right_son = node->left_son;
        node->left_son = root;
    }
    node->parent = nullptr;
    root->parent = node;
    root = node;
}

template<class T>
void SplayTree<T>::zigZag(SplayTree::Node *node) {
    Node *p = node->parent;
    Node *g = p->parent;
    if (g == root) {
        root = node;
    }
    if (node->data < p->data) {
        //attach node's left son to g
        g->right_son = node->left_son;
        g->right_son->parent = g;
        //attach nodes right son to p
        p->left_son = node->right_son;
        p->left_son->parent = p;
        //attach both g and p to node
        node->left_son = g;
        node->right_son = p;
    } else {
        //attach node's right son to g
        g->left_son = node->right_son;
        g->left_son->parent = g;
        //attach nodes left son to p
        p->right_son = node->left_son;
        p->right_son->parent = p;
        //attach both g and p to node
        node->right_son = g;
        node->left_son = p;
    }
    node->parent = g->parent;
    if (g->data < g->parent->data) {
        //g was a left son
        g->parent->left_son = node;
    } else {
        g->parent->right_son = node;
    }
    p->parent = node;
    g->parent = node;
}

template<class T>
void SplayTree<T>::zigZig(SplayTree::Node *node) {
    Node *p = node->parent;
    Node *g = p->parent;
    if (g == root) {
        root = node;
    }
    if (node->data < p->data) {
        //attach p's right son to g
        g->left_son = p->right_son;
        g->left_son->parent = g;
        //attach nodes right son to p
        p->left_son = node->right_son;
        p->left_son->parent = p;
        //attach p to node
        node->right_son = p;
        p->parent = node;
        //attach g to p
        p->right_son = g;
    } else {
        //attach p's left son to g
        g->right_son = p->left_son;
        g->right_son->parent = g;
        //attach nodes left son to p
        p->right_son = node->left_son;
        p->right_son->parent = p;
        //attach p to node
        node->left_son = p;
        p->parent = node;
        //attach g to p
        p->left_son = g;
    }
    if (g->data < g->parent->data) {
        //g was a left son
        g->parent->left_son = node;
    } else {
        g->parent->right_son = node;
    }
    node->parent = g->parent;
    g->parent = p;
}

template<class T>
template<class function>
void SplayTree<T>::inOrderAux(SplayTree::Node *cur_node, const function &func) const {
    if (cur_node == nullptr) return;

    inOrderAux(cur_node->left_son, func);
    func(*cur_node->data);
    inOrderAux(cur_node->right_son, func);
}

template<class T>
void SplayTree<T>::postOrderAuxRemoval(SplayTree::Node *cur_node) {
    if (cur_node == nullptr) return;
    postOrderAuxRemoval(cur_node->left_son);
    postOrderAuxRemoval(cur_node->left_son);
    delete cur_node;
}

template<class T>
typename SplayTree<T>::Node *SplayTree<T>::findAux(SplayTree::Node *cur_node, const T &key) {
    if (cur_node == nullptr) return nullptr;
    if (key == *cur_node->data) {
        return cur_node;
    }
    if (key > *cur_node->data) {
        if (cur_node->right_son == nullptr) {
            return cur_node;
        }
        return findAux(cur_node->right_son, key);
    }
    if (key < *cur_node->data) {
        if (cur_node->left_son == nullptr) {
            return cur_node;
        }
        return findAux(cur_node->left_son, key);
    }
}

/**
 * Node functions
 */

template<class T>
SplayTree<T>::Node::Node(T data, Node *parent) : data(new T(data)), right_son(nullptr), left_son(nullptr),
                                                 parent(parent) {}

template<class T>
SplayTree<T>::Node::~Node() {
    delete data;
}


#endif //WET1_SPLAYTREE_H
