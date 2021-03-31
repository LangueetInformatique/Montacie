// scalar_reference_primitive.cpp
// Program demonstrates usage of instance- and
// reference-scalar primitives.

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    int var = 0;

    // refvar stores reference to var:
    lambda< int >::scalar_reference refvar( &var );

    // svar makes copy of var:
    lambda< int >::scalar svar( var );

    (
        refvar = 6,
        svar = 5
    ).evaluate();

    assert( var == 6 );
    assert( svar.top() == 5 );

    return 0;
}
