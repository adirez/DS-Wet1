//
// Created by adire on 27-Nov-17.
//

#ifndef WET1_SPLAYTREE_H
#define WET1_SPLAYTREE_H

template <class T>
class SplayTree {
private:
    class Node{
    private:
        T* data;
        Node *right_son;
        Node *left_son;

        friend class SplayTree;
    public:
        Node(const T data);
        ~Node();
    };
    Node *root;
    Node *min;
    Node *max;
    int size;

public:
    SplayTree();
    SplayTree(const SplayTree &splay_tree);
    ~SplayTree();
    SplayTree &operator=(const SplayTree &splay_tree);
    void insert(const T& data);
    void remove(SplayTree::Node);

    template <class Predicate>
    SplayTree::Node find(const Predicate& predicate) const;
};

SplayTree::SplayTree(): root(nullptr), min(nullptr), max(nullptr), size(0){}

SplayTree::SplayTree(const SplayTree &splay_tree) {

}


#endif //WET1_SPLAYTREE_H
