#include<iostream>
#include<string>
#include<utility>
#include<vector>
#include<cstring>
#include"../include/exceptions.hpp"
#include"../include/stack_dynamic.hpp"
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
