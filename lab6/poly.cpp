#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <climits>
#include "poly.h"

using namespace std;

namespace coen79_lab6 {

    // CONSTANTS
    // const unsigned int polynomial::MAXIMUM_DEGREE;

    // HELPER FUNCTIONS
    void polynomial::update_current_degree() {
        current_degree = 0;

        for (int i = coef_size; i > 0; i--) {
            if (coef[i] != 0.0)
            {
                current_degree = i;
                break;
            }
        }
    }

    void polynomial::reallocateForExponent(unsigned int exponent) {
        if (exponent == coef_size) {
            return;
        }
        if (exponent < current_degree + 1) {
            exponent = current_degree + 1;
        }
        double *temp;
        temp = new double[exponent+1];
        for (int i = 0;i < exponent; i++) {
            temp[i] = 0;
        }
        assert(temp!=NULL);
        for (int i = 0; i < coef_size; i++) {
            temp[i] = coef[i];
        }
        delete [] coef;
        coef = temp;
        coef_size = exponent;
    }

    // CONSTRUCTOR
	polynomial::polynomial(double c, unsigned int exponent){
        // assert(exponent <= polynomial::MAXIMUM_DEGREE);
        // reallocateForExponent(exponent);
        coef = new double [exponent + 1];
        coef_size = exponent;
        for (size_t i = 0; i <= coef_size; ++i) {
            if (i == exponent) {
                coef[i] = c;
            }
            else {
                coef[i] = 0.0;
            }
        }
        coef[exponent]=c;
        current_degree = exponent;
    }

    polynomial::polynomial(const polynomial& other) {
        coef_size = other.get_coef_size();
        coef = new double[coef_size + 1];
        current_degree = other.degree();
        for (int i = 0; i <= other.degree(); i++) {
            coef[i] = other.coef[i];
        }
    }

    polynomial::~polynomial() {
        delete [] coef;
    }

	// MODIFICATION MEMBER FUNCTIONS
	void polynomial::assign_coef(double coefficient, unsigned int exponent) {
        // assert(exponent <= polynomial::MAXIMUM_DEGREE);
        if (exponent > coef_size)
            reallocateForExponent(exponent);
        coef[exponent] = coefficient;
        update_current_degree();
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent){
        // assert(exponent <= polynomial::MAXIMUM_DEGREE);
        if (exponent > coef_size)
            reallocateForExponent(exponent);

        // Access, add, and assign.
        assign_coef(coefficient(exponent) + amount, exponent);
    }

	void polynomial::clear( ) {
        // Zero out all the coeficients.
        for (size_t i = 0; i <= current_degree; i++) {
            coef[i] = 0.0;
        }

        current_degree = 0;
    }

	// // CONSTANT MEMBER FUNCTIONS
    polynomial polynomial::antiderivative( ) const {
        // assert(this->degree() < polynomial::MAXIMUM_DEGREE);
        // if (this->degree() >= coef_size)
            // reallocateForExponent(this->degree());

        polynomial p;
        // Calculate anti-derivative.
        for (size_t i = 1; i <= this->degree()+1; i++) {
            p.assign_coef( this->coefficient(i-1) / i , i);
        }

        return p;
    }

	double polynomial::coefficient(unsigned int exponent) const {
        // Always return 0.0 if exponent is greater than maximum degree.
        if (exponent > coef_size)
            return 0.0;

        return coef[exponent];
    }

    double polynomial::definite_integral(double x0, double x1) const {
        polynomial anti = this->antiderivative();

        return anti.eval(x1) - anti.eval(x0);
    }

	polynomial polynomial::derivative( ) const {
        polynomial p;

        // Calculate derivative.
        for (size_t i = 0; i < this->degree(); i++) {
            p.assign_coef( this->coefficient(i+1) * (i+1) , i);
        }

        return p;
    }

	double polynomial::eval(double x) const {
        double sum = 0;
        // Evaluation loop.
        for (size_t i = 0; i <= current_degree; i++) {
            double cur_coef = coefficient(i);
            if (cur_coef != 0) {
                sum += cur_coef * pow(x, i);
            }
        }

        return sum;
    }

    bool polynomial::is_zero( ) const {
        if (current_degree == 0 && coef[0] == 0.0)
            return true;
        else
            return false;
    }

	unsigned int polynomial::next_term(unsigned int e) const {
        // Search for next term.
        for (size_t i = e+1; i <= current_degree; i++) {
            if (coef[i] != 0)
                return i;
        }
        return 0;
    }

    // Search for previous term.
	unsigned int polynomial::previous_term(unsigned int e) const {
        for (int i = e-1; i >= 0; i--) {
            if (coef[i] != 0)
                return i;
        }
        return UINT_MAX;
    }

    // // NON-MEMBER BINARY OPERATORS
    polynomial operator +(const polynomial& p1, const polynomial& p2)
    {
        polynomial p3 = p1;
        for (size_t i = 0; i <= p2.degree(); i++) {
            p3.add_to_coef(p2.coefficient(i), i);
        }

        return p3;
    }

    polynomial operator -(const polynomial& p1, const polynomial& p2) {
        polynomial p3 = p1;
        for (size_t i = 0; i <= p2.degree(); i++) {
            p3.add_to_coef(-p2.coefficient(i), i);
        }

        return p3;
    }

    polynomial operator *(const polynomial& p1, const polynomial& p2) {
        // assert(p1.degree( ) + p2.degree( ) <= polynomial::MAXIMUM_DEGREE);

        polynomial p3;
        if (p1.degree()+p2.degree() > p3.get_coef_size())
            p3.reallocateForExponent(p1.degree() + p2.degree());

        for (size_t i = 0; i <= p1.degree(); i++) {
            for (size_t j = 0; j <= p2.degree(); j++) {
                p3.add_to_coef(p1.coefficient(i) * p2.coefficient(j), i+j);
            }
        }

        return p3;
    }

    // NON-MEMBER OUTPUT FUNCTIONS
    std::ostream& operator << (std::ostream& out, const polynomial& p)
    {
        // Save output settings.
        long savedFlags = out.ios::flags();
        int pres = out.precision();
        out << std::fixed;
        out << std::setprecision(1);

        if (p.is_zero())
            out << 0.00;
        else
        {
            bool firstPrint = true;
            //  Loop through array.
            for (int i = p.degree(); i >= 0; i--) {
                double theCoef = p.coefficient(i);
                if (theCoef != 0) {
                    // Don't print a plus for first coefficient.
                    if (!firstPrint) {
                        out << ((theCoef < 0) ? " - " : " + ");
                    }

                    out << ((firstPrint) ? theCoef : abs(theCoef));
                    // No need to print x^0
                    if (i > 0)
                    {
                        out << "x";
                        // No need to print ^1
                        if (i > 1)
                            out << "^" << i;
                    }

                    if (firstPrint)
                        firstPrint = false;
                }
            }
        }

        // Restore output settings.
        out << setprecision(pres);
        // out.flags(savedFlags);
        return out;
    }
}
