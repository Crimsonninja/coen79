#include "sequence.h"
#include <cassert>
#include <iostream>

namespace scu_coen79_3 {

	sequence::sequence() {
		used = 0;								// initialize used and current index variables to 0
		current_index = 0;
	}

	sequence::size_type sequence::size() const {
		return used;
	}

	void sequence::start() {
		current_index = 0;			// set the current index variable to 0
	}

	bool sequence::is_item() const {
		return current_index < used;
	}

	sequence::value_type sequence::current() const {
		assert(is_item());
		return data[current_index];		// returns the value at the current index
	}

	void sequence::advance() {
		assert(is_item());
		current_index++;
	}

	void sequence::insert(const value_type& entry) {
		assert(size() < CAPACITY);

		if (!is_item()) {
			start();
		}

		// std::cout << "entry :: " << entry << std::endl;
		// std::cout << "used :: " << used << std::endl;
		// std::cout << "current  :: " << current_index << std::endl;

	  if (is_item()) {
			for (sequence::size_type index = used; index > current_index; index--) {
				data[index] = data[index-1];
	  	}
	  	data[current_index] = entry;
	  }

	  // No item at current index. Insert at the front.
	  else {
			for (sequence::size_type index = used; index > 0; index--) {
				data[index] = data[index-1];
	    }
	    data[0] = entry;
			current_index = 0;
	  }

		used++;
	}

	void sequence::attach(const value_type& entry) {
		assert(size()<CAPACITY);
		//	data[current_index] = entry;
	  // If there are items at current index, shuffle and insert.
	  if (is_item()) {
	    for (sequence::size_type index = used; index > current_index+1; index--) {
	      data[index] = data[index-1];
	    }
	    data[current_index+1] = entry;
			current_index++;
	  }

	  // No item at current index. Insert at the end.
	  else {
	    data[used] = entry;
	    current_index = used;
	  }

	  used++;
	}

	void sequence::remove_current() {
		assert(is_item());
		for (size_type i = current_index+1; i < used; i++) {
			data[i-1]=data[i];
		}
		used--;
	}

	void sequence::insert_front(const value_type& entry) {
		start();
		insert(entry);
	}

	void sequence::remove_front() {
		start();
		remove_current();
	}

	void sequence::attach_back(const value_type& entry) {
		current_index = used;
		attach(entry);
	}

	void sequence::end() {
		current_index = used - 1;
	}

	sequence::value_type sequence::operator [] (sequence::size_type index) const {
		return data[index];
	}

	sequence operator+ (const sequence& seq1, const sequence& seq2) {
		assert(seq1.size() + seq2.size() < sequence::CAPACITY);
		sequence res;

		for (int i = 0; i < seq1.size(); ++i) {
			res.attach_back(seq1[i]);
		}

		for (int i = 0; i < seq2.size(); ++i) {
			res.attach_back(seq2[i]);
		}

		return res;
	}

	void operator += (sequence& seq1, const sequence& seq2) {		// seq1 is not const because we modify it
		for (int i = 0; i < seq2.size(); ++i)
      {
				seq1.attach_back(seq2[i]);
      }
	}

}

