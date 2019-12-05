#include "rational.h"
#include "gcd.h"

#include <stdexcept>
#include <ostream>
#include <iostream>

// Implement this
const Rational Rational::inverse() const {
  return Rational{ this->_den, this->_num };
}

// Implement this
Rational::sign_type Rational::sign() const {
  return (this->_num >= 0) ? POSITIVE : NEGATIVE;
}

/* Print the value num/den to the supplied output stream, or 0 if 
 * the Rational happens to be identically zero.
 */
std::ostream& operator<<( std::ostream &os, const Rational &ratio ) {
  if( ratio == 0 ) {
    os << "0";
  } else {
    if( ratio.sign() == Rational::NEGATIVE ) {
      os << "-";
    }
    os << std::abs( ratio.num() ) << "/" << std::abs( ratio.den() );
  }
  return os;
}

/* This function will be called whenever the 
 * Rational is constructed from integers that
 * are supplied as numerator and denominator.
 * It should reduce the fraction to lowest terms;
 * for example, when we try to construct a
 * Rational{ 4, -8 }, this is the function that
 * will cause the number to be exactly the same
 * as Rational{ -1, 2 }. Numerators should be
 * the only value potentially negative after
 * the call to ::normalize().
 * Throw bad_rational if there is an attempt
 * to set one with a zero denominator.
 */
void Rational::normalize() {
  if (this->_den == 0) {
    throw bad_rational();
  }
  intmax_t gcd_ = gcd(std::abs(this->_num), std::abs(this->_den));
  this->_num /= gcd_;
  this->_den /= gcd_;
  if (this->_den < 0) {
    this->_num *= -1;
    this->_den *= -1;
  }
}

// Return the float precision number corresponding to the Rational
float Rational::to_float() const {
  return (float)this->_num / this->_den;
}

// Return the double precision number corresponding to the Rational
double Rational::to_double() const {
  return (double)this->_num / this->_den;
}
