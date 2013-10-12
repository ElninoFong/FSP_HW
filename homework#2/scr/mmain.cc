#ifndef EXAMPLE_CALL
#define EXAMPLE_CALL
#include "SBB_date.h"
#endif
#include "SBB_io.h"
#include "SBB_util.h"
#include "Calculator.h"
#include <math.h>

int main(int argc, char* argv[]) {
    SBB_util sbb;
    sbb.start_clock();
    double Maturity = 100;
    const char* filename = argv[1];
    SBB_instrument_input_file file(filename);
    int length = 0;
    SBB_instrument_fields *fields_array = file.get_records(length);
    for (int i = 0; i < length; i++) {
        SBB_date from_dt;
        from_dt.set_from_yyyymmdd(fields_array[i].SettlementDate);
        SBB_date to_dt;
        to_dt.set_from_yyyymmdd(fields_array[i].MaturityDate);
        int semiannual_period_count = get_number_of_periods_semiannual(from_dt, to_dt);
        
        short frequency = fields_array[i].Frequency;
        double Coupon = (fields_array[i].CouponRate) / frequency;
        double yield = fields_array[i].YieldRate * 0.01 / frequency;
        double dv_i_up = (fields_array[i].YieldRate * 0.01 + 0.0001) / frequency;
        double dv_i_down = (fields_array[i].YieldRate * 0.01 - 0.0001) / frequency;
        int n;
        if (frequency == 2) {
            n = semiannual_period_count;
        } else {
            n = (semiannual_period_count * frequency) >> 1;
        }
        
        Calculator pv(Coupon, Maturity, yield, n);
        double price = pv.bondPriceCalc();
        double dv01_up = pv.bondPriceCalc(Coupon, Maturity, dv_i_up, n);
        double dv01_down = pv.bondPriceCalc(Coupon, Maturity, dv_i_down, n);
        double dv01 = (pv.bondPriceCalc(Coupon, Maturity, dv_i_down, n) - pv.bondPriceCalc(Coupon, Maturity, dv_i_up, n)) / 2;
        std::cout.precision(7);
        std::cout << price << " " << dv01 << std::endl;
//        std::cout << "up: " << dv01_up << ", down: " << dv01_down << std::endl;
    }
    sbb.end_clock();
    return 0;
}