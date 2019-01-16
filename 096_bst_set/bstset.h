#ifndef __BSTSET_H__
#define __BSTSET_H__
#include <iostream>

#include "cstdlib"
#include "set.h"

template<typename T>
class BstSet : public Set<T>
{
 private:
  class Node
  {
   public:
    T key;
    Node * left;
    Node * right;
    Node() : key(), left(NULL), right(NULL) {}
    Node(const T & key, Node * l, Node * r) : key(key), left(l), right(r) {}
  };
  Node * root;

 public:
  virtual void add(const T & key) {
    Node ** curr = &root;
    while (*curr != NULL) {
      if ((*curr)->key > key) {
        curr = &(*curr)->left;
      }
      else if ((*curr)->key < key) {
        curr = &(*curr)->right;
      }
    }
    *curr = new Node(key, NULL, NULL);
  }

  virtual bool contains(const T & key) const {
    Node * curr = root;
    while (curr != NULL) {
      if (curr->key == key) {
        return true;
      }
      else if (curr->key > key) {
        curr = curr->left;
      }
      else {
        curr = curr->right;
      }
    }
    return false;
  }
  Node * helper(Node * curr, const T & key) {
    if (curr == NULL) {
      return NULL;
    }
    else if (key == curr->key) {
      if (curr->left == NULL) {  //left is NULL
        Node * temp = curr->right;
        delete curr;
        return temp;
      }
      else if (curr->right == NULL) {  //right is NULL
        Node * temp = curr->left;
        delete curr;
        return temp;
      }
      else {  // neither is NULL,select the left-most right child (right once, then all the way left)
        Node * temp = curr->right;
        while (temp->left != NULL) {
          temp = temp->left;
        }
        curr->key = temp->key;
        curr->right = helper(curr->right, temp->key);
      }
    }
    else if (key < curr->key) {
      curr->left = helper(curr->left, key);
    }
    else if (key > curr->key) {
      curr->right = helper(curr->right, key);
    }
    return curr;
  }
  virtual void remove(const T & key) { root = helper(root, key); }

  BstSet() : root(NULL) {}

  Node * ad(Node * curr) {
    if (curr == NULL) {
      return NULL;
    }
    else {
      Node * temp = new Node(curr->key, NULL, NULL);
      temp->left = ad(curr->left);
      temp->right = ad(curr->right);
      return temp;
    }
  }

  BstSet(const BstSet<T> & rhs) : root(NULL) { root = ad(rhs.root); }
  BstSet<T> & operator=(const BstSet<T> & rhs) {
    if (this != &rhs) {
      delete_helper(root);
      root = ad(rhs.root);
    }
    return *this;
  }
  void delete_helper(Node * curr) {
    if (curr != NULL) {
      delete_helper(curr->left);
      delete_helper(curr->right);
      delete curr;
    }
  }

  virtual ~BstSet<T>() {
    Node * curr = root;
    delete_helper(curr);
  }
};

#endif
