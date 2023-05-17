#include <iostream>
#include <fstream>
using namespace std;
#include "bst.h"


void BST::pre_order_print(ostream & out, Node * t){
    if(t){
        out<<t->value<<" ";
        pre_order_print(out,t->left);
        pre_order_print(out,t->right);

        }
}

void BST::in_order_print(ostream & out, Node * t){
    if(t){

        in_order_print(out,t->left);
        out<<t->value<<" ";
        in_order_print(out,t->right);
    }

}

void BST::post_order_print(ostream & out, Node * t){
    if(t){
        post_order_print(out,t->left);
        post_order_print(out,t->right);
        out<<t->value<<" ";

    }
}

BST::~BST(){

    if(root){
        Dest(root);
    }
    return;


}

void BST::Dest(Node * t){
    Dest(t->left);
    Dest(t->right);
    delete t;
}



ostream & operator << (ostream & out, BST & L){


}

void error(string word, string msg);
void insert_all_words(int k, string file_name, BST & L);
void find_all_words(int k, string file_name, BST & L);
void remove_all_words(int k, string file_name, BST & L);
void measure_BST(string file_name, BST & L);
void measure_BSTs(string input_file);

