#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "holder.h"
#include "is_balanced.h"

void Stack_gtests(Stack & L){
    cout<<endl<<"//////////"<<endl<<"BEGINNING NEW STACK TEST FOR :"<<L.name<<endl<<"////////"<<endl<<"////////"<<endl;
    string s("word");
    cout<<"checking if empty : "<<L.is_empty()<<endl;
    cout<<"ADDING CHARS"<<endl;
    for(int i = 0;i<36;i++){
        
        L.push(s);
    }
    cout<<"Stack is :";
    L.print(cout);
    cout<<endl;
    cout<<"Top is :"<<L.top()<<endl;
    cout<<"TESTING POP"<<endl;
    for(int i = 0;i<36;i++){
        cout<<endl<<"Current Stack"<<endl;
        L.print(cout);
        cout<<"popping"<<endl;

    }
    cout<<"Pop ended"<<endl;


}
