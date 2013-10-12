// TB_Collection.h

#include "Bond.h"

class TB_Collection {
private:
    Bond *_bond_array;
    int _collection_size; // total number of bonds
    double _collection_risk;
    double _collection_amount;

    TB_Collection();
    // void cal_collection_risk();

public:
    // Constructor
    TB_Collection(const char* tradingbook);
    ~TB_Collection();

    int get_collection_size();
    void print_collection_position();
    double get_collection_risk();
    Bond* get_bond_array();

    void free_bond_array();
};