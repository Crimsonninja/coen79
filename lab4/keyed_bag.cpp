#include "keyed_bag.h"
#include <cassert>
#include <iostream>

namespace coen79_lab4 {

  // This is a helper function that will later be used when checking for duplicate keys and overloading operators
  keyed_bag::key_type keyed_bag::get_key(const keyed_bag::size_type& index) const {
    return keys[index];
  }

  // Also a helper function
  keyed_bag::value_type keyed_bag::get_data(const keyed_bag::size_type& index) const {
    return data[index];
  }

  bool keyed_bag::has_key(const keyed_bag::key_type& key) const {
    for (keyed_bag::size_type i = 0; i < used; i++) {   // go through the keys array and see if the parameter matches
      if (keys[i] == key) {
        return true;
      }
    }
    return false;
  }

  keyed_bag::value_type keyed_bag::get(const keyed_bag::key_type& key) const {
    assert(has_key(key));
    keyed_bag::size_type index = 0;
    for (keyed_bag::size_type i = 0; i < used; i++) {
      if (keys[i] == key) {
        index = i;
      }
    }
    return data[index];
  }

  bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const {
    for (keyed_bag::size_type i = 0; i < size(); i++) {
      for (keyed_bag::size_type j = 0; j < otherBag.size(); j++) {
        if (get_key(i) == otherBag.get_key(j)) {    // go through both arrays and compare each and every item for duplicate keys
          return true;
        }
      }
    }
    return false;
  }

  keyed_bag::size_type keyed_bag::count(const keyed_bag::value_type& target) const {
    keyed_bag::size_type counter = 0;
    for (keyed_bag::size_type i = 0; i < used; i++) {
      if (data[i] == target) {    // go through the data array and check for the target, and increment the counter
        counter++;
      }
    }
    return counter;
  }

  bool keyed_bag::erase(const keyed_bag::key_type& key) {
    if (has_key(key)) {
      keyed_bag::size_type index = 0;
      for (keyed_bag::size_type i = 0; i < used; i++) {
        if (keys[i] == key) {   // go through keys array and if we find the key...
          index = i;
        }
      }
      keys[index] = keys[used]; // then we remove the key and replace with the last value (order doesn't matter)
      data[index] = data[used]; // (same with data/value array)
      used--;
      return true;              // and return true
    }
    return false;
  }

  void keyed_bag::insert(const keyed_bag::value_type& entry, const keyed_bag::key_type& key) {
    if (size() < CAPACITY && !has_key(key)) {
      keys[used] = key;       // insert key and data at the next spot in the bag
      data[used] = entry;
      used++;
    }
  }

  keyed_bag operator +(const keyed_bag& b1, const keyed_bag& b2) {
    assert(b1.size() + b2.size() <= keyed_bag::CAPACITY);
    keyed_bag res;
    if (!b1.hasDuplicateKey(b2)) {    // check for duplicate key, if there are we just return an empty bag
      for (keyed_bag::size_type i = 0; i < b1.size(); i++) {  // if check is successful, then insert contents of bag1
        res.insert(b1.get_data(i),b1.get_key(i));
      }
      for (keyed_bag::size_type i = 0; i < b2.size(); i++) {  // and insert contents of bag2
        res.insert(b2.get_data(i),b2.get_key(i));
      }
      return res;
    } else {
      cout << "Addition operator failed because there was one or more duplicate key(s)" << endl;
      return res;
    }
  }

  void operator +=(keyed_bag& bag1, const keyed_bag& bag2) {
    assert(bag1.size() + bag2.size() <= keyed_bag::CAPACITY);
    if(!bag1.hasDuplicateKey(bag2)){    // same algorithm as operator +
      for (keyed_bag::size_type i = 0; i < bag2.size(); i++) {
        bag1.insert(bag2.get_data(i),bag2.get_key(i));
      }
    } else {
      cout << "Addition equals operator failed because there was one or more duplicate keys" << endl;
    }

  }
}
