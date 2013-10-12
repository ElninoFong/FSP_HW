//Calculator.cc

#include <math.h>
#include "Calculator.h"

Calculator::Calculator(double C, double M, double i, int n) {
    _C = C;
    _M = M;
    _i = i;
    _n = n;
}

double Calculator::bondPriceCalc() {
    return (_C * (1 - 1 / pow((1+_i), _n)) / _i) + (_M / pow((1+_i), _n));
}

double Calculator::bondPriceCalc(double C, double M, double i, int n) {
    return (C * (1 - 1 / pow((1+i), n)) / i) + (M / pow((1+i), n));
}
