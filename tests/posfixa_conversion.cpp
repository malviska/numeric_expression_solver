#include<iostream>
#include<string>
#include<utility>
#include<vector>
#include<cstring>
#include"../include/exceptions.hpp"
#include"../include/stack_dynamic.hpp"
using namespace std;


void toInf(const char * posfix, char* result) {
  StackDynamic<char *> st;
  int count = 0, counter = 0, aux = 0;
  char val = posfix[0], pCounter = 0;
  char get[1000][10];
  char str1[10000], str2[10000], pointer[100][1000];
  while(val != '\0'){
    if(val == ' ' && (strcmp(get[aux], "\0") == 0))
      ;
    else if(val == ' '){
      st.stack(get[aux]);
      aux++;
      counter = 0;
    }
    else if(isdigit(val) || val == '.'){
      get[aux][counter] = val;
      counter++;
    }
    else if(val == '+' || val == '-' || val == '/' || val == '*'){
      char * n = st.unstack();
      char * m = st.unstack();
      char nCp[10000];
      strcpy(nCp, n);
      const char * par1 = "( ";
      const char * par2 = " )";
      strcpy(str1, par1);
      strcpy(str2, par2); 
      strcat(str1, m);
      strcat(nCp, str2);
      char * op;
      switch(val){
        case '+':
          op = " + ";
          break;
        case '-':
          op = " - ";
          break;
        case '*':
          op = " * ";
          break;
        case '/':
          op = " / ";
          break;
        }
      strcat(str1, op);
      strcat(str1, nCp);
      strcpy(pointer[pCounter], str1);
      st.stack(pointer[pCounter]);
      pCounter++;
    }
    count++;
    val = posfix[count];
  }
  strcpy(result, st.unstack());
}

bool isEqual(const char* ch1, const char* ch2){
  for(int i = 0; ch1[i] != '\0'; i++){
    if(ch1[i] != ch2[i]) 
      return false;
  }
  return true;
}


int main () 
{
  cout<<"====Posfixa to infixa conversion======\n";
  vector<pair<const char*, const char *>>  tests = {
    {"1.430560 6.889632 / 2.255391 9.655282 + 2.075334 - 0.822038 7.007894 * + / 9.827914 3.516262 6.577532 / - 2.560684 * 9.362095 / - 5.562911 7.878364 + 9.584948 + - 4.856426 * 0.766523 6.980499 / 8.642408 3.041649 - + 0.327483 7.814537 - * 9.022130 0.797961 6.797215 * 0.093923 + - / *", "( ( ( ( ( ( 1.430560 / 6.889632 ) / ( ( ( 2.255391 + 9.655282 ) - 2.075334 ) + ( 0.822038 * 7.007894 ) ) ) - ( ( ( 9.827914 - ( 3.516262 / 6.577532 ) ) * 2.560684 ) / 9.362095 ) ) - ( ( 5.562911 + 7.878364 ) + 9.584948 ) ) * 4.856426 ) * ( ( ( ( 0.766523 / 6.980499 ) + ( 8.642408 - 3.041649 ) ) * ( 0.327483 - 7.814537 ) ) / ( 9.022130 - ( ( 0.797961 * 6.797215 ) + 0.093923 ) ) ) )"},
    };
  char* result = (char*)malloc(1000*sizeof(char));
  for (size_t i = 0; i<tests.size(); i++){
    cout<<"Test "<<i<<": "<< tests[i].first<<" is "<<tests[i].second<<"\n";
    toInf(tests[i].first, result);
    isEqual(result, tests[i].second) ? cout<<"SUCCESS!!\n" : cout<<"FAIL!!\n"; 
  }
  free(result);

  return 0;
}