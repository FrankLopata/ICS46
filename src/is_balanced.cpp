#include <iostream>
#include <fstream>
#include <stack>
using namespace std;
#include "is_balanced.h"

void error(string msg, char c){

    cout<<msg<<":"<<c<<endl;

}

bool is_balanced(string s){
    std::stack<char> stk;
    auto check_starter = [](char x){return x=='{'||x=='['||x=='<'||x=='(';};
    for(auto c:s){
        if(check_starter(c))
            stk.push(c);
        else{
            if(stk.empty())
                return false;
            char tp = stk.top();
            if(c=='('&&tp==')')
                stk.pop();
            else{
                if(c=='{'&&tp=='}')
                    stk.pop();
                else{
                    if(c=='['&&tp==']')
                        stk.pop();
                    else{
                        if(c=='<'&&tp=='>')
                            stk.pop();
                        else{
                            return false;
                            }
                        }
                    }
                }
            }
        }

    return stk.empty();

}

void test_is_balanced(){
    




}
