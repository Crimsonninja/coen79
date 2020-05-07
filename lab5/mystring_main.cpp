#include <cctype>   // Provides toupper
#include <iostream>   // Provides cout and cin
#include <cstdlib>    // Provides EXIT_SUCCESS
#include "mystring.h" // With value_type defined as double

using namespace std;
using namespace coen79_lab5;

int main(int argc, char const *argv[])
{
  coen79_lab5::string woo = "Hello";
  coen79_lab5::string woo1 = " There.";
  char woo2 = 'I';
  char const woo3[] = " want to go home";
  woo += woo1;
  cout << woo<< endl;
  woo += woo2;
  cout << woo<< endl;
  woo += woo3;
  cout << woo<< endl;
  woo = woo1;
  cout << woo << endl;
  coen79_lab5::string woo4;
  cin >> woo4;
  cout << woo4 << endl;
  cout << (woo>=woo1) << endl;

  // getchar();
  return EXIT_SUCCESS;
}
