#ifndef SYF_YIELDCURVE__H
#define SYF_YIELDCURVE__H

#include "SBB_io.h"

class Yield {
private:
	int _yield_term;
	double _yield_rate;

public:
	Yield() {};
	~Yield() {};

	void set_yield_state(SBB_instrument_fields* yield_record);
	int get_yield_term() { return _yield_term; }
	double get_yield_rate() { return _yield_rate; }
	void show() {
		printf("Term: %d, Yield: %.1f\n", _yield_term, _yield_rate);
	}
};

class YieldCurve {
private:
    Yield* _yc_array;
    int _yc_size;

    YieldCurve();

public:
    YieldCurve(const char* yieldcurve);
    ~YieldCurve() {
    	delete[] _yc_array;
    };

    int get_yc_size() { return _yc_size; }
    Yield* get_yc_array() { return _yc_array; }
	double cal_yield_rate(int term);
};

#endif
