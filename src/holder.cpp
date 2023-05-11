#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "holder.h"
#include "Timer.h"



    //size will be -1 of the actual amount of elements in buf

    // for Array Stack, the bottom of the array will be the top of the stack

    ArrayStack::ArrayStack(int cap):Stack("Arraystack"),buf(new string[cap]),capacity(cap),size(0){
        
    }
    
    void ArrayStack::push(const string & word){
        if(!is_full()){
            buf[size] = word;    
            ++size;}
    }
    void ArrayStack::pop(){
        if(!is_empty())
            size--;
    }
    string ArrayStack::top(){
        return buf[size-1];
    }
    bool ArrayStack::is_empty(){
        if(size==0)
            return true;
        return false;
    }
    bool ArrayStack::is_full(){
        if(size>=capacity)
            return true;
        return false;
    }
    void ArrayStack::print(ostream & out){
        for(int i = size-1;i >= 0;i--){
            out<<buf[i]<<" ";

        }
    }
    ArrayStack::~ArrayStack(){
        delete[] buf;
    }



     void ListNode::delete_list(ListNode * L){
            while(L!=nullptr){
                ListNode * temp = L->next;
                delete L;
                L = temp;
            }
        }

    void ListNode::print(ostream & out, ListNode * L){
            for(ListNode * temp = L;temp!=nullptr;temp = temp->next){
                out<<temp->data<<" ";
            }
        }


//For Linked Stack, the top of the stack will be the head

    LinkedStack::LinkedStack():head(nullptr),Stack("Linkedstack"){ }
    
    void LinkedStack::push(const string & word){
        head = new ListNode(word,head);

    }
    
    void LinkedStack::pop(){
        if(head->next == nullptr){
            head = nullptr;
        }else{
            head = head->next;
        }
    }    
    string LinkedStack::top(){
        return head->data;
    }
    
    bool LinkedStack::is_empty(){
        if(head == nullptr)
            return true;
        return false;
    }
    
    bool LinkedStack::is_full(){
        return false;
    }
    
    void LinkedStack::print(ostream & out){
        ListNode::print(out,head);
    }
    
    LinkedStack::~LinkedStack(){
        ListNode::delete_list(head);
    }


    ArrayQueue::ArrayQueue(int cap):capacity(cap + 1),buf(new string[cap+1]),front(0),rear(0),Queue("Arrayqueue"){
        
    }
    
    void ArrayQueue::enq(const string & word){
            if(!is_full()){
                buf[rear]=word;
                rear = (rear+1)%capacity;

            }
        
    }
    
    void ArrayQueue::deq(){
        if(!is_empty()){
            front = (front+1)%capacity;

        }
    }
    
    string ArrayQueue::next(){
        if(!is_empty())
            return buf[front];
    }
    
    bool ArrayQueue::is_empty(){
        if(front == rear)
            return true;
        return false;
    }
    
    bool ArrayQueue::is_full(){
        int temp_rear = rear+1;
        if(temp_rear%capacity == front)
            return true;
        return false;
    }
    
    void ArrayQueue::print(ostream & out){
            for(int i = front ;i!=rear;i=(i+1)%capacity){

                out<<buf[i]<<" ";
            }
    }
    
    ArrayQueue::~ArrayQueue(){
        delete[] buf;
    }



    LinkedQueue::LinkedQueue():head(nullptr),tail(nullptr),Queue("Linkedqueue"){
        
    }
    
    void LinkedQueue::enq(const string & word){
        if(head == nullptr){
            head =tail = new ListNode(word,nullptr);
        }else{
            tail->next = new ListNode(word,nullptr);
            tail = tail->next;
        }
    }
    
    void LinkedQueue::deq(){
        if(head != nullptr)
            head = head->next;
    }
    
    string LinkedQueue::next(){
        return head->data;
    }
    
    bool LinkedQueue::is_empty(){
            if(head == nullptr)
                return true;
            return false;
            }

    
    bool LinkedQueue::is_full(){
        return false;
    }
    
    void LinkedQueue::print(ostream & out){
        ListNode::print(out,head);
    }
    
    LinkedQueue::~LinkedQueue(){
        ListNode::delete_list(head);
    }





void error(string word, string msg){
    cout<<msg<<":"<<word<<endl;
}

void insert_all_words(int K, string file_name, Holder & L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = K * NWORDS / 10;
    t.start();
    for(string word;(in>>word) && limit >0; --limit){
        L.insert(word);
    }
    t.elapsedUserTime(eTime);
    in.close();
    cout<<"\t\tI = "<< eTime << endl;
}



void remove_all_words(int K,string file_name, Holder & L){
    Timer t;
     double eTime;
     ifstream in(file_name);
     int limit = K * NWORDS / 10;
     t.start();
     for(string word;(in>>word) && limit >0; --limit){
         L.remove();
     }
     t.elapsedUserTime(eTime);
     in.close();
     cout<<"\t\tI = "<< eTime << endl;
}

void measure_holder(string file_name,Holder & L){
    cout<<L.name<<endl;
    for(int K=1; K<=10;++K){
        cout << "\tK = "<<K<<endl;
        insert_all_words(K,file_name,L);
        remove_all_words(K,file_name,L);
        if(!L.is_empty())
            error(L.name,"is not empty");

    }

}
void measure_holders(string input_file)
{
    ArrayStack AS;
    measure_holder(input_file, AS);
    LinkedStack LS;
    measure_holder(input_file, LS);
    ArrayQueue AQ;
    measure_holder(input_file, AQ);
    LinkedQueue LQ;
    measure_holder(input_file, LQ);
}
