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
    void insert(int data); //TODO: change to const when generic

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

void SplayTree::insert(const int data) {
    if(root == nullptr){
        auto *new_root = new Node(data, nullptr);
        return;
    }
    Node *insert_node = find(root, data);
    if(data == insert_node->data){
        throw KeyAlreadyExists();
    }
    auto *new_node = new Node(data, insert_node); //TODO: what the fuck is auto?!?!
    if(data > insert_node->data){
        insert_node->right_son = new_node;
        return;
    }
    insert_node->left_son = new_node;
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



/*template <class Predicate>
void SplayTree::inOrderAux(SplayTree::Node *cur_node, int key) {
    if(cur_node == nullptr){
        return;
    }

}*/


/*void SplayTree::remove(int key) {
    if(root == nullptr){
        throw EmptyTree();
    }
    Node *to_remove = find(root, key);
    if(to_remove->data != key){
        throw KeyNotFound();
    }
    if(to_remove == root){
        delete root;
    }
    //meaning to_remove is the left son of his parent
    if(to_remove->data < to_remove->parent->data){
        if(to_remove->left_son != nullptr){
            //finds the biggest node in the left sons node
            Node *closest = find(to_remove->left_son, key);
            closest->parent->right_son = nullptr; //TODO: assuming we got to the biggest
            closest->parent = to_remove->parent;
            to_remove->parent->left_son = closest;
            closest->right_son = to_remove->right_son;
            closest->left_son = to_remove->left_son;
        }

    }

}*/


#endif //WET1_SPLAYTREE_H
