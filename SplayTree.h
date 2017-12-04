//
// Created by adire on 27-Nov-17.
//

#ifndef WET1_SPLAYTREE_H
#define WET1_SPLAYTREE_H

#include "Exceptions.h"

/**
 * a generic class for a SplayTree, with a nested class for a node. the class holds a pointer to the root of the tree, to the minimum and maximum nodes
 * and an integer to hold the tree size.
 */
template<class T>
class SplayTree {
private:

    /**
     * a nested class of the tree to represent a node in the tree. a node will hold a generic data (which in our case will hold a gladiator or a trainer)
     * and pointers to his sons and parent.
     */
    class Node {
    private:
        T *data;
        Node *parent;
        Node *right_son;
        Node *left_son;

        friend class SplayTree;

    public:
        /**
         * a constructor for a tree node.
         * @param data - the type the node will hold
         * @param parent - the parent under which the node will be listed as a son
         */
        Node(const T data, Node *parent);
        /**
         * a destructor for the node
         */
        ~Node();
    };

    Node *root;
    Node *min;
    Node *max;
    int size;

    //to make them unavailable to users (= delete does not work in g++)
    SplayTree &operator=(const SplayTree &splay_tree);
    SplayTree(const SplayTree &splay_tree);

    /**
     * splaying a node to the top of the tree to become a root. in the worst case scenario a node will be splayed through the entire height of the tree
     * which is averagely log(n) and thus splay will run in a complexity of log n
     * @param node - the node to splay
     */
    void splay(Node *node);
    /**
     * the types of splays (determined by the position and situation of the node to be splayed).
     * implemented as shown in the slides.
     * @param node - the node to be splayed
     */
    void zig(Node *node);
    void zigZag(Node *node);
    void zigZig(Node *node);
    /**
     * an aux function for inOrder that will receive a functor and perform it's action on any node by the sorting order. will run in O(n) since it runs
     * over 'n' nodes (not including the time of func itself)
     * @param cur_node - the root of the tree
     * @param func - the functor to perform on the nodes
     */
    template<class do_something>
    void inOrderAux(Node *cur_node, do_something &func);
    template<class do_something>
    // exactly similar to inOrderAux, only it will go in a reverse order. similarly, will run at O(n) (not considering the time of func)
    void inOrderAuxReverese(Node *cur_node, do_something &func);
    // an aux function for postOrderRemoval function. runs over 'n' nodes and thus run in a complexity of O(n)
    void postOrderAuxRemoval(Node *cur_node);
    // an aux function for 'find'. runs in an average complexity of log(n).
    Node *findAux(Node *cur_node, const T& key);
    // joins two trees when the right tree is bigger than the left tree. runs at O(log n) since it runs to the bottom right of the left tree.
    void join(Node *left_tree, Node *right_tree);

public:
    // an empty constructor for the tree
    SplayTree();
    // destructor for the tree
    ~SplayTree();
    // find an object in the tree and returns it's pointer. calls findAux and runs in O(log n).
    T &find(const T &key);
    // receives an object, sends it to 'find' to get the closest node and inserts it to the tree. after that, splays it to the root. runs in O(log n).
    void insert(const T &key);
    // receives a key of an object to be removed from the tree. finds it, splays to the root, removes and calls 'join' to merge the trees. runs in O(log n).
    void remove(const T &key);
    // iterates through the nodes in order. calls inOrderAux and receives a func to perform on the nodes. runs in O(n) (for the iteration only).
    template<class do_something>
    void inOrder(do_something &func);
    // iterates through the nodes in reverse order. calls inOrderReverseAux and receives a func to perform on the nodes. runs in O(n) (iteration only).
    template<class do_something>
    void inOrderReverse(do_something &func);
    // returns the maximum object of the tree. runs in O(1) since the tree holds a pointer for the max.
    T &getMax();
    // returns the size (int) of the tree. runs in O(1) since the tree holds an integer for the size.
    int getSize();
};

/**
 * Public functions
 */

template<class T>
SplayTree<T>::SplayTree() : root(NULL), min(NULL), max(NULL), size(0) {}

template<class T>
SplayTree<T>::~SplayTree() {
    postOrderAuxRemoval(root);
}

template<class T>
T &SplayTree<T>::find(const T &key) {
    Node *found_node = findAux(root, key);
    splay(found_node);
    if (found_node == NULL || *found_node->data != key) {
        throw KeyNotFound();
    }
    return *found_node->data;
}

template<class T>
void SplayTree<T>::insert(const T &key) {
    Node *found_node = findAux(root, key);
    if (found_node != NULL && key == *found_node->data) {
        throw KeyAlreadyExists();
    }
    Node *to_insert = new Node(key, found_node);
    if (found_node != NULL) {
        if (key < *found_node->data) {
            found_node->left_son = to_insert;
        } else {
            found_node->right_son = to_insert;
        }
        to_insert->parent = found_node;
    }
    splay(to_insert);
    if (found_node == NULL) {
        root = to_insert;
    }
    //updating min/max of the tree
    if (root->right_son == NULL) {
        max = root;
    }
    if (root->left_son == NULL) {
        min = root;
    }
    size++;
}

template<class T>
void SplayTree<T>::remove(const T &key) {
    if (root == NULL) {
        throw EmptyTree();
    }
    Node *found_node = findAux(root, key);
    if (key != *found_node->data) {
        throw KeyNotFound();
    }
    splay(found_node);
    Node *left_tree = root->left_son;
    Node *right_tree = root->right_son;
    delete root;
    size--;
    join(left_tree, right_tree);
}

template<class T>
void SplayTree<T>::join(Node *left_tree, Node *right_tree){
    if(right_tree != NULL && left_tree != NULL){
        right_tree->parent = NULL;
        left_tree->parent = NULL;
        root = left_tree;
        Node *max_left = left_tree;
        while (max_left->right_son != NULL) {
            max_left = max_left->right_son;
        }
        splay(max_left);
        root->right_son = right_tree;
        root->parent = NULL;
        root->right_son->parent = root;
    } else if(right_tree == NULL && left_tree == NULL){
        root = NULL;
        max = NULL;
        min = NULL;
    } else if(right_tree == NULL){
        left_tree->parent = NULL;
        root = left_tree;
        Node *max_left = left_tree;
        while (max_left->right_son != NULL) {
            max_left = max_left->right_son;
        }
        splay(max_left);
        max = root;
        root->parent = NULL;
    } else {
        root = right_tree;
        root->parent = NULL;
        Node *min_right = right_tree;
        while (min_right->left_son != NULL) {
            min_right = min_right->left_son;
        }
        min = min_right;
    }
}

template<class T>
template<class do_something>
void SplayTree<T>::inOrder(do_something &func) {
    inOrderAux(root, func);
}

template<class T>
template<class do_something>
void SplayTree<T>::inOrderReverse(do_something &func) {
    inOrderAuxReverese(root, func);
}

template<class T>
T &SplayTree<T>::getMax() {
    if (max == NULL) {
        throw EmptyTree();
    }
    return *max->data;
}

template<class T>
int SplayTree<T>::getSize() {
    return size;
}

/**
 * private functions
 */

template<class T>
void SplayTree<T>::splay(SplayTree::Node *node) {
    while (node!=NULL && node->parent != NULL && node != root && node->parent != root) {
        Node *p = node->parent;
        Node *g = p->parent;
        if ((*node->data < *p->data && *node->data > *g->data) ||
            (*node->data > *p->data && *node->data < *g->data)) {
            zigZag(node);
        } else {
            zigZig(node);
        }
    }
    if (node != NULL && node->parent != NULL && node->parent == root && node->parent != NULL) {
        zig(node);
    }
}

template<class T>
void SplayTree<T>::zig(SplayTree::Node *node) {
    if (root->left_son == node) {
        root->left_son = node->right_son;
        if (node->right_son != NULL) {
            root->left_son->parent = root;
        }
        node->right_son = root;
    } else {
        root->right_son = node->left_son;
        if (node->left_son != NULL) {
            root->right_son->parent = root;
        }
        node->left_son = root;
    }
    node->parent = NULL;
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
    if (*node->data < *p->data) {
        //attach node's left son to g
        g->right_son = node->left_son;
        if (g->right_son != NULL) {
            g->right_son->parent = g;
        }
        //attach nodes right son to p
        p->left_son = node->right_son;
        if (p->left_son != NULL) {
            p->left_son->parent = p;
        }
        //attach both g and p to node
        node->left_son = g;
        node->right_son = p;
    } else {
        //attach node's right son to g
        g->left_son = node->right_son;
        if (g->left_son != NULL) {
            g->left_son->parent = g;
        }
        //attach nodes left son to p
        p->right_son = node->left_son;
        if (p->right_son != NULL) {
            p->right_son->parent = p;
        }
        //attach both g and p to node
        node->right_son = g;
        node->left_son = p;
    }
    node->parent = g->parent;
    if (g->parent != NULL && *g->data < *g->parent->data) {
        //g was a left son
        g->parent->left_son = node;
    } else if (g->parent != NULL) {
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
    if (*node->data < *p->data) {
        //attach p's right son to g
        g->left_son = p->right_son;
        if (g->left_son != NULL) {
            g->left_son->parent = g;
        }
        //attach nodes right son to p
        p->left_son = node->right_son;
        if (p->left_son != NULL) {
            p->left_son->parent = p;
        }
        //attach p to node
        node->right_son = p;
        p->parent = node;
        //attach g to p
        p->right_son = g;
    } else {
        //attach p's left son to g
        g->right_son = p->left_son;
        if (g->right_son != NULL) {
            g->right_son->parent = g;
        }
        //attach nodes left son to p
        p->right_son = node->left_son;
        if (p->right_son != NULL) {
            p->right_son->parent = p;
        }
        //attach p to node
        node->left_son = p;
        p->parent = node;
        //attach g to p
        p->left_son = g;
    }
    if (g->parent != NULL && *g->data < *g->parent->data) {
        //g was a left son
        g->parent->left_son = node;
    } else if (g->parent != NULL) {
        g->parent->right_son = node;
    }
    node->parent = g->parent;
    g->parent = p;
}

template<class T>
template<class do_something>
void SplayTree<T>::inOrderAux(SplayTree::Node *cur_node, do_something &func) {
    if (cur_node == NULL) return;

    inOrderAux(cur_node->left_son, func);
    func(cur_node->data);
    inOrderAux(cur_node->right_son, func);
}

template<class T>
template<class do_something>
void SplayTree<T>::inOrderAuxReverese(Node *cur_node, do_something &func) {
    if (cur_node == NULL) return;

    inOrderAuxReverese(cur_node->right_son, func);
    func(cur_node->data);
    inOrderAuxReverese(cur_node->left_son, func);
}

template<class T>
void SplayTree<T>::postOrderAuxRemoval(SplayTree::Node *cur_node) {
    if (cur_node == NULL) return;
    postOrderAuxRemoval(cur_node->left_son);
    postOrderAuxRemoval(cur_node->right_son);
    delete cur_node;
}

template<class T>
typename SplayTree<T>::Node *SplayTree<T>::findAux(SplayTree::Node *cur_node, const T& key) {
    if (cur_node == NULL) return NULL;
    if (key == *cur_node->data) {
        return cur_node;
    }
    if (key > *cur_node->data) {
        if (cur_node->right_son == NULL) {
            return cur_node;
        }
        return findAux(cur_node->right_son, key);
    }
    if (key < *cur_node->data) {
        if (cur_node->left_son == NULL) {
            return cur_node;
        }
        return findAux(cur_node->left_son, key);
    }
    return  NULL;
}

/**
 * Node functions
 */

template<class T>
SplayTree<T>::Node::Node(const T data, Node *parent) : data(new T(data)), parent(parent), right_son(NULL), left_son(NULL) {}

template<class T>
SplayTree<T>::Node::~Node() {
    delete data;
}


#endif //WET1_SPLAYTREE_H
