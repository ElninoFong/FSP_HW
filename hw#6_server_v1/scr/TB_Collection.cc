// TB_Collection.cc

#include <cmath>
#include "TB_Collection.h"
#include "SBB_io.h"
#include "Calculator.h"
#include "SBB_ratings.h"
#include <iostream>
using namespace std;

TB_Collection::TB_Collection(const char* yieldcurve, const char* tradingbook) {
    SBB_bond_ratings ratings;

    _yieldcurve = new YieldCurve(yieldcurve);

    SBB_instrument_input_file file(tradingbook);
    SBB_instrument_fields *fields_array = file.get_records(_collection_size);
    _bond_array = new Bond[_collection_size];
    int largest_long = 0;
    int largest_short = 0;
    double most_risk = 0.0;
    for (int i = 0; i < _collection_size; i++) {
    	_bond_array[i].set_bond_state(&fields_array[i], _yieldcurve, &ratings);

        // set bond risk
        double bond_risk = _bond_array[i].get_bond_risk();
    	_collection_risk += bond_risk;
        if (abs(bond_risk) > abs(most_risk)) {
            most_risk = bond_risk;
            _most_risk_index = i;
        }

        // set bond amount
        int bond_amount = _bond_array[i].get_bond_amount();
    	_collection_amount += bond_amount;
        if (bond_amount > largest_long) {
            largest_long = bond_amount;
            _largest_long_index = i;
        }
        if (bond_amount < largest_short) {
            largest_short = bond_amount;
            _largest_short_index = i;
        }

        // set buckets
        int term = _bond_array[i].get_term();
        if (term > 0 && term <= 2) {
            bucket0_2yr.push_back(i);
        } else if (term > 10) {
            bucket10_30yr.push_back(i);
        }
    }
    file.free_records();
}

TB_Collection::~TB_Collection() {
	free_bond_array();
}

void TB_Collection::print_collection_position() {
	cout << "Total Position: ";
	if(_collection_amount > 0) {
        cout << "long";
    } else if (_collection_amount < 0) {
        cout << "short";
    } else {
        cout << "flat";
    }
    cout << " (" << _collection_amount << ")";
}

int TB_Collection::get_collection_size() {
	return _collection_size;
}

double TB_Collection::get_collection_risk() {
    return _collection_risk;
}

Bond* TB_Collection::get_bond_array() {
	return _bond_array;
}

int TB_Collection::get_largest_long_index() {
    return _largest_long_index;
}

int TB_Collection::get_largest_short_index() {
    return _largest_short_index;
}

int TB_Collection::get_most_risk_index() {
    return _most_risk_index;
}

void TB_Collection::free_bond_array() {
	delete[] _bond_array;
}

void TB_Collection::show() {
    for (int i = 0; i < _collection_size; i++)
    {
        cout << _bond_array[i].get_security_id() << " (" << _bond_array[i].get_bond_type() << ")" << endl;
        cout << "Bond ID:     " << _bond_array[i].get_bond_id() << endl;;
        cout << "Bond Price:  " << _bond_array[i].get_bond_price() << endl;
        cout << "DV01:        " << _bond_array[i].get_bond_dv01() << endl;
        cout << "LGD:         " << _bond_array[i].get_bond_LGD() << endl;
        cout << "Risk Amount: " << _bond_array[i].get_bond_risk() << "\n" << endl;
    }
    
    cout << "==============" << endl;
    cout << "Total Risk:     " << _collection_risk << endl;
    print_collection_position();

    // cout<< endl << _most_risk_index << " " << _largest_long_index << " " << _largest_short_index << endl;
}

double TB_Collection::get_2yr_hedge_risk() {
    double bucket_risk = 0.0;
    for (int i=0; i<bucket10_30yr.size(); i++) {
        bucket_risk += _bond_array[bucket10_30yr[i]].get_bond_risk();
    }
    return bucket_risk / _yieldcurve->cal_2yr_dv01();
}

double TB_Collection::get_total_market_value(double shift) {
    double total_market_value = 0.0;
    for (int i=0; i<_collection_size; i++) {
        total_market_value += _bond_array[i].get_bond_price_shift(shift) * _bond_array[i].get_bond_amount();
    }
    return total_market_value / 100;
}