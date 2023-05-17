#include <iostream>
using namespace std;
#include "bstree.h"


Node * BSTree::insert_node(Node * t, string key){
    if ( t == nullptr ) 
         t= new Node(key);
    else{
        if(t->key>key)
            t->left = insert_node(t->left,key);
        else{
            if(key>t->key)
            t->right = insert_node(t->right,key);}}
    return t;

}

Node * BSTree::find_node(Node * t, string key){
    if(t==nullptr)
        return t;
    if(t->key==key)
        return t;
    if(t->key > key)
        return find_node(t->left,key);
    if(t->key<key)
        return find_node(t->right,key);



}


Node * BSTree::delete_node(Node * t, string key) {
    if (t != nullptr)
    {
        if (key < t->key)
        {
            t->left = delete_node(t->left, key);
        }
        else if (key > t->key)
        {
            t->right = delete_node(t->right, key);
        }
        else
        {
            if (t->left == nullptr && t->right == nullptr)
            {
                delete t;
                t = nullptr;
            }
            else if (t->left == nullptr)
            {
                Node * temp = t;
                t = t->right;
                delete temp;
            }
            else if (t->right == nullptr)
            {
                Node * temp = t;
                t = t->left;
                delete temp;
            }
            else
            {
                Node * temp = find_leftmost(t->right);
                t->key = temp->key;
                t->right = delete_node(t->right, temp->key);
            }
        }
    }
    return t;
}

Node * BSTree::find_leftmost(Node *t) {
    if (t == nullptr) {return nullptr;}
    else if (t->left == nullptr) {return t;}

    else {
        return find_leftmost(t->left);
    }
}

int BSTree::compute_height(Node * node){
     if (node == nullptr) {return 0;}

    return 1 + max(compute_height(node->left), compute_height(node->right));
}


BSTree::BSTree(): BST("BSTree") {}

void BSTree::insert(const string & key) {
    root = insert_node(root, key);
    ++count;
}

bool BSTree::find(const string & key) const {
    return find_node(root, key);
}

void BSTree::remove(const string & key) {
    root = delete_node(root, key);
    --count;
}

bool BSTree::is_empty() const {
    return root == nullptr;
}

int BSTree::get_height() const {
    return compute_height(root);
}
