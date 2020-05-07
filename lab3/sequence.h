#include <cstdlib>

#ifndef SEQUENCE_H
#define SEQUENCE_H

/*
 * @author Jonathan Trinh
 * @version 110717
 */
namespace scu_coen79_3 {
	class sequence {
	public:
		// TYPEDEFS and MEMBER CONSTANTS for the sequence class:

		// sequence::value_type is the data type of the items in the
		// sequence. It may be any of the C++ built-in types (int, char,
		// etc.), or a class with a default constructor, an assignment
		// operator, and a copy constructor.
		typedef double value_type;

		// sequence::size_type is the data type of any variable that keeps
		// track of how many items are in a sequence.
		typedef std::size_t size_type;

		// We define 50 as the maximum number of items that a sequence
		// can hold.
		static const size_type CAPACITY = 50;

		// CONSTRUCTOR for the sequence class:
		// Postcondition: The sequence has been initialized as an empty sequence.
		sequence();

		// MODIFICATION MEMBER FUNCTIONS for the sequence class:

		// Function: void start()
		// Postcondition: The first item on the sequence becomes the current
		// item(but if the sequence is empty, then there is no current item).
		void start();

		// Function: void advance();
		// Precondition: is_item returns true.
		// Postcondition: If the current item was already the last item in the
		// sequence, then there is no longer any current item. Otherwise, the
		// new current item is the item immediately after the original current // item.
		void advance();

		// Function: void insert(const value_type& entry)
		// Precondition: size( ) < CAPACITY.
		// Postcondition: A new copy of entry has been inserted in the
		// sequence before the current item. If there was no current item,
		// then the new entry has been inserted at the front of the sequence.
		// In either case, the newly inserted item is now the current item of
		// the sequence.
		void insert(const value_type& entry);

		// Function: void attach(const value_type& entry)
		// Precondition: size( ) < CAPACITY.
		// Postcondition: A new copy of entry has been inserted in the
		// sequence after the current item. If there was no current item, then
		// the new entry has been attached to the end of the sequence. In
		// either case, the newly inserted item is now the current item of the
		// sequence.
		void attach(const value_type& entry);

		// Function: void remove_current()
		// Precondition: is_item returns true.
		// Postcondition: The current item has been removed from the sequence,
		// and the item after this (if there is one) is now the new current item.
		void remove_current();

		// CONSTANT MEMBER FUNCTIONS for the sequence class:

		// Function: size_type size() const
		// Postcondition: The return value is the number of items in the
		// sequence.
		size_type size() const;

		// Function: bool is_item( ) const
		// Postcondition: A true return value indicates that there is a valid
		// "current" item that may be retrieved by
		// member function (listed below). A false
		// there is no valid current item.
		bool is_item() const;

		// Function: value_type current( ) const
		// Precondition: is_item( ) returns true.
		// Postcondition: The item returned is the
		// sequence.
		value_type current() const;

		// Additional useful member functions:

		void insert_front(const value_type& entry);
		void remove_front();
		void attach_back(const value_type& entry);
		void end();

		value_type operator [] (size_type index) const;

	private:
		value_type data[CAPACITY];
		size_type used;
		size_type current_index;
	};

	sequence operator + (const sequence& seq1, const sequence& seq2);
	void operator += (sequence& seq1, const sequence& seq2);
}
#endif
