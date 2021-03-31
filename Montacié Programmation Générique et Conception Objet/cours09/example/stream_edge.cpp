// stream_edge.cpp
// Program demonstrates usage of stream I/O with cttl substrings.

//#define NDEBUG    // define before assert.h to stop assertions from being compiled 
//#define CTTL_TRACE_EVERYTHING

#include <iostream>
#include <sstream> 

#include "cttl/cttl.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    std::stringstream  buffer;
    buffer << "ABC 123";

    std::string inp;
    edge<> substring( inp );
    buffer >> substring;

    assert( inp == "ABC" );
    assert( substring.first.offset() == 0 );
    assert( substring.second.offset() == inp.length() );

    std::cout
        << '\''
        << substring
        << '\''
        << std::endl
        ;

    return 0;
}
