// Calculator.h
#ifndef SYF_CALCULATOR__H
#define	SYF_CALCULATOR__H

class Bond_calculator_interface
{
protected:
	int _frequency;
    double _couponRate;
    double _rate;

    int _M;  // Maturity
    int _n;  // Number of periodes

    double _price;
    double _dv01;

public:
	Bond_calculator_interface() {};
	~Bond_calculator_interface() {};

	virtual double cal_bond_price(void) = 0;
	virtual double cal_bond_dv01(void) = 0;
	virtual double cal_bond_price_shift(double shift) = 0;
};

class Zero_coupon_calculator: public Bond_calculator_interface
{
public:
	Zero_coupon_calculator() {};
	~Zero_coupon_calculator() {};
	Zero_coupon_calculator(int frequency, double rate, int periodes);

	double cal_bond_price();
	double cal_bond_price_shift(double shift);
	double cal_bond_dv01();
};

class Coupon_bearing_calculator: public Bond_calculator_interface
{
protected:
	double _C; // Coupon

public:
	Coupon_bearing_calculator() {};
	~Coupon_bearing_calculator() {};
	Coupon_bearing_calculator(int frequency, double couponRate, double rate, int periodes);

	double cal_bond_price();
	double cal_bond_price_shift(double shift);
	double cal_bond_dv01();
};

#endif