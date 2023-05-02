#include"../include/queue_dynamic.hpp"
#include"../include/exceptions.hpp"


template<typename ItemType>
QueueDynamic<ItemType>::QueueDynamic() : Queue<ItemType>(){
  front = new Cell<ItemType>;
  back = front;
}


template<typename ItemType>
QueueDynamic<ItemType>::~QueueDynamic() {
  clean();
  delete front;
}

template<typename ItemType>
void QueueDynamic<ItemType>::queue(ItemType item){
  Cell<ItemType>* now = new Cell<ItemType>();
  now->item = item;
  back->next = now;
  back = now;
  this->size++;
}

template<typename ItemType>
ItemType QueueDynamic<ItemType>::unqueue() {
  Cell<ItemType> *p;
  ItemType aux;
  if(this->size == 0)
    throw EmptyQueue();
  aux =  front->next->item;
  p = front;
  front = front->next;
  delete p;
  this->size--;
  return aux;
}

template<typename ItemType>
void QueueDynamic<ItemType>::clean(){
  Cell<ItemType>* p;
  p = front->next;
  while(p!=NULL){
    front->next = p->next;
    delete p;
    p = front->next
  }
  this->size = 0;
  back = front;
}
