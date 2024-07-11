#ifndef COMPLEX_CLASS
#define COMPLEX_CLASS

#include <math.h>
#define PI 3.14159265358979323846

class Complex
{
    double re, im;

public:
    Complex(double new_real = 0, double new_imaginary = 0)
    {
        re = new_real;
        im = new_imaginary;
    }

    double real() const
    {
        return re;
    }

    double imag() const
    {
        return im;
    }

    Complex conj()
    {
        return Complex(re, -im);
    }

    double norm()
    {
        return sqrt(re * re + im * im);
    }

    double arg()
    {
        if (re == 0)
        {
            if (im > 0)
            {
                return PI / 2;
            }
            else if (im < 0)
            {
                return -PI / 2;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return atan(im / re);
        }
    }

    Complex polar(double mag, double angle = 0)
    {
        double re = mag * cos(angle);
        double im = mag * sin(angle);
        return Complex(re, im);
    }

    Complex operator+(Complex other)
    {
        return Complex(re + other.re, im + other.im);
    }

    friend Complex operator+(Complex, double);

    Complex operator-(Complex other)
    {
        return Complex(re - other.re, im - other.im);
    }

    friend Complex operator-(double, Complex);

    friend Complex operator-(Complex, double);

    Complex operator*(Complex other)
    {
        return Complex(re * other.re - im * other.im, re * other.im + other.re * im);
    }

    friend Complex operator*(double, Complex);

    friend Complex operator*(Complex, double);

    Complex operator/(Complex other)
    {
        double denominator = other.re * other.re + other.im * other.im;
        double re = (re * other.re + im * other.im) / denominator;
        double im = (im * other.re - re * other.im) / denominator;
        return Complex(re, im);
    }

    friend Complex operator/(double, Complex);

    friend Complex operator/(Complex, double);

    int operator==(Complex other)
    {
        return (other.im == im && other.re == re) ? 1 : 0;
    }

    int operator!=(Complex other)
    {
        return !((*this) == other);
    }

    Complex operator-()
    {
        return Complex(-re, -im);
    }
};

std::ostream &operator<<(std::ostream &os, Complex z)
{
    os << '(' << z.real() << ", " << z.imag() << ')';
    return os;
}

#endif