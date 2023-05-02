#include"stack_dynamic.hpp"
#include"exceptions.hpp"

template<typename ItemType>
StackDynamic<ItemType>::StackDynamic() : Stack<ItemType>() {
  top = NULL;
}

template<typename ItemType>
StackDynamic<ItemType>::~StackDynamic(){
  clean();
}

template<typename ItemType>
void StackDynamic<ItemType>::stack(ItemType item){
  Cell<ItemType> * now;
  now = new Cell<ItemType>();
  now->item = item;
  now->next = top;
  top = now;
  this->size++;
}

template<typename ItemType>
ItemType StackDynamic<ItemType>::unstack() {
  ItemType aux;
  Cell<ItemType> * p;
  if(this->size == 0)
    throw EmptyStack();
  aux = top->item;
  p = top;
  top = top->next;
  delete p;
  this->size--;

  return aux;
}

template<typename ItemType>
void StackDynamic<ItemType>::clean(){
  while(!this->empty())
    unstack();
}

template class StackDynamic<int>;
template class StackDynamic<char>;