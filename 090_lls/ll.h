#define _LL_H_
#define _LL_H_
#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>
//YOUR CODE GOES HERE
using namespace std;

struct wrong : public std::exception {
  const char * what() const throw() { return "wrong\n"; }
};

template<typename T>
class LinkedList
{
 private:
  class Node
  {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : data(), next(NULL), prev(NULL) {}
    Node(const T & data, Node * next, Node * prev) : data(data), next(next), prev(prev){};
  };
  Node * head;
  Node * tail;
  int size;

 public:
  void addFront(const T & item) {
    head = new Node(item, head, NULL);
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
    size++;
  }
  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
    size++;
  }
  /*
  bool remove(const T & item) {
    if (head == NULL) {
      return false;
    }
    else if (head->data == item) {
      if (head->next == NULL) {
        Node * del = head;
        delete del;
        head = NULL;
        tail = NULL;
      }
      else {
        Node * del = head;
        Node * ans = head->next;
        delete del;
        head = ans;
        head->prev = NULL;
      }
      size--;
      return true;
    }
    else {
      Node * curr = head;
      while (curr->next != NULL && item != curr->next->data) {
        curr = curr->next;
      }
      Node * del = curr->next;
      if (curr->next == NULL) {
        curr->next = NULL;
        tail = curr;
        delete del;
      }
      else if (curr->next != NULL) {
        curr->next = curr->next->next;
        //    curr->next->prev = curr;
        delete del;
      }
      size--;
      return true;
    }
  }
  */
  bool remove(const T & item) {
    Node ** current = &head;
    while ((*current) != NULL && (*current)->data != item) {
      current = &(*current)->next;
    }
    if ((*current) == NULL) {
      return false;
    }
    Node * temp = (*current);
    if ((*current)->next == NULL) {
      tail = (*current)->prev;
      tail->next = NULL;
      //      (*current)->prev->next = NULL;
      // *current = (*current)->next;

      delete temp;
      size--;
      return true;
    }
    (*current)->next->prev = (*current)->prev;
    // *current = (*current)->next;
    //    (*current)->prev->next = (*current)->next;
    size--;
    delete temp;
    return true;
  } /*
  bool remove(const T & item) {
    Node ** current = &head;
    while ((*current) != NULL && (*current)->data != item) {
      current = &(*current)->next;
    }
    if ((*current) == NULL) {
      return false;
    }
    Node * temp = (*current);

    if ((*current)->next == NULL) {
      tail = (*current)->prev;
    }
    else {
      (*current)->next->prev = (*current)->prev;
    }
    *current = (*current)->next;
    size--;
    delete temp;
    return true;
  }
  */
  T & operator[](int index) {
    try {
      if (index < 0 || index >= size) {
        throw wrong();
      }
    }
    catch (std::exception & e) {
      cerr << "exception caught: " << e.what() << '\n';
      exit(EXIT_FAILURE);
    }

    Node * current = head;
    for (int i = 0; i < index; i++) {
      current = current->next;
    }
    return current->data;
  }
  const T & operator[](int index) const {
    try {
      if (index < 0 || index >= size) {
        throw wrong();
      }
    }
    catch (std::exception & e) {
      cerr << "exception caught: " << e.what() << '\n';
      exit(EXIT_FAILURE);
    }
    Node * current = head;
    for (int i = 0; i < index; i++) {
      current = current->next;
    }
    return current->data;
  }
  int find(const T & item) const {
    for (int i = 0; i < size; i++) {
      if ((*this)[i] == item) {
        return i;
      }
    }
    return -1;
  }
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  LinkedList(const LinkedList & rhs) {
    head = NULL;
    tail = NULL;
    size = 0;
    for (int i = 0; i < rhs.size; i++) {
      (*this).addBack(rhs[i]);
    }
  }
  LinkedList & operator=(const LinkedList & rhs) {
    LinkedList temp(rhs);
    size = rhs.size;
    std::swap(head, temp.head);
    std::swap(tail, temp.tail);
    return *this;
  }
  ~LinkedList() {
    /*Node * curr = head;
    for (int i = 0; i < size; i++) {
      delete curr[i].next;
      delete curr[i].prev;
    }
  }
    */
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
    tail = NULL;
  }

  int getSize() const { return size; }
  friend void testList(void);
};
