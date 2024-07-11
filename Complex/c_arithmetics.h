#include "Complex.h"

Complex operator+(Complex, double);

Complex operator-(double, Complex);

Complex operator-(Complex, double);

Complex operator*(double, Complex);

Complex operator*(Complex, double);

Complex operator/(double, Complex);

Complex operator/(Complex, double);

// definitions

Complex operator+(Complex c, double val)
{
    return Complex(c.re + val, c.im);
}

Complex operator-(double val, Complex c)
{
    return Complex(c.re - val, c.im);
}

Complex operator-(Complex c, double val)
{
    return Complex(c.re - val, c.im);
}

Complex operator*(double val, Complex c)
{
    return Complex(c.re * val, c.im * val);
}

Complex operator*(Complex c, double val)
{
    return Complex(c.re * val, c.im * val);
}

Complex operator/(double val, Complex c)
{
    return Complex(c.re / val, c.im / val);
}

Complex operator/(Complex c, double val)
{
    return Complex(c.re / val, c.im / val);
}
