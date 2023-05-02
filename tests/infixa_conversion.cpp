#include<iostream>
#include<string>
#include<utility>
#include<vector>
#include<cstring>
#include"../include/exceptions.hpp"
#include"../include/stack_dynamic.hpp"
using namespace std;

void toPos(const char* value, int& index, char*  posfix){
  StackDynamic<char> st;
  char initCell = '(';
  char endCell = ')';
  char* aux = (char*)malloc(1000*sizeof(char));
  for(; value[index] != '\0'; index++){
    if(value[index] == ' ') continue;
    if(value[index] == initCell){
      index++;
      toPos(value, index, posfix);
      continue;
    }
    if(value[index] == endCell){
      while(!st.empty()){
        strcpy(aux, posfix);
        sprintf(posfix, "%s %c", aux, st.unstack());
      }
      free(aux);
      return;
    }
    if(value[index] == '*' || value[index] =='/'){
      if(!st.empty() && (st.top->item == '*' || st.top->item == '/')){
        strcpy(aux, posfix);
        sprintf(posfix, "%s%c", aux, st.unstack());
      }
      strcpy(aux, posfix);
      sprintf(posfix, "%s%c", aux, ' ');
      st.stack(value[index]);
      continue;
    }
    if(value[index] == '+' || value[index] =='-'){
     while(!st.empty()){
        strcpy(aux, posfix);
        sprintf(posfix, "%s %c", aux, st.unstack());
      }
      strcpy(aux, posfix);
      sprintf(posfix, "%s%c", aux, ' ');
      st.stack(value[index]);
      continue;
    }
    strcpy(aux, posfix);
    sprintf(posfix, "%s%c", aux, value[index]);
  }
   while(!st.empty()){
    strcpy(aux, posfix);
    sprintf(posfix, "%s %c", aux, st.unstack());
  }
  free(aux);
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
  cout<<"====ConvertToPosfix======\n";
  vector<pair<const char*, const char*>>  tests = {
    {"5+3+2+4+6", "5 3 + 2 + 4 + 6 +"},
    {"5+4.5+7.8+9.10-11*8", "5 4.5 + 7.8 + 9.10 + 11 8 * -"},
    {"( ( ( ( 7.204409 ) - ( 0.933449 ) ) + ( ( 8.878333 ) / ( 4.141810 ) ) ) * ( 0.613876 ) )", "7.204409 0.933449 - 8.878333 4.141810 / + 0.613876 *"},
    {"( ( ( ( ( ( ( 1.430560 ) / ( 6.889632 ) ) / ( ( ( ( 2.255391 ) + ( 9.655282 ) ) - ( 2.075334 ) ) + ( ( 0.822038 ) * ( 7.007894 ) ) ) ) - ( ( ( ( 9.827914 ) - ( ( 3.516262 ) / ( 6.577532 ) ) ) * ( 2.560684 ) ) / ( 9.362095 ) ) ) - ( ( ( 5.562911 ) + ( 7.878364 ) ) + ( 9.584948 ) ) ) * ( 4.856426 ) ) * ( ( ( ( ( 0.766523 ) / ( 6.980499 ) ) + ( ( 8.642408 ) - ( 3.041649 ) ) ) * ( ( 0.327483 ) - ( 7.814537 ) ) ) / ( ( 9.022130 ) - ( ( ( 0.797961 ) * ( 6.797215 ) ) + ( 0.093923 ) ) ) ) )", 
    "1.430560 6.889632 / 2.255391 9.655282 + 2.075334 - 0.822038 7.007894 * + / 9.827914 3.516262 6.577532 / - 2.560684 * 9.362095 / - 5.562911 7.878364 + 9.584948 + - 4.856426 * 0.766523 6.980499 / 8.642408 3.041649 - + 0.327483 7.814537 - * 9.022130 0.797961 6.797215 * 0.093923 + - / *"}
  };
  char* posfix = (char*)malloc(1000*sizeof(char));
  for (size_t i = 0; i<tests.size(); i++){
    cout<<"Test "<<i<<": "<< tests[i].first<<"\n converts to\n "<<tests[i].second<<"\n";
    int index = 0;
    memset(posfix, 0, 1000);
    toPos(tests[i].first, index, posfix);
    cout<<"Output\n "<<posfix<<'\n';
    (isEqual(tests[i].second, posfix)) ? cout<<"success\n\n" : cout<<"fail\n\n";
  }
  free(posfix);
}
