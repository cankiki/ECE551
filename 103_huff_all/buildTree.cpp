#include "node.h"

Node * buildTree(uint64_t * counts) {
  priority_queue_t pq;
  for (int i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      pq.push(new Node(i, counts[i]));
    }
  }
  while (pq.size() > 1) {
    Node * l = pq.top();
    pq.pop();
    Node * r = pq.top();
    pq.pop();
    Node * root = new Node(l, r);
    pq.push(root);
  }
  return pq.top();
  //WRITE ME!
}
