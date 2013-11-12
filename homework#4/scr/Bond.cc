#include "SBB_date.h"
#include "Bond.h"
#include "Calculator.h"
#include "YieldCurve.h"
#include <string>
using namespace std;

void Bond::set_bond_state(SBB_instrument_fields* bond_record, YieldCurve* yc) {
	SBB_date from_dt;
    from_dt.set_from_yyyymmdd(bond_record->SettlementDate);
    SBB_date to_dt;
    to_dt.set_from_yyyymmdd(bond_record->MaturityDate);
    int semiannual_period_count = SBB_periods::get_number_of_periods_semiannual(from_dt, to_dt);
    
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
        yield_rate = bond_record->Rate/100 + yc->cal_yield_rate(periodes);
        // printf("yield_rate: %f\n", yield_rate);
    }
    Bond_calculator_interface* bond_calc_ptr;
    if (bond_record->CouponRate == 0)
    {
    	_bond_type = "zero coupon bond";
    	Zero_coupon_calculator zero(frequency, yield_rate, periodes);
    	bond_calc_ptr = &zero;
    } else {
    	_bond_type = "coupon bearing bond";

    	Coupon_bearing_calculator bearing(frequency, bond_record->CouponRate, yield_rate, periodes);
    	bond_calc_ptr = &bearing;
    }

    _bond_amount = bond_record->Amount;
    _bond_price = bond_calc_ptr->cal_bond_price();
	_bond_dv01 = bond_calc_ptr->cal_bond_dv01();
	_bond_risk = _bond_dv01 * _bond_amount / 100;
}


