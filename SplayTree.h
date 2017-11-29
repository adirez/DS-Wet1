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

    Node* findAux(Node* cur_node, int key);
    void inOrderAux(Node* cur_node, int key);
    void zig(Node* node);
    void zigZag(Node* node);
    void zigZig(Node* node);

    Node *root;
    Node *min;
    Node *max;
    int size;

public:
    SplayTree();
    SplayTree(const SplayTree &splay_tree) = delete ;
    SplayTree &operator=(const SplayTree &splay_tree) = delete;
    ~SplayTree();
    Node &find(Node *cur_node, int key);
    void insert(int key); //TODO: change to const when generic
    void remove(int key); //TODO: change to const when generic
};

SplayTree::Node *SplayTree::findAux(SplayTree::Node *cur_node, int key) {
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

SplayTree::Node::Node(int data, Node *parent) : data(data), right_son(nullptr), left_son(nullptr), parent(parent){}

SplayTree::SplayTree() : root(nullptr), min(nullptr), max(nullptr), size(0){}


SplayTree::~SplayTree() {
    delete root;
}



SplayTree::Node &SplayTree::find(Node *cur_node, int key) {
    if(key == 0){ //TODO: change to nullptr
        throw NullParameter();
    }

}

void SplayTree::insert(const int key) {
    if (root == nullptr) {
        auto *new_root = new Node(key, nullptr); //TODO: auto???
        root = new_root;
        max = root;
        min = root;
        return;
    }
    Node &find_node = find(root, key);
    if (key == find_node.data) {
        throw KeyAlreadyExists();
    }

    //meaning the data we want to insert did not exist in the tree
    auto *to_insert = new Node(key, nullptr); //TODO: auto???

    //the value closest to the one we needed is now in the root after zig-zag
    to_insert->left_son = root;
    to_insert->right_son = root->right_son;

    //updating the previously root and it's right son as both sons of the inserted value
    to_insert->left_son->parent = to_insert;
    to_insert->right_son->parent = to_insert;
    to_insert->left_son->right_son = nullptr;

    //updating the root
    root = to_insert;

    //updating min/max of the tree
    if (root->data > max->data) {
        max = root;
    } else if (root->data < min->data) {
        min = root;
    }
}

void SplayTree::remove(int key) {
    if (root == nullptr) {
        throw EmptyTree();
    }

    Node &find_node = find(root, key);
    if (key != root->data) {
        throw KeyNotFound();
    }

    Node *left_son= root->left_son;
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
    while (left_son->right_son != nullptr) {
        left_son = left_son->right_son;
    }
    root = left_son;
    if (right_son == nullptr) {
        max = root;
    }

    root->right_son = right_son;
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
    if (g == root) {
        root = node;
    }
    if(node->data < p->data){
        //attach node's left son to g
        g->right_son = node->left_son;
        g->right_son->parent = g;
        //attach nodes right son to p
        p->left_son = node->right_son;
        p->left_son->parent = p;
        //attach both g and p to node
        node->left_son = g;
        node->right_son = p;
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
    if (g->data < g->parent->data) {
        //g was a left son
        g->parent->left_son = node;
    } else {
        g->parent->right_son = node;
    }
    p->parent = node;
    g->parent = node;
}

void SplayTree::zigZig(SplayTree::Node *node) {
    Node *p = node->parent;
    Node *g = p->parent;
    if (g == root) {
        root = node;
    }
    if(node->data < p->data){
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



/*template <class Predicate>
void SplayTree::inOrderAux(SplayTree::Node *cur_node, int key) {
    if(cur_node == nullptr){
        return;
    }

}*/



#endif //WET1_SPLAYTREE_H
