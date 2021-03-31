// const_scalar_type.cpp
// Program demonstrates macro const_scalar_type(T),
// which instantiates stand-alone C++ -like constants.
// T is either int, or type, convertible to integer,
// such as enumerated type.

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

enum { zero, one, two };
const_scalar_type( zero ) ZERO;
const_scalar_type( one )  ONE;
const_scalar_type( two )  TWO;
const_scalar_type( 3 )    THREE;
const_scalar_type( -5 )   MINUS_FIVE;

int main(/*int argc, char* argv[]*/)
{
    lambda< int >::stack Stack;    // instantiate std::stack< int >
    (
        //Stack = const_scalar( 2 )^const_scalar( 3 ),
        Stack = TWO^THREE,
        CTTL_LAMBDA_ASSERT( +Stack == scalar( size_t( TWO.const_value_ ) ) ),
        CTTL_LAMBDA_ASSERT( *Stack == THREE ),
        Stack--,
        CTTL_LAMBDA_ASSERT( +Stack == scalar( size_t( ONE.const_value_ ) ) ),
        CTTL_LAMBDA_ASSERT( *Stack == TWO )
    ).evaluate();

    return 0;
}
