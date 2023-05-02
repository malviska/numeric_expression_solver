#ifndef CELL_H
#define CELL_H
#include <cstddef>


template<typename ItemType>
class Cell 
{
  public:
    Cell();
    ItemType item;
    Cell * next;
  template<typename U>
  friend class StackDynamic;
  template<typename U>
  friend class QueueDynamic;

};


#endif