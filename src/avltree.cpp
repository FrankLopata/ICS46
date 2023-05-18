#include <iostream>
#include <fstream>
using namespace std;
#include "avltree.h"


int AVLTree::get_height(Node * node){
    if (node != nullptr){
        return node->height;
    }
    return 0; 
}

int AVLTree::get_balance(Node * node){
    if (node != nullptr){
        return get_height(node->left) - get_height(node->right);
    }
    return 0;


}

Node * AVLTree::left_rotate(Node * x){
    Node * y = x->right;
    Node * T = y->left;
    y->left = x;                     
    x->right = T;
    set_height(x);                
    set_height(y);
    return y;          



}

Node * AVLTree::right_rotate(Node * y) {
    Node * x = y->left;
    Node * T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    set_height(x);
    set_height(y);

    // Return new root
    return x;
}

Node * AVLTree::rebalance(Node * t){
        set_height(t);
        int balance = get_balance(t);
        if ( balance > 1 ) {
            if ( get_balance(t->left) < 0 )
                t->left = left_rotate(t->left);
            return right_rotate(t);
        } else if ( balance < -1 ) {
            if ( get_balance(t->right ) > 0)
                t->right = right_rotate(t->right);
            return left_rotate(t);
        }
        return t;



}

Node * AVLTree::insert_node(Node * t, string key){
    if ( t == nullptr ) 
         t= new Node(key);
    else{
        if(t->key>key){
            t->left = insert_node(t->left,key);
        }else{
            if(key>t->key)
                t->right = insert_node(t->right,key);
            }}
    t=rebalance(t);
    set_height(t);
    return t;
}

Node * AVLTree::find_node(Node * t, string key){
    if(t==nullptr)
        return nullptr;
    if(t->key > key)
        return find_node(t->right,key);
    if(t->key<key)
        return find_node(t->left,key);
    return t;


}


Node * AVLTree::find_leftmost(Node *t) {
    if (t == nullptr) {return nullptr;}
    else if (t->left == nullptr) {return t;}

    else {
        return find_leftmost(t->left);
    }
}


AVLTree::AVLTree():BST("AVLTree"){}

void AVLTree::insert(const string & key){
    root=insert_node(root,key);
    count++;
}

bool AVLTree::find(const string & key) const{
    return find_node(root,key)!=nullptr;

}

void AVLTree::remove(const string & key){
        root=delete_node(root,key);
        count--;
}

bool AVLTree::is_empty() const{
    return root==nullptr;

}

int AVLTree::get_height() const{
    return get_height(root);

}
Node * AVLTree::delete_node(Node * t, string key)
{
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
    return rebalance(t);
    }

void AVLTree::set_height(Node * node)
{
    if (node != nullptr)
    {
        int left = get_height(node->left);
        int right = get_height(node->right);
        node->height = std::max(left, right) + 1;
        }
    }

