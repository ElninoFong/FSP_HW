#include "SBB_io.h"
#include <string>
using namespace std;

class Bond
{
private:
	string _security_id;
	string _bond_id;
	string _bond_type;

	double _bond_price;
	double _bond_dv01;
	double _bond_risk;
	int _bond_amount;

	// void cal_bond_price();
	// void cal_bond_risk();
	// void cal_bond_dv01();

public:
	Bond() {};
	~Bond() {};

	void set_bond_state(SBB_instrument_fields* bond_record);
	string get_security_id() { return _security_id; }
	string get_bond_id() { return _bond_id; }
	string get_bond_type() { return _bond_type; }
	double get_bond_price() { return _bond_price; }
	double get_bond_dv01() { return _bond_dv01; }
	double get_bond_risk() { return _bond_risk; }
	double get_bond_amount() { return _bond_amount; };
	string get_bond_position() {
		if(_bond_amount > 0) {
	        return "long";
	    } else if (_bond_amount < 0) {
	        return "short";
	    } else {
	       return "bond amout equals to zero";
	    }
	}
};