#ifndef STACK_DYNAMIC_H
#define STACK_DYNAMIC_H
#include"stack.hpp"
#include"cell.hpp"

template<typename ItemType>

class StackDynamic : public Stack<ItemType>
{
  public:
    StackDynamic();
    virtual ~StackDynamic();
    
    void stack(ItemType item);
    ItemType unstack();
    void clean();
  private:
    Cell<ItemType>* top;
};


#endif