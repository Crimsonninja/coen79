#include "sequence.h"
#include "node.h"
#include <cassert>
#include <cstdlib>

namespace coen79_lab7 {
  sequence::sequence() {
    many_nodes = 0;
    head_ptr = NULL;
    tail_ptr = NULL;
    cursor = NULL;
    precursor = NULL;
  }

  sequence::sequence(const sequence &source) {
    many_nodes = source.size();
    list_copy(source.head_ptr, head_ptr, tail_ptr);
    cursor = NULL;
    precursor = NULL;
  }

  sequence::~sequence() {
    list_clear(head_ptr);
    many_nodes = 0;
  }

  void sequence::start() {
    precursor = NULL;
    cursor = head_ptr;
  }

  void sequence::end() {
    precursor = list_locate(head_ptr,many_nodes-1);
    cursor = precursor->link();
    tail_ptr = cursor;
  }

  void sequence::advance() {
    assert(is_item());
    cursor = cursor->link();
    if (precursor == NULL) {
      precursor = head_ptr;
    } else {
    precursor = precursor->link();
    }
  }

  void sequence::insert(const value_type& entry) {
    if (many_nodes == 0 || many_nodes == 1) {
      list_head_insert(head_ptr, entry);
      cursor = head_ptr;
      precursor = NULL;
      tail_ptr = cursor;
    } else if (precursor==NULL){
      // precursor = head_ptr;
      list_head_insert(head_ptr, entry);
      cursor = head_ptr;
      precursor=NULL;
    } else {
      list_insert(precursor, entry);
      cursor = precursor->link();
    }
    many_nodes++;
  }

  void sequence::attach(const value_type& entry) {
    if (head_ptr == NULL) {
      list_head_insert(head_ptr, entry);
      cursor = head_ptr;
      precursor = NULL;
      tail_ptr = head_ptr;
    } else if (precursor==NULL) {
      list_insert(cursor, entry);
      precursor = head_ptr;
      cursor = precursor->link();
      tail_ptr = cursor;
    } else {
      list_insert(cursor, entry);
      precursor = precursor->link();
      cursor = precursor->link();
      if (cursor->link()==NULL) {
        tail_ptr = cursor;
      }
    }
    many_nodes++;
  }

  void sequence::operator =(const sequence& source) {
    if (this == &source)
      return;
    list_clear(head_ptr);
    many_nodes = 0;
    list_copy(source.head_ptr, head_ptr, tail_ptr);
    many_nodes = source.size();
  }

  void sequence::remove_current() {
    assert(is_item());
    if (many_nodes == 0)
      return;
    if (precursor == NULL) {
      list_head_remove(head_ptr);
    } else {
      node* ptr_to_remove = cursor;
      precursor->set_link(cursor->link());
      delete ptr_to_remove;
      cursor = precursor->link();
    }
  }

  sequence::size_type sequence::size() const {
    return many_nodes;
  }

  bool sequence::is_item() const {
    if (cursor!=NULL) {
      return true;
    }
    return false;
  }

  sequence::value_type sequence::current() const {
    assert(is_item());
    return cursor->data();
  }
}
