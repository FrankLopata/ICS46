
#include <iostream>
#include <fstream>
#include <string>
 using namespace std;
 #include "hashtable.h"
#include "Timer.h"
#include "stats.h"
   
    ListNode * ListNode::find(string key, ListNode * L){
        ListNode * temp = L;
            while(temp != nullptr){
                if(temp -> data == key)
                    return temp;
                temp = temp->next;

            }
            return nullptr;
    }
     ListNode * ListNode::insert(string key, ListNode * L){
        ListNode * temp = L;
        if(temp==nullptr){
            temp = new ListNode(key,nullptr);
            return temp;
            }
        while(temp->next != nullptr){
                temp = temp->next;
           }
        temp->next = new ListNode(key,nullptr); 
        return temp->next;
    }
   
    ListNode * ListNode::remove(string word, ListNode *  L){
            ListNode * prev = L;
            if(L==nullptr)
                return nullptr;
            if(prev->data == word){
                L = nullptr;
                return L;
                }
            for(ListNode * temp = prev -> next;temp != nullptr;temp=temp->next){
                if(temp -> data == word){
                    ListNode * tempNext = temp->next;
                    prev -> next = tempNext;
                    temp = nullptr;
                    if(tempNext == nullptr)
                        return prev;
                    return tempNext;
                }
                prev = temp;
            }
            return nullptr;
   }
     void ListNode::print(ostream & out, ListNode * L){
        for(ListNode * temp = L;temp!=nullptr;temp = temp->next){
            out<<temp->data<<" ";
            }

    }
     int ListNode::length(ListNode * L){
        int count = 0;
        ListNode* current = L;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
        }


    
    

     void ListNode::delete_list(ListNode * L){
        while(L!=nullptr){
                ListNode * temp = L->next;
                delete L;
                L = temp;
            }

    }


    void HashTable::insert( const string & word){
        int index  =  hasher.hash(word,capacity);
        if(buf[index]==nullptr)
            size++;
        buf[index] = ListNode::insert(word,buf[index]);

    }
    bool HashTable::find( const string & word){
        int index = hasher.hash(word,capacity);
        return ListNode::find(word,buf[index]);

    }
    void HashTable::remove( const string & word){
        int index = hasher.hash(word,capacity);
        if(!is_empty()){
         size--;
         buf[index] = ListNode::remove(word,buf[index]);
        }



    }
    bool HashTable::is_empty(){
        return size <=0;

    }
    bool HashTable::is_full(){
        return size>=capacity;

    }
    void HashTable::print(ostream & out){
        for(int i = 0; i<size;++i){
            ListNode::print(out,buf[i]);
        }
    }
    HashTable::~HashTable(){
        for(int i = 0; i<capacity;i++){

            ListNode::delete_list(buf[i]);
        }
        delete[] buf;
    }

    size_t HashTable::number_of_entries(){
        int out = 0;
        for(int i = 0; i<capacity;++i){
            out += ListNode::length(buf[i]);
        }
        return out;
    }
    size_t HashTable::number_of_chains(){
        return size;
    }
    void HashTable::get_chain_lengths(vector<int> & v){
        for(int i = 0;i<capacity;i++){
            int l = ListNode::length(buf[i]);
            v.push_back(l);
        }

    }


void error(string word, string msg){
    cout<<msg<<":"<<word<<endl;
}
void insert_all_words(string file_name, HashTable & L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = NWORDS ;
    t.start();
   for(string word; (in >> word)&& limit > 0; --limit){
        L.insert(word);
    }
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = "<< eTime << endl;
    
}
void find_all_words(string file_name, HashTable & L){
    cout<<"RUNNING FIND"<<endl;
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit =  NWORDS;
    t.start();
    for(string word; (in >> word) && limit > 0; --limit){
        L.find(word);
       }
    t.elapsedUserTime(eTime);
     in.close();
    cout << "\t\tI = " << eTime << endl;
    
}
void remove_all_words(string file_name, HashTable & L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit =  NWORDS ;
    t.start();
    for(string word; (in >> word) && limit > 0; --limit){
        L.remove(word);}
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = " << eTime << endl;
    
}

void measure_hashtable(string file_name, HashTable & L)
{
    cout << L.get_name() << endl;
    insert_all_words(file_name, L);
    vector<int> chain_lengths;
    L.get_chain_lengths(chain_lengths);
    Stats stats(L.get_name(), chain_lengths);
    stats.print(cout);

    find_all_words(file_name, L);
    remove_all_words(file_name, L);
    if(!(L.is_empty()))
        error(L.get_name(), "is not empty");
}

void measure_hashtables(string input_file){

    ChatGPTHasher m1;
    HashTable myTable(m1, 100);
    measure_hashtable(input_file, myTable);


}
