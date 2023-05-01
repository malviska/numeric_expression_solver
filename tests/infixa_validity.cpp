#include"stack_dynamic.hpp"
#include<iostream>
#include<string>
#include<utility>
#include<vector>
#include"exceptions.hpp"
using namespace std;

bool isValidParentesis(const char* value){
  char initCell = '(';
  char endCell = ')';
  StackDynamic<int> allclosed;
  try{
    for(int i = 0; value[i] != '\0'; i++){
      char ch = value[i]; // Character
      char ch2 = value[i+1]; //Next character
      if(ch == initCell){
        if(ch2 == endCell)
          return false; //Empty parentesis
        allclosed.stack(0);
      }
      if(ch == endCell){
        if(ch2 == initCell)
          return false; // Closed bracket followed by an open bracket without operator
        allclosed.unstack();
      }
    }
    if(allclosed.empty()) return true;
    return false;
  }
  catch(EmptyStack& e){
    return false;
  }

}



int main () 
{
  cout<<"====Parentesis Validity======\n";
  vector<pair<const char*, bool>>  tests = {
    {"()", false},
    {"(()*4)", false},
    {"(7*1", false},
    {"9+10)", false},
    {"((((75)*4)*5)+8", false},
    {"(20*(4+((1+2)*3)))", true},
    {"9+10", true},
    {")", false},
    {"9-(8+7)(4*5)", false}
  };

  for (unsigned int i = 0; i<tests.size(); i++){
    cout<<"Test 1: "<< tests[i].first<<" is "<<tests[i].second<<"\n";
    (isValidParentesis(tests[i].first) == tests[i].second) ? cout<<"success\n" : cout<<"fail\n";
  }
  cout<<"\n\n====Operational Validity======\n";
  tests = {
    {"8+-1", false},
    {"7*3", true},
    {"(8)*9", true},
    {"()*9)", true}, //Passes through operational test but not parentesis test.
    {"((((75)*4)*5)+8", false},
    {"(20*(4+((1+2)*3)))", true},
    {"9+10", true},
    {")", false},
    {"9-(8+7)(4*5)", false}
  };


  return 0;

}