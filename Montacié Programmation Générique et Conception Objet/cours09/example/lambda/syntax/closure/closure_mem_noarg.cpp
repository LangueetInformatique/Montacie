// closure_mem_noarg.cpp
// Program demonstrates calling member function with no arguments.

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    int var = 0;
    std::vector< int > vect( 3 );
    
    (
        scalar( &var ) =
            *scalar( CTTL_MEMBER_ACTION_NOARG(
                vect,
                std::mem_fun( &std::vector< int >::size )
            ))
    ).evaluate();

    assert( var == 3 );

    return 0;
}
