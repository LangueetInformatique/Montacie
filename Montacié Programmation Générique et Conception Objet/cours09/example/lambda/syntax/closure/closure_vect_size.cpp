// closure_vect_size.cpp
// The program extracts the length of the vector and
// stores it in the variable named length.

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    std::vector< int > vect( 5 );
    std::vector< int >::size_type length;
    (
        scalar( &length ) = *scalar( action(
            &vect,
            std::mem_fun( &std::vector< int >::size )
        ))
    ).evaluate();

    assert( length == 5 );

    return 0;
}
