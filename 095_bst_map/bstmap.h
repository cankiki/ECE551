#ifndef __BSTMAP_H__
#define __BSTMAP_H__

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "map.h"
template<typename K, typename V>
class BstMap : public Map<K, V>
{
 private:
  class Node
  {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node() : key(), value(), left(NULL), right(NULL) {}
    Node(const K & key, const V & value, Node * l, Node * r) :
        key(key),
        value(value),
        left(l),
        right(r) {}
  };
  Node * root;

 public:
  virtual void add(const K & key, const V & value) {
    Node ** curr = &root;

    while (*curr != NULL) {
      if ((*curr)->key > key) {
        curr = &(*curr)->left;
      }
      else if ((*curr)->key < key) {
        curr = &(*curr)->right;
      }
      else {
        (*curr)->value = value;
        return;
      }
    }
    *curr = new Node(key, value, NULL, NULL);
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * curr = root;
    while (curr != NULL) {
      if (curr->key == key) {
        return curr->value;
      }
      else if (curr->key > key) {
        curr = curr->left;
      }
      else {
        curr = curr->right;
      }
    }
    throw std::invalid_argument("The key is not found.");
  }
  Node * helper(Node * curr, const K & key) {
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
        curr->value = temp->value;
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
  virtual void remove(const K & key) { root = helper(root, key); }

  BstMap() : root(NULL) {}

  Node * ad(Node * curr) {
    if (curr == NULL) {
      return NULL;
    }
    else {
      Node * temp = new Node(curr->key, curr->value, NULL, NULL);
      temp->left = ad(curr->left);
      temp->right = ad(curr->right);
      return temp;
    }
  }

  BstMap(const BstMap<K, V> & rhs) : root(NULL) { root = ad(rhs.root); }
  BstMap<K, V> & operator=(const BstMap<K, V> & rhs) {
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

  virtual ~BstMap<K, V>() {
    Node * curr = root;
    delete_helper(curr);
  }
};

#endif
