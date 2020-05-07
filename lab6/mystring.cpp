#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cassert>

// For ops on char*
#include "string.h"

// My string header
#include "mystring.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::ostream;
using std::istream;

// To enter debug mode, change DEBUGMODE to 1.  This
// is handy when you need to convince yourself exactly
// which of the methods is being called when
#define DEBUGMODE 0
#define DEBUG(s) if (DEBUGMODE) cerr << s << endl;

namespace coen79_lab6
{
	// Some of below implementation is copied from:
	// http://www-cs-students.stanford.edu/~wolfe/cpp/Mystring.cpp
	// and then modified.

	// CONSTRUCTORS AND DESTRUCTORS

	//
	// Constructor called when a string is constructed
	// with a char*.
	//
	string::string(const char str[])
	{
		DEBUG("Char* constructor")

		// Allocate enough space for the char*
		current_length = strlen(str);
		sequence = NULL;
		allocated = 0;
		reserve(current_length+1);
		sequence[0] = '\0';

		// Copy the char* into the internal string data
		strncpy(sequence, str, allocated);
	}

	string::string(char c) {
		current_length = 1;
		sequence = NULL;
		allocated = 0;
		reserve(current_length+1);
		sequence[0] = c;
		sequence[1] = '\0';
	}

	//
	// Copy constructor.
	//
	string::string(const string& source)
	{
		DEBUG("string constructor")

		// Allocate enough space for the new string
		current_length = source.length();
		sequence = NULL;
		allocated = 0;
		reserve(current_length+1);

		// Copy the string buffer from the new string into
		// myself (I can access the private sequence in str
		// because I am also a member of string
		strncpy(sequence, source.sequence, allocated);
	}

	//
	// Destructor
	//
	string::~string()
	{
		DEBUG("Delete a str (" << sequence << ")")
		delete [] sequence;
	}

	// MODIFICATION MEMBER FUNCTIONS

	void string::operator +=(const string& addend)
	{
		DEBUG("String += operator string& parameter.")

		// Temp string to old the original data

		// Allocate enough space for both string
		reserve(current_length + addend.length() + 1);

		// Concat the strings
		strncat(sequence, addend.sequence, allocated - current_length);
		current_length += addend.length();
	}

	void string::operator +=(const char addend[ ])
	{
		DEBUG("String += operator char[] parameter.")
		string temp(addend);
		(*this) += temp;
	}

	void string::operator +=(char addend)
	{
		DEBUG("String += operator char parameter.")
		char temp[2];
		temp[0] = addend;
		temp[1] = '\0';
		(*this) += temp;
	}

	//
	// Increases size of sequence array if n > current size.
	//
	void string::reserve(size_t n)
	{
		DEBUG("Attempting to reserve " << n)
		// Only increase size with this function.
		if (n == allocated)
			return;

		if (n < current_length+1)
			n = current_length+1;

		char *temp = sequence;
		sequence = new char[n];
		assert(sequence != NULL);
		if (temp != NULL) {
			strncpy(sequence, temp, n);
			delete [] temp;
		}
		allocated = n;
	}

	//
	// Assignment of a string into another string
	//
	string& string::operator=(const string& source)
	{
		DEBUG("string assignment operator")

		if (&source == this)
		{
			DEBUG("Not copying myself");
			return *this;
		}
		// Delete the old string that this class was holding.

		// Allocate enough space for the new string.
		current_length = source.length();
		reserve(current_length+1);

		// Copy the new string into myself
		strncpy(sequence, source.sequence, allocated);

		// Return myself
		return *this;
	}

	void string::insert(const string& source, unsigned int position) {
		// current_length += source.length();
		// reserve(current_length + source.length() + 1);
		char temp[allocated];
		strncpy(temp, sequence + position, source.length());
		sequence[position] = '\0';
		*this+=source;
		*this+=temp;
	}

	void string::dlt(unsigned int position, unsigned int num) {
		for (int i = position + num; i < current_length; ++i) {
			sequence[i]=sequence[i-num];
		}
		current_length -= num;
		sequence[position + num] = '\0';
	}

	void string::replace(char c, unsigned int position) {
		sequence[position] = c;
	}

	void string::replace(const string& source, unsigned int position) {
		// for (int i = position; i < position + source.length(); ++i) {

		// }
		strncpy(sequence + position, source.sequence, source.length());
	}

	int string::search(char c) const {
		for (int i = 0; i < current_length; ++i) {
			if (sequence[i] == c) {
				return i;
			}
		}
		return -1;
	}

	int string::search(const string& substring) const {
		for (int i = 0; i < current_length - substring.length(); ++i) {
			if (strncmp(sequence + i, substring.sequence, substring.length())) {
				return i;
			}
		}
		return -1;
	}

	unsigned int string::count(char c) const {
		unsigned int count = 0;
		for (int i = 0; i < current_length; ++i) {
			if (sequence[i] == c) {
				count ++;
			}
		}
		return count;
	}

	//
	// Return the character at a given position
	//
	char string::operator[](size_t pos) const
	{
		DEBUG("Calling []");
		if (pos >= length())
		{
			cerr << "Tried to access invalid string index\n";
			exit(1);
		}
		return sequence[pos];
	}

	// FRIEND FUNCTIONS

	//
	// Send the string to an output string.
	//
	ostream& operator<<(ostream& outs, const string& source)
	{
		DEBUG("<< operator")
		return outs << source.sequence;
	}

	//
	// Return if s2 is equal to s1 in
	// alphanumeric order
	bool operator==(const string&s1, const string& s2)
	{
		DEBUG("Calling ==");
		return (bool)(strcmp(s1.sequence, s2.sequence) == 0);
	}

	//
	// Return if s2 is not equal to s1 in
	// alphanumeric order
	bool operator !=(const string& s1, const string& s2)
	{
		DEBUG("Calling !=");
		return !(s1 == s2);
	}

	//
	// Return if s2 is before s1 in
	// alphanumeric order
	bool operator>(const string&s1, const string& s2)
	{
		DEBUG("Calling >");
		return (bool)(strcmp(s1.sequence, s2.sequence) > 0);
	}

	//
	// Return if s2 string is after s1 in
	// alphanumeric order
	bool operator<(const string&s1, const string& s2)
	{
		DEBUG("Calling <");
		return (bool)(strcmp(s1.sequence, s2.sequence) < 0);
	}

	//
	// Return if s2 is equal to or after s1 in
	// alphanumeric order
	bool operator >=(const string& s1, const string& s2)
	{
		DEBUG("Calling >=");
		return (s1 > s2 || s1 == s2);
	}

	//
	// Return if s2 is equal to or before s1 in
	// alphanumeric order
	bool operator <=(const string& s1, const string& s2)
	{
		DEBUG("Calling <=");
		return (s1 < s2 || s1 == s2);
	}

	// NON-MEMBER FUNCTIONS

	//
	// Concatenation of two strings
	//
	string operator+(const string& s1, const string& s2)
	{
		DEBUG("String + operator with 2 strings")

		// Temp string to old the original data
		string tmp;

		tmp += s1;
		tmp += s2;

		// Return the temporary string
		return tmp;
	}

	string operator+(const string& s1, const char addend[ ]) {
		DEBUG("String + operator with 1 string and 1 character array.")
		return s1 + string(addend);
	}

	// Read from an input stream
	//
	istream& operator>>(istream& ins, string& target)
	{
		DEBUG(">> operator")
		// Skip white space characters.
		while (ins && isspace(ins.peek()))
			ins.ignore();



		char tmp;

		// Clear the target string.
		target = "";

		// Read characters from the stream;
		while (ins && !isspace(ins.peek()))
		{
			ins >> tmp;
			target += tmp;
		}

		return ins;
	}
}
