#include "poly.h"
#include <cassert>
#include <cmath>
#include <climits>
#include <algorithm>

namespace coen79_lab4 {

  polynomial::polynomial(double c, unsigned int exponent) {
    current_degree = exponent;
    coef[current_degree] = c;
  }

  void polynomial::update_current_degree() {
    for (unsigned int i = MAXIMUM_DEGREE; i > 0; i--) {
      if (coef[i]!=0) {     // start at the end of the array, until you find the first non-zero number
        current_degree = i; // its index is the current degree;
        return;
      }
    }
    current_degree = 0;
  }

  void polynomial::assign_coef(double coefficient, unsigned int exponent) {
    coef[exponent] = coefficient;
    update_current_degree();
  }

  void polynomial::add_to_coef(double amount, unsigned int exponent) {
    coef[exponent] = coef[exponent] + amount;
  }

  void polynomial::clear () {
    for(int i = 0; i < current_degree+1; i++) {
      coef[i] = 0;  // go through the entire array and make sure that every coefficient is 0.
    }
    current_degree = 0;
  }

  polynomial polynomial::antiderivative() const {
    polynomial res;
    for (int i = 0; i < current_degree + 1; ++i)
    {
      res.assign_coef(coef[i]/(i+1),i+1);   // shift everything one spot forward and divide by that new index
    }
    return res;
  }

  double polynomial::coefficient(unsigned int exponent) const {
    return coef[exponent];
  }

  double polynomial::definite_integral(double x0, double x1) const {
    polynomial temp = antiderivative();
    return temp.eval(x1) - temp.eval(x0);
  }

  polynomial polynomial::derivative() const {
    polynomial p1;
    for (int i = 0; i < current_degree+1; i++) {
      p1.assign_coef(coef[i+1]*(i+1), i);   // shift everything one spot backwards and multiply by old index
    }
    return p1;
  }

  double polynomial::eval(double x) const {
    double theNum = 0;
    for (int i = 0; i < current_degree+1; i++) {
      double polyEval = pow(x,i);           // raise x to the power corresponding to its index
      theNum += (coef[i]*polyEval);         // multiply by the coefficient
    }
    return theNum;
  }

  bool polynomial::is_zero() const {
    int count = 0;
    for (int i = 0; i < current_degree+1; ++i)
    {
      if (coef[i]==0) {       // check if current coefficient is zero
        count++;              // if condition is met, the increase the count
      }
    }
    if (count == current_degree+1)
    {
      return true;          // if the count matches current degree + 1, polynomial has all zeroes
    }
    return false;
  }

  unsigned int polynomial::next_term(unsigned int e) const {
    for (int i = e; i < current_degree + 1; i++) {
      if (coefficient(i)!=0) {  // go through array forward (starting at e) and check if a coefficient is not zero
        return i;               // if condition is met, we have a next term at "i"
      }
    }
    return 0;                   // otherwise return 0
  }

  unsigned int polynomial::previous_term(unsigned int e) const {
    for (int i = e; i > 0; i--) { // the above algorithm but check the array going backwards
      if (coefficient(i)!=0) {
        return i;
      }
    }
    return UINT_MAX;
  }

  polynomial operator +(const polynomial& p1, const polynomial& p2) {
    polynomial p3;

    for (int i = 0; i <= fmax(p1.degree(),p2.degree()); i++) {  // go through array and add each position of p1 and p2 storing into p3
      p3.assign_coef(p1.coefficient(i) + p2.coefficient(i), i);
    }

    return p3;
  }

  polynomial operator -(const polynomial& p1, const polynomial& p2) {
    polynomial p3;

    for (int i = 0; i <= fmax(p1.degree(),p2.degree()); i++) {  // go through array and subtract each position of p1 and p2 storing into p3
      p3.assign_coef(p1.coefficient(i) - p2.coefficient(i), i);
    }

    return p3;
  }

  polynomial operator * (const polynomial& p1, const polynomial& p2) {
    assert(p1.degree() + p2.degree() <= polynomial::MAXIMUM_DEGREE);
    polynomial p3;
    for (int i = p1.degree(); i > -1; i--) {
      for (int j = p2.degree(); i > -1; i--) {
        p3.assign_coef(p1.coefficient(i)*p2.coefficient(j),i+j);
      }
    }
    return p3;
  }

  std::ostream& operator << (std::ostream& out, const polynomial& p) {
    for (int i = p.degree(); i > -1; i--) {
      out << p.coefficient(i) << "x^" << i << "\t";
    }

    return out;
  }

}
