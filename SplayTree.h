//
// Created by adire on 27-Nov-17.
//

#ifndef WET1_SPLAYTREE_H
#define WET1_SPLAYTREE_H

#include <assert.h>
#include "Exceptions.h"

class SplayTree {
private:

    class Node{
    private:
        int data;
        Node *parent;
        Node *right_son;
        Node *left_son;

        friend class SplayTree;
    public:
        Node(int data, Node *parent); //TODO: change to const data when generic
        ~Node() = default; //TODO: need to delete the data when generic
    };

    Node *root;
    Node *min;
    Node *max;
    int size;

    void splay(Node* node);
    void zig(Node* node);
    void zigZag(Node* node);
    void zigZig(Node* node);
    template <class function>
    void inOrderAux(Node *cur_node, const function& func) const;
    void postOrderAuxRemoval(Node *cur_node);
    Node* findAux(Node* cur_node, int key);

public:
    SplayTree();
    SplayTree(const SplayTree &splay_tree) = delete ;
    SplayTree &operator=(const SplayTree &splay_tree) = delete;
    ~SplayTree();
    int find(int key);
    void insert(int key); //TODO: change to const when generic
    void remove(int key);
    template <class function>
    void inOrder(const function& func) const;
};

/**
 * Public functions
 */

SplayTree::SplayTree() : root(nullptr), min(nullptr), max(nullptr), size(0){}

SplayTree::~SplayTree() {
    postOrderAuxRemoval(root);
}

int SplayTree::find(int key) {
    if(key == 0){ //TODO: change to nullptr
        throw NullParameter();
    }
    Node *found_node = findAux(root, key);
    splay(found_node);
    if(found_node->data != key){
        return 0;
    }
    return found_node->data;
}

void SplayTree::insert(const int key) {
    Node *found_node = findAux(root, key);
    if (found_node != nullptr && key == found_node->data) {
        throw KeyAlreadyExists();
    }
    auto *to_insert = new Node(key, found_node);
    if(found_node != nullptr){
        found_node->right_son = to_insert;
    }
    splay(to_insert);
    //updating min/max of the tree
    if (root->right_son == nullptr) {
        max = root;
    }
    if (root->left_son == nullptr) {
        min = root;
    }
    size++;
}

void SplayTree::remove(int key) {
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
        max = 0;
        min = 0;
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

template<class function>
void SplayTree::inOrder(const function &func) const {
    inOrderAux(root, func);
}

/**
 * private functions
 */

void SplayTree::splay(SplayTree::Node *node) {
    while (node != root){
        Node *p = node->parent;
        Node *g = p->parent;
        if(p == root){
            zig(node);
        } else if((node->data < p->data && node->data > g->data) ||
                  (node->data > p->data && node->data < g->data)){
            zigZag(node);
        } else {
            zigZig(node);
        }
    }
}

void SplayTree::zig(SplayTree::Node *node) {
    assert(node->parent == root);
    if(root->left_son == node){
        root->left_son = node->right_son;
        root->left_son->parent = root;
        node->right_son = root;
    } else{
        root->right_son = node->left_son;
        root->right_son->parent = root;
        node->left_son = root;
    }
    node->parent = nullptr;
    root->parent = node;
    root = node;
}

void SplayTree::zigZag(SplayTree::Node *node) {
    Node *p = node->parent;
    Node *g = p->parent;
    if(node->data < p->data){
        //attach node's left son to g
        g->right_son = node->left_son;
        g->right_son->parent = g;
        //attach nodes right son to p
        p->left_son = node->right_son;
        p->left_son->parent = p;
        //attach both g and p to node
        node->left_son = p;
        node->right_son = g;
    }
    else {
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
    p->parent = node;
    g->parent = node;
}

void SplayTree::zigZig(SplayTree::Node *node) {
    Node *p = node->parent;
    Node *g = p->parent;
    if(node->data < p->data){
        //attach p's right son to g
        g->left_son = p->right_son;
        g->left_son->parent = g;
        //attach nodes right son to p
        p->left_son = node->right_son;
        p->left_son->parent = p;
        //attach p to node
        node->right_son = p;
        //attach g to p
        p->right_son = g;
    }
    else {
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
        g->parent = p;
    }
    p->parent = node;
    g->parent = p;
}

template<class function>
void SplayTree::inOrderAux(SplayTree::Node *cur_node, const function &func) const {
    if(cur_node == nullptr) return;

    inOrderAux(cur_node->left_son, func);
    func(cur_node->data);
    inOrderAux(cur_node->right_son, func);
}

void SplayTree::postOrderAuxRemoval(SplayTree::Node *cur_node) {
    if(cur_node == nullptr) return;
    postOrderAuxRemoval(cur_node->left_son);
    postOrderAuxRemoval(cur_node->left_son);
    delete cur_node;
}

SplayTree::Node *SplayTree::findAux(SplayTree::Node *cur_node, int key) {
    if(cur_node == nullptr) return nullptr;
    if(key == cur_node->data){
        return cur_node;
    }
    if(key > cur_node->data){
        if(cur_node->right_son == nullptr){
            return cur_node;
        }
        return findAux(cur_node->right_son, key);
    }
    if(key < cur_node->data){
        if(cur_node->left_son == nullptr){
            return cur_node;
        }
        return findAux(cur_node->left_son, key);
    }
}

/**
 * Node functions
 */

SplayTree::Node::Node(int data, Node *parent) : data(data), right_son(nullptr), left_son(nullptr), parent(parent){}












#endif //WET1_SPLAYTREE_H
