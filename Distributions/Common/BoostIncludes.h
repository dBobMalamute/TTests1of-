#ifndef BOOSTINCLUDES_H
#define BOOSTINCLUDES_H
#include <tgmath.h>

template<typename T> inline T gammaFunction(T x)
{
    return tgamma(x);
}

template<typename T> inline T factorialFunction(T a)
{
    return tgamma(a - 1.0);
}

template<typename T> inline T beta(T a, T b)
{
    return beta(a, b);
}

double incbeta(double a, double b, double x);
template<typename T> inline T incompleteBeta(T a, T b, T x)
{
    return incbeta(a, b, x);

}

template<typename T> inline T errorFunction(T x)
{
    return erf(x);
}

float my_logf (float a);
float my_erfinvf (float a);

template<typename T> inline T inverseErrorFunction(T x)
{
    return my_erfinvf(x);
}


#endif // BOOSTINCLUDES_H
