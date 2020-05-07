#include <cctype>   // Provides toupper
#include <iostream>   // Provides cout and cin
#include <cstdlib>    // Provides EXIT_SUCCESS
#include "keyed_bag.h" // With value_type defined as double

using namespace std;
using namespace coen79_lab4;

int main(int argc, char const *argv[])
{
  keyed_bag kb1;
  kb1.insert(10, "hello");
  kb1.insert(5, "wahooya");
  keyed_bag kb2;
  kb2.insert(18, "okay");
  cout << kb1.get("wahooya") << endl;
  cout << kb2.get("okay") << endl;
  cout << kb1.size() << endl;
  keyed_bag kb3 = kb1 + kb2;
  cout << kb3.get("wahooya") << endl;
  cout << kb3.get("hello") << endl;

  kb3.erase("hello");

  kb1 += kb2;
  cout << kb1.get("okay") << endl;

  // cout << kb3.get("hello") << endl;
  cout << kb3.size();

  return EXIT_SUCCESS;
}
