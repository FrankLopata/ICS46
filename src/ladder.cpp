#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include "ladder.cpp"
using namespace std;

void error(string word1, string word2, string msg){   cout << word1 << word2 << ": " << msg << endl;}


bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    if(str1 == str2)
        return d>=1;

    int len1 = str1.length();
    int len2 = str2.length();

    if(abs(len1-len2)>1)
        return false;
    int x=0, y=0,checker=0;
    while(x<len1 &&y<len2){
        if(str1[x]!=str2[y]){
            if(checker >= 1)
                return false;
            if(len1>len2)
                ++x;
            else{ if(len1<len2)
                ++y;
            }else{
                ++x;
                ++y;
            }
            ++checker;

        }else{
            ++x;
            ++y;
    }

}
if(len1>x||len2>y){
    checker++;
}
return checker>=1;
}

bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1,word2,1);

}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    queue<vector<string>> lq;
    lq.push(begin_word);
    vector<string> visited;
    visited.push_back(begin_word);

    vector<string> sp;
    while(!lq.empty()){
        current = lq.front();
        lq.pop();
        string fin = current.back();
        for(const string&  word: word_list){
            if(is_adjacent(fin,word) && !visited.contains(word)){
                visited.insert(word);
                vector<string> newlad = current;
                newlad.pushback(word);
                if(word == fin){
                    return newlad;
                    }
                lq.push(newlad);
    
            }
            }
        }
    return {};
}


void load_words(set<string> & word_list, const string& file_name){
    ifstream file(file_name);
    if(!file){
        error("", "", "file not found");
    }
    string in;
    while (file >> in) {
    word_list.insert(in);
    }
    file.close();
}

void print_word_ladder(const vector<string>& ladder){
    for (auto it = ladder.begin(); it != ladder.end(); it++){
            cout << *it;
            if (it != ladder.end() - 1)
                cout << " ";
        }
        cout << " " << endl;
    }
}

void verify_word_ladder(){}
