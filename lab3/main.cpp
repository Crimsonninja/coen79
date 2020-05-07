#include <cctype>   // Provides toupper
#include <iostream>   // Provides cout and cin
#include <cstdlib>    // Provides EXIT_SUCCESS
#include "sequence.h" // With value_type defined as double

using namespace std;
using namespace scu_coen79_3;

// A separate test file

void show_sequence(sequence display) {
  for (display.start(); display.is_item(); display.advance())
    cout << display.current() << endl;
}

int main() {
  // sequence test;
  // sequence test2;
  // sequence test3;
  // test.attach_back(5.0);
  // test.attach_back(625.0);
  // test2.attach_back(8.3);
  // test2.attach_back(5.3);
  // test+=test2;
  // cout << test[1] << endl;
  // test.start();
  // cout << test.current() << endl;
  sequence test;
  sequence test2;
  sequence test3;
  test.insert(5.0);
  test.insert(625.0);
  test2.insert(8.3);
  test2.insert(5.3);
  test3 = test + test2;
  // test += test2;
  //test.start();
  // cout << test[3] << endl;
  show_sequence(test3);
  //test3 = test + test2;
  //show_sequence(test3);

// test3.advance();
// cout << test3.current() << endl;
}
