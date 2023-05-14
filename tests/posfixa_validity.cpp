#include"../include/stack_dynamic.hpp"
#include"../include/stack_dynamic.hpp"
#include<cstring>
#include<iostream>
#include <cctype>
#include <vector>
using namespace std;



bool isValidPosfix(const char * posfix) {
  StackDynamic<double> st;
  int count = 0, counter = 0;
  double num;
  char val = posfix[0];
  char get[10];
  char * endpointer;
  while(val != '\0'){
    if(val == ' ' && (strcmp(get, "\0") == 0))
      ;
    else if(val == ' '){
      num = strtod(get, &endpointer);
      if(*endpointer == '\0')
        st.stack(num);
      counter = 0;
      memset(get, 0, sizeof(get));
    }
    else if(isdigit(val) || val == '.'){
      get[counter] = val;
      counter++;
    }
    else if(val == '+' || val == '-' || val == '/' || val == '*'){
      if(st.getSize() < 2)
        return false;
      double n = st.unstack();
      double m = st.unstack();
      double res;
      switch(val){
        case '+':
          res = m+n;
          break;
        case '-':
          res = m-n;
          break;
        case '*':
          res = m*n;
          break;
        case '/':
          if(n == 0){
            return false;
          }
          res = m/n;
          break;
      }
      st.stack(res);
    }else{
      return false;
    }
    count++;
    val = posfix[count];
  }
  return st.getSize() == 1;
}


int main () 
{
  cout<<"====Posfixa Validity======\n";
  vector<pair<const char*, bool>>  tests = {
    {"1.430560 6.889632 / 2.255391 9.655282 + 2.075334 - 0.822038 7.007894 * + / 9.827914 3.516262 6.577532 / - 2.560684 * 9.362095 / - 5.562911 7.878364 + 9.584948 + - 4.856426 * 0.766523 6.980499 / 8.642408 3.041649 - + 0.327483 7.814537 - * 9.022130 0.797961 6.797215 * 0.093923 + - / *", true},
    {"1.430560 6.889632 / 2.255391 9.655282 + 2.075334 - 0.822038 7.007894 * + / 9.827914 3.516262 6.577532 / - 2.560684 * 9.362095 / - 5.562911 7.878364 + 9.584948 + - 4.856426 * 0.766523 6.980499 / 8.642408 3.041649 - + 0.327483 7.814537 - * 9.022130 0.797961 6.797215 0.093923 + - / *", false}
    };
  for (size_t i = 0; i<tests.size(); i++){
    cout<<"Test "<<i<<": "<< tests[i].first<<" is "<<tests[i].second<<"\n";
    (isValidPosfix(tests[i].first) == tests[i].second) ? cout<<"success\n" : cout<<"fail\n";
  }


}