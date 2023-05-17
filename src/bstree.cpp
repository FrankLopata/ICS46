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
    if (t!=nullptr) return t;
    if (key < t->key)
        t->left = delete_node(t->left, key);
    else if (key > t->key)
        t->right = delete_node(t->right, key);
    else { 
        if (t->left == nullptr || t->right == nullptr) {
            Node * child;
            if (t->left == nullptr) {
                child = t-> right;
            } else { 
                child = t->left;
            }
            if(child == nullptr){
                child =t;
                t=nullptr;
            }else{
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

Node * BSTree::find_leftmost(Node *t) {
    while (t->left)
		t = t->left;
	return t;
}

int BSTree::compute_height(Node * node){
    if(node==nullptr)
        return 0;
    return max(compute_height(node->left),compute_height(node->right))+1;
}


    BSTree::BSTree():BST("BSTree"){}
    
    void BSTree::insert(const string & key){
        root = insert_node( root,key);
        count++;
    }
    
    bool BSTree::find(const string & key) const{
         return find_node(root,key);
    }
    
    void BSTree::remove(const string & key){
        delete_node(root,key);
        count--;

    }
    
    bool BSTree::is_empty() const{
        return root==nullptr;


    }
    
    int BSTree::get_height() const{
        return compute_height(root);

    }
