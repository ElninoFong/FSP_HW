#include <iostream>
#include "SBB_util.h"

int main() 
{
    SBB_util sbb;
    sbb.start_clock();
	std::cout << "Hello world." << std::endl;
    sbb.end_clock();
	return 0;
}
