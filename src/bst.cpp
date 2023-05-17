#include <iostream>
#include <fstream>
using namespace std;
#include "bst.h"
#include "timer.h"
#include "avltree.h"
#include "bstree.h"
void BST::pre_order_print(ostream & out, Node * t){
    if(t){
        out<<t->key<<" ";
        pre_order_print(out,t->left);
        pre_order_print(out,t->right);

        }
}

void BST::in_order_print(ostream & out, Node * t){
    if(t){

        in_order_print(out,t->left);
        out<<t->key<<" ";
        in_order_print(out,t->right);
    }

}

void BST::post_order_print(ostream & out, Node * t){
    if(t){
        post_order_print(out,t->left);
        post_order_print(out,t->right);
        out<<t->key<<" ";

    }
}

BST::~BST(){
    Dest(root);
}

void BST::Dest(Node * t){
    if(t!= nullptr){
        Dest(t->left);
        Dest(t->right);
        delete t;
    }
}

ostream & operator << (ostream & out, BST & L){
    L.print(out);
    return out;

}


void error(string word, string msg) {
    cout << word << msg << endl;
}

void insert_all_words(int k, string file_name, BST & L) {
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k * NWORDS / 10;
    t.start();
    for (string word; (in >> word) && limit > 0; --limit)
        L.insert(word);
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = " << eTime << endl;
}

void find_all_words(int k, string file_name, BST & L) {
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k * NWORDS / 10;
    t.start();
    for (string word; (in >> word) && limit > 0; --limit)
        L.find(word);
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = " << eTime << endl;
}
void remove_all_words(int k, string file_name, BST & L) {

    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k * NWORDS / 10;
    t.start();
    for (string word; (in >> word) && limit > 0; --limit)
    L.remove(word);
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = " << eTime << endl;
}

void measure_BST(string file_name, BST & L) {
    cout << L.name << endl;
    for (int k = 1; k <= 10; k++) {
        cout << "\tk = " << k << endl;
        insert_all_words(k, file_name, L);
        find_all_words(k, file_name, L);
        remove_all_words(k, file_name, L);
        if (!L.is_empty()) {
            error(L.name, "is not empty");
        }
    }
}

void measure_BSTs(string input_file) {
    AVLTree a;
    BSTree b;
    measure_BST(input_file, a);
    measure_BST(input_file, b);
}

