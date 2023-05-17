#include <iostream>
using namespace std;



Node * BSTree::insert_node(Node * t, string key){
    if ( root == nullptr ) root = newNode(key, nullptr, nullptr);  
        Node * t = root;
    while ( t->key  !=  key ){
        if ( key  <  t->key) {
            if ( t->left == nullptr )
                t->left = newNode(key, nullptr, nullptr);
            t = t->left;
        }
        else if ( key  >  t->key ) {
             if ( t->right == nullptr )
                 t->right = newNode(key, nullptr, nullptr);
             t = t->right;
        }
        }
        t->value = value;
        return root;


}

Node * BSTree::find_node(Node * t, string key){
    if(t==nullptr)
        return nullptr;
    if(t->key==key)
        return t;
    if(t->key > key)
        return find_node(t->right,key);
    if(t->key<key)
        return find_node(t->left,key);



}


Node * BSTree::delete_node(Node * t, string key) {
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
            } else { // One child case
                *t = *child;
            }
            delete child;
        }
        else {
            Node * succ = find_leftmost(t->right);
            t->key =succ->key;
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
    return get_height(node->left) + get_height(node->right)+1;
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
        return compute_height(root)<=0;


    }
    
    int BSTree::get_height() const{
        return compute_height(root);

    }
