// sample code: xyz.cpp
#include "cttl/cttl.h"

using namespace cttl;

int main()
{
    std::string inp = "ABCzxyzzz";
    // char positions: 0123456789
    const_edge<> substring( inp );

    // Evaluation algorithm is find(),
    // applied to the grammar expression first( "xyz" )
    size_t result = first( "xyz" ).find( substring );

    // Verify that upper bound position of the
    // first character of "xyz" class has been found:
    assert( result == 3 );
    return 0;
}
