#include "SBB_util.h"
#include "TB_Collection.h"
#include "YieldCurve.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    SBB_util sbb;
    sbb.start_clock();
    const char* yieldcurve_file = argv[1];
    const char* tradingbook_file = argv[2];

    TB_Collection* collection = new TB_Collection(yieldcurve_file, tradingbook_file);
    cout.precision(9);
    Bond* bond_array = collection->get_bond_array();
    for (int i = 0; i < collection->get_collection_size(); i++)
    {
        cout << bond_array[i].get_security_id() << " (" << bond_array[i].get_bond_type() << ")" << endl;
        cout << "Bond ID:     " << bond_array[i].get_bond_id() << endl;;
        cout << "Bond Price:  " << bond_array[i].get_bond_price() << endl;
        cout << "DV01:        " << bond_array[i].get_bond_dv01() << endl;
        cout << "Risk Amount: " << bond_array[i].get_bond_risk() << "\n" << endl;
    }
    
    cout << "==============" << endl;
    cout << "Total Risk:     " << collection->get_collection_risk() << endl;
    collection->print_collection_position();

    sbb.end_clock();
    return 0;
}