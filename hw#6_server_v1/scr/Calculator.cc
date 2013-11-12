//Calculator.cc

#include <math.h>
#include "Calculator.h"

// Zero_coupon_calculator
Zero_coupon_calculator::Zero_coupon_calculator(int frequency, double rate, int periodes) {
	_frequency = frequency;
    _couponRate = 0.0;
    _rate = rate;
	_M = 100;
    _n = periodes;
}

double Zero_coupon_calculator::cal_bond_price() {
	double rate = _rate * 0.01 / _frequency;
    _price = _M / pow((1+rate), _n);
    return _price;
}

double Zero_coupon_calculator::cal_bond_price_shift(double shift) {
    double shift_rate = (_rate * 0.01 + shift) / _frequency;
    return _M / pow((1+shift_rate), _n);
}

double Zero_coupon_calculator::cal_bond_dv01() {
    _dv01 = (cal_bond_price_shift(-0.0001) - cal_bond_price_shift(0.0001)) / 2;
    return _dv01;
}

// Coupon_bearing_calculator
Coupon_bearing_calculator::Coupon_bearing_calculator(int frequency, double couponRate, double rate, int periodes) {
	_frequency = frequency;
    _couponRate = couponRate;
    _rate = rate;
	_M = 100;
    _n = periodes;
    _C = couponRate / frequency;
}

double Coupon_bearing_calculator::cal_bond_price() {
	double rate = _rate * 0.01 / _frequency;
    _price = (_C * (1 - 1 / pow((1+rate), _n)) / rate) + (_M / pow((1+rate), _n));
    return _price;
}

double Coupon_bearing_calculator::cal_bond_price_shift(double shift) {
    double shift_rate = (_rate * 0.01 + shift) / _frequency;
    return (_C * (1 - 1 / pow((1+shift_rate), _n)) / shift_rate) + (_M / pow((1+shift_rate), _n));
}

double Coupon_bearing_calculator::cal_bond_dv01() {
    _dv01 = (cal_bond_price_shift(-0.0001) - cal_bond_price_shift(0.0001)) / 2;
    return _dv01;
}
