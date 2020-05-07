#include <cctype>   // Provides toupper
#include <iostream>   // Provides cout and cin
#include <cstdlib>    // Provides EXIT_SUCCESS
#include "poly.h" // With value_type defined as double

using namespace std;
using namespace coen79_lab4;

int main(int argc, char const *argv[])
{
  polynomial res(5,3);
  cout << res << endl;
  // res.add_to_coef(3,1);
  polynomial res4;
  // polynomial res(1,5);
  polynomial res2(2,1);
  polynomial res3 = res + res2;
  cout << res2 << endl;
  // for (int i = 0; i < res3.degree()+1; i++) {
  //   cout << res3.coefficient(i) << endl;;
  // }
  cout << res << endl;
  cout << res.derivative() << endl;
  cout << res3 << endl;
  // cout << res4.is_zero() << endl;;
  // cout << res.next_term(1) << endl;
  // cout << res.previous_term(3) << endl;
  // cout << res.eval(2) << endl;
  return EXIT_SUCCESS;
}
