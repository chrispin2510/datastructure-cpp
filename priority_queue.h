#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>

const int INF = INT16_MAX;

template <class T>
class PriorityQueue
{
public:
    PriorityQueue(int capacity = 0);
    ~PriorityQueue();
    PriorityQueue(const PriorityQueue &);
    void set_capacity(int);
    int get_size() const;
    int get_capacity() const;
    void increment_size();
    void decrement_size();
    void insert(const T &);
    T peek_minimum() const;
    T delete_minimum();
    bool is_empty() const;
    bool is_full() const;
private:
    int size;
    int capacity;
    T *queue;
    void create_queue(int);
};

template <class T>
PriorityQueue<T>::PriorityQueue(int capacity)
{
    create_queue(capacity);
    size = 0;
}

template <class T>
PriorityQueue<T>::~PriorityQueue()
{
    delete[] queue;
}

template <class T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue &x)
{
    set_capacity(x.capacity);
    queue = new T[get_capacity()];
    if (get_size() >= x.size) {
        for (int i = 1; i <= x.size; i++) {
            queue[i] = x.queue[i];
        }
    }
    else {
        for (int i = 1; i <= get_size(); i++) {
            queue[i] = x.queue[i];
        }
    }
}

template <class T>
void PriorityQueue<T>::set_capacity(int capacity)
{
    this->capacity = capacity;
}

template <class T>
void PriorityQueue<T>::create_queue(int capacity)
{
    set_capacity(capacity);
    queue = new T[get_capacity()];
}

template <class T>
int PriorityQueue<T>::get_size() const
{
    return size;
}

template <class T>
int  PriorityQueue<T>::get_capacity() const
{
    return capacity;
}

template <class T>
void PriorityQueue<T>::increment_size()
{
    size++;
}

template <class T>
void PriorityQueue<T>::decrement_size()
{
    size--;
}

template <class T>
void PriorityQueue<T>::insert(const T &item)
{
    if (is_full()) {
        std::cerr << "Queue is full: Insertion is not possible. \n";
        exit(EXIT_FAILURE);
    }
    increment_size();
    queue[get_size()] = item;
    int i = get_size();
    int p = i / 2;
    while (p > 1 && (queue[p] > queue[i])) {
        std::swap(queue[i], queue[p]);
        i = p;
        p /= 2;
    }
}

template <class T>
T PriorityQueue<T>::peek_minimum() const
{
    return queue[1];
}

template <class T>
T PriorityQueue<T>::delete_minimum()
{
    if (is_empty()) {
        std::cerr << "Queue is empty: Deletion is not possible.\n";
        exit(EXIT_FAILURE);
    }
    T item = queue[1];
    queue[1] = queue[get_size()];
    decrement_size();
    bool flag = false;
    int i = 1, lchild = 0, rchild = 0, x = 0, y = 0;
    while ((flag == false) && (i < get_size())) {
        lchild = 2 * i;
        rchild = 2 * i + 1;
        if (lchild <= get_size())
            x = queue[lchild];
        else
            x = INF;
        if (rchild <= get_size())
            y = queue[rchild];
        else
            y = INF;
        if (queue[i] < x && queue[i] < y) {
            flag = true;
        }
        else if (x < y && queue[i] > x) {
            std::swap(queue[i], queue[lchild]);
            i = lchild;
        }
        else if (y < x && queue[i] > y) {
            std::swap(queue[i], queue[rchild]);
            i = rchild;
        }
    }
    return item;
}

template <class T>
bool PriorityQueue<T>::is_empty() const
{
    return get_size() == 0;
}

template <class T>
bool PriorityQueue<T>::is_full() const
{
    return get_size() >= get_capacity();
}

#endif /* PRIORITY_QUEUE */
