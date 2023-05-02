#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include<string>

class EmptyStack {
  public:
    EmptyStack(){getMsg();};
    std::string getMsg(){return _msg;}
  private:
    std::string _msg = "Empty_Stack!";
};

class EmptyQueue {
  public:
    EmptyQueue(){getMsg();};
    std::string getMsg(){return _msg;}
  private:
    std::string _msg = "Empty_Queue!";
};


#endif