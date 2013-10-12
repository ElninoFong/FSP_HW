// Calculator.h

class Calculator {
private:
    double _C;  // Coupon
    double _M;  // Maturity
    double _i;  // Prevailing interest rate
    int _n;  // Number of periodes
    
public:
    // Constructor
    Calculator(double C, double M, double i, int n);
    
    double bondPriceCalc();
    double bondPriceCalc(double C, double M, double i, int n);
    
};