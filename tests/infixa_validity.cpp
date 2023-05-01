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

bool isValidOperation(const char* value){
  const char operations[4] = {'+', '-', '*', '/'};
  const char isValid[14] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '(', ')', '-', '+'};
  for(int i = 0; value[i] != '\0'; i++){
    char ch0 = '0'; // If no number before signal, assume 0.
    if(i != 0) ch0 = value[i-1]; //Previous character
    char ch = value[i]; // Character
    char ch2 = value[i+1]; //Next character
    bool firstCheck = false, secondCheck = false;
    for(size_t j = 0; j < sizeof(operations); j++){
      if(ch != operations[j]) continue;
      for (size_t k = 0; k < sizeof(isValid); k++){
        (firstCheck) ? (bool)1 : firstCheck = ch0==isValid[k];
        (secondCheck) ? (bool)1 : secondCheck = ch2==isValid[k]; 
      }
      if(!firstCheck || !secondCheck) return false;
    }
  }
  return true;
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

  for (size_t i = 0; i<tests.size(); i++){
    cout<<"Test "<<i<<": "<< tests[i].first<<" is "<<tests[i].second<<"\n";
    (isValidParentesis(tests[i].first) == tests[i].second) ? cout<<"success\n" : cout<<"fail\n";
  }
  cout<<"\n\n====Operational Validity======\n";
  tests = {
    {"8+-1", true},
    {"7*x", false},
    {"(8)*9", true},
    {"-9", true},
    {")*-10", true}, //Pass through operational validity but not through parentesis validity
    {"8**10", false},
    {"4/*10", false},
    {"9,856-10,789*3", true},
  };
   for (size_t i = 0; i<tests.size(); i++){
    cout<<"Test "<<i<<": "<< tests[i].first<<" is "<<tests[i].second<<"\n";
    (isValidOperation(tests[i].first) == tests[i].second) ? cout<<"success\n" : cout<<"fail\n";
  }

  return 0;

}