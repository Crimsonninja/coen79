#include <cctype>
#include <iostream>
#include <cstdlib>
#include "mystring.h"

using namespace std;
using namespace coen79_lab6;

int main(int argc, char const *argv[])
{
  coen79_lab6::string str;
  str = "Hello";
  cout << str.search('o') << endl;
  str.replace('g',8);
  cout << str << endl;
  cout << str.count('l') << endl;
  str.dlt(0,2);
  cout << str << endl;
  return EXIT_SUCCESS;
}
