#ifndef SYF_BOND__H
#define SYF_BOND__H

#include "SBB_io.h"
#include "YieldCurve.h"
#include "SBB_ratings.h"
#include "Calculator.h"
#include <string>
using namespace std;

#define RATETYPE_YIELD "YIELD"
#define RATETYPE_SPREAD "SPREAD"

class Bond
{
private:
	string _security_id;
	string _bond_id;
	string _bond_type;

	double _bond_price;
	double _bond_dv01;
	double _bond_risk;
	double _bond_LGD;
	int _bond_amount;

	Bond_calculator_interface *bond_calc_ptr;

	int _term;
	double _yield_rate;

public:
	Bond() {};
	~Bond() { free_bond_calculator(); }

	void set_bond_state(SBB_instrument_fields* bond_record, YieldCurve* yc, SBB_bond_ratings* ratings);
	string get_security_id() { return _security_id; }
	string get_bond_id() { return _bond_id; }
	string get_bond_type() { return _bond_type; }
	double get_bond_price() { return _bond_price; }
	double get_bond_dv01() { return _bond_dv01; }
	double get_bond_risk() { return _bond_risk; }
	double get_bond_LGD() { return _bond_LGD; }
	int get_bond_amount() { return _bond_amount; }
	string get_bond_position() {
		if(_bond_amount > 0) {
	        return "long";
	    } else if (_bond_amount < 0) {
	        return "short";
	    } else {
	       return "bond amout equals to zero";
	    }
	}

	int get_term() { return _term; }
	double get_yield_rate() { return _yield_rate; }
	double get_bond_price_shift(double shift);
	void free_bond_calculator() { delete bond_calc_ptr; }
};

#endif