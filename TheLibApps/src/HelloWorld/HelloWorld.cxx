// wrapping of the command line
#include "HelloWorldCLP.h"

// std
#include <iostream>

// main method
int main( int argc, char* argv[] )
{
    // get the input arguments
    PARSE_ARGS;
    // output the string
    std::cout << "inputString: " << inputString << std::endl;
    // return value
    return EXIT_SUCCESS;
}

