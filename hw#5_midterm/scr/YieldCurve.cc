// YieldCurve.cc
#include "SBB_date.h"
#include "YieldCurve.h"
#include <math.h>
#include <limits.h>

void Yield::set_yield_state(SBB_instrument_fields* yield_record) {
	SBB_date from_dt;
    from_dt.set_from_yyyymmdd(yield_record->SettlementDate);
    SBB_date to_dt;
    to_dt.set_from_yyyymmdd(yield_record->MaturityDate);
    _yield_term = SBB_periods::get_number_of_periods_annual(from_dt, to_dt);
    _yield_rate = yield_record->Rate;
}

YieldCurve::YieldCurve(const char* yieldcurve) {
	SBB_instrument_input_file file(yieldcurve);
    SBB_instrument_fields *fields_array = file.get_records(_yc_size);
    _yc_array = new Yield[_yc_size];
    for (int i = 0; i < _yc_size; i++) {
    	_yc_array[i].set_yield_state(&fields_array[i]);
    }
    file.free_records();
}

double YieldCurve::cal_yield_rate(int term) {
	double rate = 0.0;
	int min_distance = INT_MAX;
	int less_term = INT_MAX;
	for (int i = 0; i < _yc_size; i++)
	{
		int comp_term = _yc_array[i].get_yield_term();
		int distance = abs(comp_term - term);
		if (min_distance > distance)
		{
			min_distance = distance;
			less_term = comp_term;
			rate = _yc_array[i].get_yield_rate();
		} else if (min_distance == distance) {
			if (less_term > comp_term) {
				less_term = comp_term;
				rate = _yc_array[i].get_yield_rate();
			}
		}
	}
	return rate;
}