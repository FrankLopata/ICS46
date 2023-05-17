#include <iostream>
using namespace std


int AVLTree::get_height(Node * node){
    if(node==nullptr)
        return 0;
    return get_height(node->left) + get_height(node->right)+1;
}

int AVLTree::get_balance(Node * node){
    if(node==nullptr)
        return 0;
    return node->data + get_balance(node->left)+get_balance(node->right);

}

void AVLTree::set_height(Node * node){
    if(node == nullptr)
        return nullptr;
    node->height = 1+max(get_height(node->left)+get_height(node->right));

}

Node * AVLTree::left_rotate(Node * y){
    Node * y = x->right;
    Node * T = y->left;
    y->left = x;                     
    x->right = T;
    set_height(x);                
    set_height(y);
    return y;          



}

Node * AVLTree::right_rotate(Node * x){
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
    if ( root == nullptr ) root = newNode(key, nullptr, nullptr);  
        TreeNode * t = root;
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
    else { // delete node t
        // Case 1: Node has one or no child
        if (t->left == nullptr || t->right == nullptr) {
            Node * child = t->left ? t->left : t->right;
            // No child case
            if (child == nullptr) {
                child = t;
                t = nullptr;
            } else { // One child case
                *t = *child; // copy data up from child
            }
            delete child;
        }
        else {
            Node * succ = find_leftmost(t->right);
            swap(t->key, succ->key);
            t->right = delete_node(t->right, key);
        }
    }
    return t;
}

Node * find_leftmost(Node *t) {
    while (t->left)
		t = t->left;
	return t;
}


AVLTree::AVLTree():BST("BST");

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
