// TB_Collection.h
#ifndef SYF_TB_COLLECTION__H
#define SYF_TB_COLLECTION__H

#include "Bond.h"
#include "YieldCurve.h"

class TB_Collection {
private:
    YieldCurve* _yieldcurve;
    Bond *_bond_array;
    int _collection_size; // total number of bonds
    double _collection_risk;
    int _collection_amount;

    int _largest_long_index;
    int _largest_short_index;
    int _most_risk_index;

    TB_Collection();

public:
    // Constructor
    TB_Collection(const char* yieldcurve, const char* tradingbook);
    ~TB_Collection();

    int get_collection_size();
    void print_collection_position();
    double get_collection_risk();
    Bond* get_bond_array();
    int get_largest_long_index();
    int get_largest_short_index();
    int get_most_risk_index();
    void show();
    void free_bond_array();
};

#endif