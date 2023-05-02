#ifndef QUEUE_DYNAMIC_H
#define QUEUE_DYNAMIC_H
#include"queue.hpp"
#include"cell.hpp"


template<typename ItemType>
class QueueDynamic : public Queue<ItemType>
{
  public:
    QueueDynamic();
    virtual ~QueueDynamic();

    void queue(ItemType item);
    ItemType unqueue();
    void clean();

  private:
    Cell<ItemType>* front;
    Cell<ItemType>* back;
};

#endif