//PV.cc

#include <iostream>
#include <math.h>
#include "SBB_util.h"

using namespace std;

class PV {
private:
    double _C;  // Coupon
    double _M;  // Maturity
    double _i;  // Prevailing interest rate
    double _n;  // Number of periodes
    
public:
    PV(double C, double M, double i, double n);
    
    double bondPriceCalc();
};

PV::PV(double C, double M, double i, double n)
{
    _C = C;
    _M = M;
    _i = i;
    _n = n;
}

double PV::bondPriceCalc()
{
    return (_C * (1 - 1 / pow((1+_i), _n)) / _i) + (_M / pow((1+_i), _n));
}

int main()
{
    SBB_util sbb;
    sbb.start_clock();
    double C, M, i, n;
    cout << "Coupon: ";
    cin >> C;
    cout << "Maturity: ";
    cin >> M;
    cout << "Interest Rate: ";
    cin >> i;
    cout << "Periodes: ";
    cin >> n;
    if (C <= 0 || M <= 0 || i <= 0 || n <= 0) {
        cerr << endl << "Invalid input!" << endl;
        sbb.end_clock();
        return -1;
    }
//    PV pv(8000, 100000, 0.1, 10);
    PV pv(C, M, i, n);  
    cout << endl << "Bond Price: " << pv.bondPriceCalc() << endl;
    sbb.end_clock();
    return  0;
}