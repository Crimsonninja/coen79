#include "pqueue.h"
#include <cassert>
#include <iostream>

using namespace std;

namespace coen79_lab8_5 {
  PriorityQueue::PriorityQueue() {
    head_ptr = NULL;
    many_nodes = 0;
  }

  PriorityQueue::PriorityQueue(const PriorityQueue &source) {
    if (source.head_ptr==NULL) {
      head_ptr = NULL;
      many_nodes = 0;
    } else {
      head_ptr = new node(source.head_ptr->data(),source.head_ptr->priority());
      node* traversalNode = head_ptr;
      node* sourceTraversalNode = source.head_ptr->link();
      node* theNewNode;
      while(sourceTraversalNode!=NULL) {
        theNewNode = new node(sourceTraversalNode->data(), sourceTraversalNode->priority());
        traversalNode->set_link(theNewNode);
        traversalNode = traversalNode->link();
        sourceTraversalNode = sourceTraversalNode->link();
      }
      many_nodes = source.many_nodes;
    }
  }

  PriorityQueue::~PriorityQueue() {
    node* remove_ptr;

    while(head_ptr!=NULL) {

      remove_ptr = head_ptr;
      head_ptr = head_ptr->link( );
      delete remove_ptr;
    }
    many_nodes = 0;
  }

  void PriorityQueue::insert(const Item &entry, unsigned int priority) {
    node* precursor=NULL;
    node* traversalNode = head_ptr;
    node* insertedNode = new node(entry, priority);
    if (head_ptr==NULL) {
      head_ptr = insertedNode;
    }
    else {
      while (traversalNode!=NULL&&traversalNode->priority()>=priority) {
        precursor = traversalNode;
        traversalNode = traversalNode->link();
      }
      if (precursor == NULL){
        insertedNode->set_link(head_ptr);
        head_ptr = insertedNode;
      } else {
        precursor->set_link(insertedNode);
        insertedNode->set_link(traversalNode);
      }
    }
    ++many_nodes;
  }

  PriorityQueue::Item PriorityQueue::get_front( ) {
    assert(size() > 0);
    Item data;
    node* remove_ptr = head_ptr;
    data = remove_ptr->data();
    head_ptr = head_ptr->link();
    delete remove_ptr;
    -- many_nodes;
    return data;
  }


  void PriorityQueue::operator = (const PriorityQueue &source) {
    if (this == &source) {
      return;
    }
    node *remove_ptr;
    while(head_ptr!=NULL) {
      remove_ptr = head_ptr;
      head_ptr = head_ptr->link( );
      delete remove_ptr;
    }
    many_nodes = 0;

    if (source.head_ptr==NULL) {
      head_ptr = NULL;
      many_nodes = 0;
    } else {
      head_ptr = new node(source.head_ptr->data(),source.head_ptr->priority());
      node* traversalNode = head_ptr;
      node* sourceTraversalNode = source.head_ptr->link();
      node* theNewNode;
      while(sourceTraversalNode!=NULL) {
        theNewNode = new node(sourceTraversalNode->data(), sourceTraversalNode->priority());
        traversalNode->set_link(theNewNode);
        traversalNode = traversalNode->link();
        sourceTraversalNode = sourceTraversalNode->link();
      }
      many_nodes = source.many_nodes;

    }
}

}
