// TB_Collection.cc

// #include <math.h>
#include "TB_Collection.h"
// #include "SBB_io.h"
// #include "Calculator.h"
#include <iostream>
using namespace std;

TB_Collection::TB_Collection(const char* tradingbook) {
    SBB_instrument_input_file file(tradingbook);
    SBB_instrument_fields *fields_array = file.get_records(_collection_size);
    _bond_array = new Bond[_collection_size];
    for (int i = 0; i < _collection_size; i++) {
    	_bond_array[i].set_bond_state(&fields_array[i]);
    	_collection_risk += _bond_array[i].get_bond_risk();
    	_collection_amount += _bond_array[i].get_bond_amount();
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

void TB_Collection::free_bond_array() {
	delete[] _bond_array;
}