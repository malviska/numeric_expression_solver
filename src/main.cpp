#include"../include/stack_dynamic.hpp"
#include"../include/exceptions.hpp"
#include<string>
#include<iostream>
#include<cstring>

/**
 * This function takes a string of postfix expression as input and returns a boolean value indicating if it is a valid postfix expression
 * 
 * @param posfix - The postfix notation expression to solve.
 * 
 * @return bool value indicating if it's valid or not.
 */
bool isValidPosfix(char * posfix) {
  // Declare a stack of doubles using StackDynamic class
  StackDynamic<double> st;
  // Initialize count and counter to zero
  int count = 0, counter = 0;
  // Declare a variable to store the converted number
  double num;
  // Declare a variable to store the current character in the postfix string
  char val = posfix[0];
  // Declare an array of characters to store individual numbers
  char get[10];
  // Declare a pointer to char to keep track of the endpoint of the number conversion
  char * endpointer;

  // Loop through the characters in the postfix string until the null character is reached
  while(val != '\0'){
    // Ignore any space character where the get array is empty
    if(val == ' ' && (strcmp(get, "\0") == 0))
      ;
    // When a space character is encountered, convert the number in get array and push it to the stack
    else if(val == ' '){
      // Convert the number in get array to a double
      num = strtod(get, &endpointer);
      // If endpointer points to the null character, it means the entire number has been successfully converted
      if(*endpointer == '\0')
        st.stack(num); // Push the number to the stack
      counter = 0; // Reset counter to zero
      memset(get, 0, sizeof(get)); // Clear the get array
    }
    // If the current character is a digit or a decimal point, add it to the get array
    else if(isdigit(val) || val == '.'){
      get[counter] = val;
      counter++;
    }
    // When an operator is encountered, pop the top two numbers from the stack, perform the operation,
    // and push the result back to the stack
    else if(val == '+' || val == '-' || val == '/' || val == '*'){
      // If the stack has less than two numbers, return false
      if(st.getSize() < 2)
        return false;
      double n = st.unstack(); // Pop the top number from the stack
      double m = st.unstack(); // Pop the second number from the stack
      double res;
      // Perform the operation based on the operator character
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
      st.stack(res); // Push the result back to the stack
    }else{
      return false; // If any other character is encountered, return false
    }
    count++;
    val = posfix[count];
  }
  // If the size of the stack is one, return true, else return false
  return st.getSize() == 1;
}


/**
 * Solves a mathematical expression in postfix notation.
 * 
 * @param posfix - The postfix notation expression to solve.
 * 
 * @return The result of the expression.
 */
double solve(char * posfix) {
  // Create a stack to hold the values of the expression.
  StackDynamic<double> st;
  // Initialize the counters and variables.
  int count = 0, counter = 0;
  double num;
  // Get the first character of the postfix expression.
  char val = posfix[0];
  // Create a buffer to hold the digits of a number.
  char get[10];
  // Create a pointer to be used with strtod to detect errors in number conversion.
  char * endpointer;
  
  // Continue while there are still characters in the postfix expression.
  while(val != '\0'){
    // If the character is a space and the buffer is empty, ignore it.
    if(val == ' ' && (strcmp(get, "\0") == 0))
      ;
    // If the character is a space and the buffer is not empty, the buffer contains a number, so convert it to a double and push it onto the stack.
    else if(val == ' '){
      // Convert the characters in the buffer to a double.
      num = strtod(get, &endpointer);
      // If there was no error in the conversion, push the double onto the stack.
      if(*endpointer == '\0')
        st.stack(num);
      // Reset the counter and buffer for the next number.
      counter = 0;
      memset(get, 0, sizeof(get));
    }
    // If the character is a digit or a decimal point, add it to the buffer.
    else if(isdigit(val) || val == '.'){
      get[counter] = val;
      counter++;
    }
    // If the character is an operator, pop two values from the stack, perform the operation, and push the result back onto the stack.
    else if(val == '+' || val == '-' || val == '/' || val == '*'){
      // If there are less than two values in the stack, the expression is invalid, so return false.
      if(st.getSize() < 2)
        return false;
      // Pop the two values from the stack.
      double n = st.unstack();
      double m = st.unstack();
      double res;
      // Perform the appropriate operation on the values.
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
          // If the second value is 0 and the operation is division, the expression is invalid, so return false.
          if(n == 0){
            return false;
          }
          res = m/n;
          break;
      }
      // Push the result of the operation back onto the stack.
      st.stack(res);
    }
    // If the character is not a space, a digit, or an operator, the expression is invalid, so return false.
    else{
      return false;
    }
    // Move to the next character in the postfix expression.
    count++;
    val = posfix[count];
  }
  // If there is more than one value in the stack after all operations have been performed, the expression is invalid, so return false.
  if (st.getSize() != 1) {
    return false;
  }
  // Return the result of the expression.
  return st.unstack();
}


/**
 * This function checks if the given string of parentheses is valid or not for a infix notation
 * It returns true if the parentheses are balanced, and false otherwise
 * @param value - the expression in infix notation
 * 
 * @return is valid parentesis or not
 */
bool isValidParentesis(char* value){
  
  // Initializing the opening and closing parentheses
  char initCell = '(';
  char endCell = ')';
  
  // Initializing the stack
  StackDynamic<int> allclosed;
  
  try{
    // Iterating through all the characters of the string
    for(int i = 0; value[i] != '\0'; i++){
      
      char ch = value[i]; // Current character
      char ch2 = value[i+1]; // Next character
      
      // Pushing into stack if an opening bracket is encountered
      if(ch == initCell){
        if(ch2 == endCell)
          return false; // Empty parentheses
        allclosed.stack(0);
      }
      
      // Popping from stack if a closing bracket is encountered
      if(ch == endCell){
        if(ch2 == initCell)
          return false; // Closed bracket followed by an open bracket without operator
        allclosed.unstack();
      }
    }
    
    // If stack is empty, the parentheses are balanced
    if(allclosed.empty()) return true;
    
    // If stack is not empty, the parentheses are unbalanced
    return false;
  }
  
  // Catching the EmptyStack exception that may be thrown by the unstack() function
  catch(EmptyStack& e){
    return false;
  }

}
/**
 * @brief checks if the expression has valid operations, meaning that every operator (* and /) is preceded and followed by a valid character. 
 * 
 * @param value 
 * @return true 
 * @return false 
 */
bool isValidOperation(char* value){
  const char operations[2] = {'*', '/'}; // Valid operators
  const char isValid[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '(', ')', '-', '+', '.', ' '}; // Valid characters
  for(int i = 0; value[i] != '\0'; i++){ // Iterate over all characters in the string
    char ch0 = '0'; // If no number before signal, assume 0.
    if(i != 0) ch0 = value[i-1]; //Previous character
    char ch = value[i]; // Character
    char ch2 = value[i+1]; //Next character
    bool firstCheck = false, secondCheck = false; // Initialize check variables
    for(size_t j = 0; j < sizeof(operations); j++){ // Iterate over all valid operators
      if(ch != operations[j]) continue; // Check if the current character is a valid operator
      for (size_t k = 0; k < sizeof(isValid); k++){ // Iterate over all valid characters
        (firstCheck) ? (bool)1 : firstCheck = ch0==isValid[k]; // Check if the previous character is valid
        (secondCheck) ? (bool)1 : secondCheck = ch2==isValid[k];  // Check if the next character is valid
      }
      if(!firstCheck || !secondCheck) return false; // If any of the checks fails, the operation is invalid
    }
  }
  return true; // If the loop finished, then the operation is valid
}

bool isValidInfixa(char * value){
  return isValidOperation(value) && isValidParentesis(value); // Check if both the operation and the parentheses are valid
}

/**
 * @brief takes a postfix mathematical expression as input and converts it to an infix expression. The function uses a dynamic stack data structure to keep track of the operands and operators in the expression as it traverses the input string. It scans the input string character by character, performing the necessary operations depending on the type of character it encounters (digit, operator, or space). Once the entire string has been processed, the resulting infix expression is stored in the result string passed as an argument. 
 * 
 * @param posfix 
 * @param result 
 */
void toInf(char * posfix, char* result) {
  // Create an instance of the dynamic stack with pointers to char
  StackDynamic<char *> st;
  // Initialize variables
  int count = 0, counter = 0, aux = 0;
  char val = posfix[0];
  int pCounter = 0;
  // Arrays for storing values and intermediate results
  char get[1000][10];
  char str1[10000], str2[10000], pointer[100][1000];

  // Loop through each character in the postfix string until end-of-string
  while(val != '\0'){
    // If the character is a space and the current value being parsed is empty, skip it
    if(val == ' ' && (strcmp(get[aux], "\0") == 0))
      ;
    // If the character is a space, push the parsed value onto the stack and reset variables
    else if(val == ' '){
      st.stack(get[aux]);
      aux++;
      counter = 0;
    }
    // If the character is a digit or a decimal point, append it to the current parsed value
    else if(isdigit(val) || val == '.'){
      get[aux][counter] = val;
      counter++;
    }
    // If the character is an operator (+, -, /, *), pop two values from the stack and perform the operation
    else if(val == '+' || val == '-' || val == '/' || val == '*'){
      // Pop two values from the stack
      char * n = st.unstack();
      char * m = st.unstack();
      // Make a copy of the first popped value
      char nCp[10000];
      strcpy(nCp, n);
      // Create strings for enclosing the second value in parentheses
      const char * par1 = "( ";
      const char * par2 = " )";
      // Construct the final string representing the operation
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
      // Store the intermediate result in an array
      strcpy(pointer[pCounter], str1);
      // Push the intermediate result onto the stack
      st.stack(pointer[pCounter]);
      pCounter++;
    }
    // Move to the next character in the postfix string
    count++;
    val = posfix[count];
  }
  // Copy the final value on the stack to the result string
  strcpy(result, st.unstack());
}

/**
 * @brief recursive algorithm that converts an infix arithmetic expression into a postfix expression using a stack data structure. The function takes a string value as input, which represents the infix expression, and it outputs a string posfix, which represents the postfix expression. The function also uses an integer index to keep track of the current index position in the input string value.
 * 
 * @param value - infix expression in char*
 * @param index - int value to keep track of the position in the recursive call
 * @param posfix - postfix value to be modified by the function
 */
void toPos(char* value, int& index, char* posfix) {
  StackDynamic<char> st; // Create an empty stack to hold operators
  char initCell = '('; // Define the initial cell as a left parenthesis
  char endCell = ')'; // Define the end cell as a right parenthesis
  char* aux = (char*)malloc(1000*sizeof(char)); // Allocate memory for an auxiliary character array

  // Loop through each character in the input expression
  for (; value[index] != '\0'; index++) {
    if (value[index] == ' ') continue; // Skip spaces
    if (value[index] == initCell) { // If the current character is a left parenthesis
      index++; // Increment the index
      toPos(value, index, posfix); // Recursively call toPos() on the substring inside the parentheses
      continue;
    }
    if (value[index] == endCell) { // If the current character is a right parenthesis
      while (!st.empty()) { // Pop all operators from the stack until it is empty
        strcpy(aux, posfix); // Copy the current postfix expression to the auxiliary array
        sprintf(posfix, "%s %c", aux, st.unstack()); // Append the popped operator to the postfix expression
      }
      free(aux); // Free the memory allocated for the auxiliary array
      return; // Return from the function
    }
    if (value[index] == '*' || value[index] == '/') { // If the current character is a multiplication or division operator
      if (!st.empty() && (st.top->item == '*' || st.top->item == '/')) { // If the stack is not empty and the top operator is also multiplication or division
        strcpy(aux, posfix); // Copy the current postfix expression to the auxiliary array
        sprintf(posfix, "%s%c", aux, st.unstack()); // Append the popped operator to the postfix expression
      }
      strcpy(aux, posfix); // Copy the current postfix expression to the auxiliary array
      sprintf(posfix, "%s%c", aux, ' '); // Append a space to the postfix expression
      st.stack(value[index]); // Push the current operator onto the stack
      continue; // Move on to the next character in the input expression
    }
    if (value[index] == '+' || value[index] == '-') { // If the current character is an addition or subtraction operator
     while (!st.empty()) { // Pop all operators from the stack until it is empty
        strcpy(aux, posfix); // Copy the current postfix expression to the auxiliary array
        sprintf(posfix, "%s %c", aux, st.unstack()); // Append the popped operator to the postfix expression
      }
      strcpy(aux, posfix); // Copy the current postfix expression to the auxiliary array
      sprintf(posfix, "%s%c", aux, ' '); // Append a space to the postfix expression
      st.stack(value[index]); // Push the current operator onto the stack
      continue; // Move on to the next character in the input expression
    }
    strcpy(aux, posfix); // Copy the current postfix expression to the auxiliary array
    sprintf(posfix, "%s%c", aux, value[index]); // Append the current operand to the postfix expression
  }

  while (!st.empty()) { // Pop all operators from the stack until it is empty
    strcpy(aux, posfix); // Copy the current postfix expression to the auxiliary array
    sprintf(posfix, "%s %c", aux, st.unstack()); // Append the popped operator to the postfix expression
  }
  free(aux);
}


// Program starts here
int main ()
{
  // Initialize variables and arrays
  char buffer[100000], str1[50], str2[50], str3[10000], aux[10000];
  int options = 0, index = 0;
  double result;

  // Infinite loop to read user input until program is closed
  while(true){
    // Read user input from standard input stream
    fgets(buffer, 100000, stdin);
    // Parse user input
    sscanf(buffer,"%s %s %10000[^\n]", str1, str2, str3);

    // Check if user wants to read and validate a postfix or infix expression
    if(strcmp(str1, "LER") == 0){
      if(strcmp(str2, "POSFIXA") == 0){
        options = 1;
        // Check if postfix expression is valid and print result
        isValidPosfix(str3) ? std::cout<<"EXPRESSAO OK:"<<str3<<std::endl : std::cout<<"ERRO: EXP NAO VALIDA"<<std::endl;
      }
      if(strcmp(str2, "INFIXA") == 0){
        options = 2;
        // Check if infix expression is valid and print result
        isValidInfixa(str3) ? std::cout<<"EXPRESSAO OK:"<<str3<<std::endl : std::cout<<"ERRO: EXP NAO VALIDA"<<std::endl;
      }
    }

    // Check if user wants to convert an expression to postfix notation
    if(strcmp(str1, "POSFIXA") == 0){
      if(str3 != NULL){
        // Convert expression to postfix notation and print result
        toPos(str3, index, aux);
        std::cout<<"POSFIXA:"<<aux<<'\n';
        index = 0;
        continue;
      }
      std::cout<<"ERRO: EXP NAO EXISTE\n";
    }

    // Check if user wants to convert an expression to infix notation
    if(strcmp(str1, "INFIXA") == 0){
      if(str3 != NULL){
        // Convert expression to infix notation and print result
        toInf(str3, aux);
        std::cout<<"POSFIXA:"<<aux<<'\n';
        index = 0;
        continue;
      }
      std::cout<<"ERRO: EXP NAO EXISTE\n";
    }

    // Check if user wants to solve an expression
    if(strcmp(str1, "RESOLVE") == 0){
      if(str3 != NULL && options == 2){
        // Convert infix expression to postfix notation, solve it, and print result
        toPos(str3, index, aux);
        result = solve(aux);
        std::cout<<"VAL:"<<result<<'\n';
        continue;
      }
      if(str3 != NULL && options == 1){
        // Solve postfix expression and print result
        result = solve(str3);
        std::cout<<"VAL:"<<result<<'\n';
        continue;
      }
      std::cout<<"ERRO: EXP NAO EXISTE\n";
    }

  }

}