/*
 * @author: Jonathan Trinh
 * @version 10282017
 * @description - mystring is the implementation of the string class defined
 *                mystring.h. We are reimplimenting the string class by overloading
 *                certain operators including +=, =, +, >>, <<, etc.
 */

#include <cctype>   // Provides toupper
#include <iostream>   // Provides cout and cin
#include <cstdlib>    // Provides EXIT_SUCCESS
#include "mystring.h"
namespace coen79_lab5 {

  // constructor
  string::string(const char str[]) {
    current_length = strlen(str);       // use strlen to find current length of string
    allocated = current_length + 1;     // to start, allocated will be 1 greater than allocated
    sequence = new char[allocated];     // initialize sequence to a new character array on heap memory
    strncpy(sequence, str, allocated);  // copy everything over
  }

  // copy constructor
  string::string(const string& source) {
    current_length = source.length();             // use source's length to get the current length
    allocated = current_length + 1;               // everything else is same as above
    sequence = new char[source.allocated];
    strncpy(sequence, source.sequence, allocated);
  }

  // destrcutor
  string::~string() {
    delete [] sequence;   // sequence is the only thing on heap memory so we just delete it
  }

void string::operator +=(const string& addend) {
    reserve((current_length + addend.length()) +1);   // we reserve space of current length and other string lengths + 1 (for null terminating character)
	  strncpy(sequence + current_length,addend.sequence,addend.length()+1);    // copy second string over starting at end of first string
    current_length += addend.current_length;          // add to the current length, the second string's length
  }

  void string::operator +=(const char addend[]) {
	reserve(current_length+strlen(addend)+1);      // same as above, but we need to use strlen to grab the length of second string
	strncat(sequence,addend,strlen(addend)+1);
	current_length += strlen(addend);
  }

  void string::operator +=(char addend) {
	reserve(allocated + 2);                        // we reserve for the current allocated + 2 (for the char we are adding and the null terminating char)
	sequence[current_length] = addend;
	current_length ++;
  }

  void string::reserve(size_t n) {
    char *larger_array;           // declare new pointer
    if (n == allocated)           // if we reserve the same amount, what's the point? just return
      return;
    if (n < current_length + 1)
      n = current_length + 1;

    larger_array = new char[n];   // initialize larger array to a new character array on heap memory
    strncpy(larger_array,sequence,n );  // copy everything over
	delete [] sequence;            // delete the old array
    sequence = larger_array;     // set the pointer to the larger_array
    allocated = n;
  }

  string& string::operator =(const string& source) {
    // *this += source;
    current_length = source.length();               // almost like the constructor but this string already exists
    allocated = current_length + 1;
    sequence = new char[source.allocated];
    strncpy(sequence, source.sequence, allocated);
    return *this;
  }

  char string::operator [](size_t position) const {
    return sequence[position];
  }

std::ostream& operator <<(std::ostream& outs, const string& source)
{
	outs << source.sequence;     // print the sequence
	return outs;
}


  bool operator ==(const string& s1, const string& s2) {
    return (strncmp(s1.sequence, s2.sequence,s1.current_length+1) == 0);
  }

  bool operator !=(const string& s1, const string& s2) {
    return (strncmp(s1.sequence, s2.sequence,s1.current_length+1) != 0);
  }

  bool operator > (const string& s1, const string& s2) {
    return (strncmp(s1.sequence, s2.sequence,s1.current_length+1) > 0);
  }

  bool operator < (const string& s1, const string& s2) {
    return (strncmp(s1.sequence, s2.sequence,s1.current_length+1) < 0);
  }

  bool operator >=(const string& s1, const string& s2) {
    return (strncmp(s1.sequence, s2.sequence,s1.current_length+1) >= 0);
  }

  bool operator <=(const string& s1, const string& s2) {
    return (strncmp(s1.sequence, s2.sequence,s1.current_length+1) <= 0);
  }

  string operator +(const string& s1, const string& s2) {
    string res;   // we can take advantage of += functions we've written above
    res += s1;
    res +=s2;
    return res;
  }

  string operator +(const string& s1, const char addend[ ]) {
    string res;
    res+=s1;
    res+=addend;
    return res;
  }

  std::istream& operator >> (std::istream& ins, string& target) {
    while (ins && isspace(ins.peek()))
      ins.ignore();
    char tmp;

    target = "";
    while (ins && !isspace(ins.peek()))
    {
      ins >> tmp;
      target += tmp;
    }

    return ins;
  }

}
