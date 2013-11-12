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
    double _collection_amount;

    TB_Collection();

public:
    // Constructor
    TB_Collection(const char* yieldcurve, const char* tradingbook);
    ~TB_Collection();

    int get_collection_size();
    void print_collection_position();
    double get_collection_risk();
    Bond* get_bond_array();

    void free_bond_array();
};

#endif