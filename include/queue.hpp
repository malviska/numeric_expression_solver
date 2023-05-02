#ifndef QUEUE_H
#define QUEUE_H

template<typename ItemType>
class Queue
{
  public:
    Queue() {size = 0;}
    int getsize(){return size;}
    bool empty() {return size == 0;}

    virtual void queue(ItemType item) = 0;
    virtual ItemType unqueue() = 0;
    virtual void clean() = 0;

    protected:
      int size;
};



#endif QUEUE_H