#include <cctype>
#include <iostream>
#include <cstdlib>
#include "poly.h"

using namespace std;
using namespace coen79_lab6;

int main(int argc, char const *argv[])
{
  polynomial res(5,3);
  cout << res << endl;
  polynomial res2(res);
  cout << res2 << endl;
  polynomial res3 = res.antiderivative();
  cout << res3 << endl;
  cout << res3.definite_integral(3,5) << endl;
  cout << res3.derivative() << endl;
  res.add_to_coef(3,1);
  cout << res << endl;
  res.clear();
  cout << res << endl;
  return EXIT_SUCCESS;
}
