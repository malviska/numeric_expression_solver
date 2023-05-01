#ifndef STACK_H
#define STACK_H

template<typename ItemType>

class Stack 
{
  public:
    Stack() { size = 0; };
    int getSize() { return size;}
    bool empty() {return size == 0; }
    virtual void stack (ItemType item) = 0;
    virtual ItemType unstack() = 0;
    virtual void clean () = 0;

  protected:
    int size;

};


#endif