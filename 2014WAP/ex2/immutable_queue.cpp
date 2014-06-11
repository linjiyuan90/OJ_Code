//
//  main.cpp
//  LearnCpp
//
//  Created by yuan on 5/25/14.
//  Copyright (c) 2014 yuan. All rights reserved.
//

#include <iostream>
#include "cassert"
#include "queue"
#include "stdexcept"
#include "memory"
#include "functional"


/*
 * immutable list
 * New data is prepend to head. The implementation use shared_ptr to ease work.
 */
template<typename T>
class List {
public:
  List();
  List(const T &head, const std::shared_ptr<List<T>> &tail);
  T head() const;
  // point to next immutable list
  std::shared_ptr<List<T>> tail() const;
  
  int size() const;
  bool empty() const;
private:
  int _size;
  T _head;
  std::shared_ptr<List<T>> _tail;
};

template<typename T>
List<T>::List() {
}

template<typename T>
List<T>::List(const T &head, const std::shared_ptr<List<T>> &tail) {
  _head = head;
  _tail = tail;
  _size = 1 + (tail == nullptr ? 0 : tail->size());
}

template<typename T>
int List<T>::size() const {
  return _size;
}

template<typename T>
bool List<T>::empty() const {
  return _size == 0;
}

/*
 * Return head of the list.
 * if the list is empty, throw range_error
 * @return
 * @exception range_error
 */
template<typename T>
T List<T>::head() const {
  if (_size == 0) {
    throw std::range_error("List is empty");
  }
  return _head;
}

/*
 * Return tail of the list.
 * if the list is empty, throw range_error
 * @return
 * @exception range_error
 */
template<typename T>
std::shared_ptr<List<T>> List<T>::tail() const {
  if (_size == 0) {
    throw std::range_error("List is empty");
  }
  return _tail;
}

/*
 * returns a new list with reversed order
 */
/*
template<typename T>
T reverse_list(const T &list, const T &rlist = T::make_shared()) {
  if (list->empty()) {
    return rlist;
  }
  return reverse_list(list->tail(), T::make_shared(list->head(), rlist));
}*/

// this should be faster since with less object construction
template<typename T>
std::shared_ptr<List<T>> reverse_list(const std::shared_ptr<List<T>> &list) {
  std::shared_ptr<List<T>> rlist;
  // which is better? p != nullptr or !p->empty()
  for (std::shared_ptr<List<T>> p = list; p != nullptr; p = p->tail()) {
    rlist = std::make_shared<List<T>>(p->head(), rlist);
  }
  return rlist;
}


/*
 * The Queue typename represents an immutable first-in-first-out (FIFO) queue of objects.
 * This queue use two List defined above as its storage:
 * leading is a normal order list, while order of trailing is reversed
 * enqueue will prepend element to trailing while dequeue will remove head of leading
 */
template<typename T>
class immutable_queue {
public:
  immutable_queue();
  ~immutable_queue();
  immutable_queue<T> enqueue(T &element);
  immutable_queue<T> dequeue();
  T peek();
  int size();
  immutable_queue<T>& operator == (const immutable_queue<T> &that);
  
private:
  typedef std::shared_ptr<List<T>> ListPtr;

  ListPtr leading;
  ListPtr trailing;
  
  immutable_queue(const ListPtr &leading, const ListPtr &trailing);
};

template<typename T>
immutable_queue<T>::immutable_queue() {
}

template<typename T>
immutable_queue<T>::~immutable_queue() {
}

/*
 * Private constructor, construct an new immutable_queue from two immutable lists
 * leading is a normal order list, while order of trailing is reversed
 */
template<typename T>
immutable_queue<T>::immutable_queue(const ListPtr &leading, const ListPtr &trailing):
  leading(leading), trailing(trailing) {
}

/*
 * Returns the queue that adds an item into the tail of this queue without modifying this queue.
 * <pre>
 * e.g.
 * when this queue represents the queue (2, 1, 2, 2, 6) and we enqueue the value 4 into this queue,
 * this method returns a new queue (2, 1, 2, 2, 6, 4)
 * and this object still represents the queue (2, 1, 2, 2, 6).
 * </pre>
 * if the element e is NULL, throw invalid_argument
 * @param e
 * @return
 * @exception invalid_argument
 */
template<typename T>
immutable_queue<T> immutable_queue<T>::enqueue(T &element) {
  if (&element == NULL) {
    throw std::invalid_argument("Can't enqueue NULL");
  }
  return immutable_queue(leading, ListPtr::make_shared(element, trailing));
}

/*
 * Returns the queue that removes the object at the head of this queue without modifying this queue.
 * <pre>
 * e.g.
 * when this queue represents the queue (7, 1, 3, 3, 5, 1)
 * this method returns a new queue (1, 3, 3, 5, 1)
 * and this object still represents the queue (7, 1, 3, 3, 5, 1).
 * </pre>
 * if the queue is empty, throw range_error
 * @return
 * @exception range_error
 */
template<typename T>
immutable_queue<T> immutable_queue<T>::dequeue() {
  // if (leading->empty() && trailing->empty()) {
  if (leading == nullptr && trailing == nullptr) {
    throw std::range_error("Can't dequeue an empty queue");
  }
  // if leading is empty, dump the elements in trailing to leading, and clear trailing
  // if (leading->empty()) {
  if (leading == nullptr) {
    leading = reverse_list(trailing);
    // an empty list
    // trailing = ListPtr::make_shared();
    trailing = nullptr;
  }
  return immutable_queue(leading->tail(), trailing);
}

/*
 * Looks at the object which is the head of this queue without removing it from the queue.
 * <pre>
 * e.g.
 * when this queue represents the queue (7, 1, 3, 3, 5, 1)
 * this method returns 7 and this object still represents the queue (7, 1, 3, 3, 5, 1).
 * </pre>
 * if the queue is empty, throw range_error
 * @return
 * @exception range_error
 */
template<typename T>
T immutable_queue<T>::peek() {
  if (leading == nullptr && trailing == nullptr) {
    throw std::range_error("Can't peak an empty queue");
  }
  if (leading == nullptr) {
    // if leading is empty, dump the elements in trailing to leading, and clear trailing
    leading = reverse_list(trailing);
    // an empty list
    trailing = nullptr;
  }
  return leading->head();
}

template<typename T>
immutable_queue<T>& immutable_queue<T>::operator == (const immutable_queue<T> &that) {
  leading = that.leading;
  trailing = that.trailing;
  return *this;
}

/*
 * Returns the number of objects in this queue.
 * @return
 */
template<typename T>
int immutable_queue<T>::size() {
  return (leading == nullptr ? 0 : leading->size()) + (trailing == nullptr ? 0 : trailing->size());
}

template<typename T>
std::ostream& operator << (std::ostream &os, immutable_queue<T> &queue) {
  immutable_queue<T> q = queue;
  os << "(";
  while (q.size() > 0) {
    os << q.peek();
    if (q.size() > 1) {
      os << ", ";
    }
    q = q.dequeue();
  }
  os << ")";
  return os;
}

void testImmutableQueue() {
  immutable_queue<int> queue;
  // test enqueue
  for (int i = 0; i < 10; ++i) {
    immutable_queue<int> _queue = queue.enqueue(i);
    queue = _queue;
    std::cout << queue << std::endl;
  }
  for (int i = 0; i < 10; ++i) {
    immutable_queue<int> _queue = queue.dequeue();
    queue = _queue;
    std::cout << queue << std::endl;
  }
}

