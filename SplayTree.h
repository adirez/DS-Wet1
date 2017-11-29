//
// Created by adire on 27-Nov-17.
//

#ifndef WET1_SPLAYTREE_H
#define WET1_SPLAYTREE_H

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

public:
    SplayTree();
    SplayTree(const SplayTree &splay_tree) = delete ;
    SplayTree &operator=(const SplayTree &splay_tree) = delete;
    ~SplayTree();
    SplayTree::Node *find(Node *cur_node, int key);
    void insert(int data); //TODO: change to const when generic
    void remove(int key); //TODO: change to const
    SplayTree::Node *getMin();
    SplayTree::Node *getMax();
    void join(SplayTree small_tree, SplayTree big_tree);
    void split(SplayTree root);
    void printInOrder(SplayTree splay_tree);
};

SplayTree::Node::Node(int data, Node *parent) : data(data), right_son(right_son), left_son(left_son), parent(parent){}

SplayTree::SplayTree(): root(nullptr), min(nullptr), max(nullptr), size(0){}


SplayTree::~SplayTree() {
    delete root;
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

SplayTree::Node *SplayTree::find(Node *cur_node, int key) {
    if(key == 0){ //TODO: change to nullptr
        throw NullParameter();
    }
    if(key == cur_node->data){
        return cur_node;
    }
    if(key > cur_node->data){
        if(cur_node->right_son == nullptr){
            return cur_node;
        }
        return find(cur_node->right_son, key);
    }
    if(key < cur_node->data){
        if(cur_node->left_son == nullptr){
            return cur_node;
        }
        return find(cur_node->left_son, key);
    }
}

void SplayTree::remove(int key) {
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

}


#endif //WET1_SPLAYTREE_H
