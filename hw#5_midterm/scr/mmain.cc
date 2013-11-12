#include "SBB_util.h"
#include "TB_Collection.h"
#include <stdio.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    SBB_util sbb;
    sbb.start_clock();
    const char* tradingbook_file = argv[1];
    const char* yieldcurve_file = argv[2];
    const char* results_file = argv[3];
    const char* temp_file = "./data/temp.txt";

    TB_Collection* collection = new TB_Collection(yieldcurve_file, tradingbook_file);
    // cout.precision(9);
    // collection->show();
    Bond* bond_array = collection->get_bond_array();

    FILE* tb_File = fopen (tradingbook_file, "r");
    if (!tb_File){
        fprintf(stderr,"ERROR couldn't open: %s\n", tradingbook_file);
        throw std::runtime_error("file open failure");
    }
    FILE* temp_File = fopen (temp_file, "w");
    if (!temp_File){
        fprintf(stderr,"ERROR couldn't open: %s\n", temp_file);
        throw std::runtime_error("file open failure");
    }

    char _line_buf[SBB_LINE_BUFFER_LENGTH];
    _line_buf[0]=' ';
    int count = 0;
    while(fgets(_line_buf, SBB_LINE_BUFFER_LENGTH, tb_File)) {

        if('#' == _line_buf[0]) { 
            fprintf(temp_File,_line_buf);
            continue;
        }
        
        fwrite(_line_buf, strlen(_line_buf)-1, 1, temp_File);
        fprintf(temp_File," %.3f %.3f %.3f %.3f\n", bond_array[count].get_bond_price(),
                                                    bond_array[count].get_bond_dv01(),
                                                    bond_array[count].get_bond_risk(),
                                                    bond_array[count].get_bond_LGD());
        count++;
    }
    
    FILE* res_File = fopen (results_file,"w");
    if (!res_File){
        fprintf(stderr,"ERROR couldn't open: %s\n", results_file);
        throw std::runtime_error("file open failure");
    }
    fprintf (res_File, "%s %d\n%s %d\n%s %.3f\n%.3f\n", bond_array[collection->get_largest_long_index()].get_security_id().c_str(),
                                                        bond_array[collection->get_largest_long_index()].get_bond_amount(),
                                                        bond_array[collection->get_largest_short_index()].get_security_id().c_str(),
                                                        bond_array[collection->get_largest_short_index()].get_bond_amount(),
                                                        bond_array[collection->get_most_risk_index()].get_security_id().c_str(),
                                                        bond_array[collection->get_most_risk_index()].get_bond_risk(),
                                                        collection->get_collection_risk());

    if (fclose(tb_File)) {
        fprintf(stderr,"flose failed on file %s errno: %d\n", tb_File, errno);
    }
    if (fclose(temp_File)) {
        fprintf(stderr,"flose failed on file %s errno: %d\n", temp_File, errno);
    }
    if (fclose(res_File)) {
        fprintf(stderr,"flose failed on file %s errno: %d\n", res_File, errno);
    }

    if(remove(tradingbook_file) == -1) {
        fprintf(stderr,"ERROR couldn't delete %s\n",tradingbook_file);
    } else {
        rename(temp_file ,tradingbook_file); 
    }

    sbb.end_clock();
    return 0;
}