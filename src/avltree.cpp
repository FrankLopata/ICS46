
#include <iostream>
#include <fstream>
using namespace std;
#include "avltree.h"


int AVLTree::get_height(Node * node){
    if(node==nullptr)
        return 0;
    return get_height(node->left) + get_height(node->right)+1;
}

int AVLTree::get_balance(Node * node){
    return node ? get_height(node->left) - get_height(node->right) : 0;


}

void AVLTree::set_height(Node * node){
    node->height = 1+max(get_height(node->left),get_height(node->right));

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

Node * AVLTree::right_rotate(Node * y){
    Node * x = y->left;
    Node * T = x->right;
    x->right = y;                  
    y->left = T;
    set_height(x);                
    set_height(y);
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
         t= new Node(key, nullptr, nullptr);
    if(t->key>key)
        t->left = insert_node(t->left,key);
    if(key>t->key)
        t->right = insert_node(t->right,key);
    t=rebalance(t);
    set_height(t);
    return t;
}

Node * AVLTree::find_node(Node * t, string key){
    if(t==nullptr)
        return nullptr;
    if(t->key==key)
        return t;
    if(t->key > key)
        return find_node(t->right,key);
    if(t->key<key)
        return find_node(t->left,key);



}


Node * AVLTree::delete_node(Node * t, string key) {
    if (!t) return t;
    if (key < t->key)
        t->left = delete_node(t->left, key);
    else if (key > t->key)
        t->right = delete_node(t->right, key);
    else { 
        if (t->left == nullptr || t->right == nullptr) {
            Node * child = t->left ? t->left : t->right;
            if (child == nullptr) {
                child = t;
                t = nullptr;
            } else { 
                *t = *child;
            }
            delete child;
        }
        else {
            Node * succ = find_leftmost(t->right);
            t->key=succ->key;            
            t->right = delete_node(t->right, key);
        }
    }
    return t;
}

Node * AVLTree::find_leftmost(Node *t) {
    while (t->left)
		t = t->left;
	return t;
}


AVLTree::AVLTree():BST("AVLTree"){}

void AVLTree::insert(const string & key){
    insert_node(root,key);
    count++;
}

bool AVLTree::find(const string & key) const{
    return find_node(root,key);

}

void AVLTree::remove(const string & key){
        delete_node(root,key);
        count--;
}

bool AVLTree::is_empty() const{
 return get_height(root)<=0;

}

int AVLTree::get_height() const{
    return get_height(root);

}
