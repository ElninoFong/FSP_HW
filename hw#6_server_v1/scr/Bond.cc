#include "SBB_date.h"
#include "Bond.h"
#include "Calculator.h"
#include "YieldCurve.h"
#include <string>
using namespace std;

void Bond::set_bond_state(SBB_instrument_fields* bond_record, YieldCurve* yc, SBB_bond_ratings* ratings) {
	SBB_date from_dt;
    from_dt.set_from_yyyymmdd(bond_record->SettlementDate);
    SBB_date to_dt;
    to_dt.set_from_yyyymmdd(bond_record->MaturityDate);
    int semiannual_period_count = SBB_periods::get_number_of_periods_semiannual(from_dt, to_dt);
    _term = semiannual_period_count >> 1;

    short frequency = bond_record->Frequency;
    int periodes;
    if (frequency == 2) {
        periodes = semiannual_period_count;
    } else {
        periodes = (semiannual_period_count * frequency) >> 1;
    }

    string securityID(bond_record->SecurityID);
    _security_id = securityID;
    char* tmp = new char[60];
    sprintf(tmp, "%s_%.1f_%ld",bond_record->Ticker, bond_record->CouponRate, to_dt.get_yyyymmdd());
    string id(tmp);
    _bond_id = id;

    // "YIELD" or "SPREAD"
    double yield_rate;
    if (strcmp(bond_record->RateType, RATETYPE_YIELD)==0)
    {
        yield_rate = bond_record->Rate;
    } else {
        yield_rate = bond_record->Rate/100 + yc->cal_yield_rate(_term);
        // printf("yield_rate: %f\n", yield_rate);
    }
    if (bond_record->CouponRate == 0)
    {
    	_bond_type = "zero coupon bond";
    	bond_calc_ptr = new Zero_coupon_calculator(frequency, yield_rate, periodes);
    } else {
    	_bond_type = "coupon bearing bond";
        bond_calc_ptr = new Coupon_bearing_calculator(frequency, bond_record->CouponRate, yield_rate, periodes);
    }

    // cal LGD
    _bond_LGD = ratings->LGD_given_SnP_Fitch(bond_record->Quality) * bond_record->Amount;
    
    _bond_amount = bond_record->Amount;
    _bond_price = bond_calc_ptr->cal_bond_price();
	_bond_dv01 = bond_calc_ptr->cal_bond_dv01();
	_bond_risk = _bond_dv01 * _bond_amount / 100;

    _yield_rate = yield_rate;
}

double Bond::get_bond_price_shift(double shift) {
    return bond_calc_ptr->cal_bond_price_shift(shift);
}
