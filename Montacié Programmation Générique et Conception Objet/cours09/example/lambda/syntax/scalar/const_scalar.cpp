// const_scalar.cpp
// Program demonstrates helper macro const_scalar(T), which
// yields in-line C++ -like constants.
// T is either an integer constant, or a type, convertible
// to integer constant, such as enumerated constant.

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    lambda< int >::stack Stack;    // instantiate std::stack< int >
    (
        Stack = const_scalar( 2 )^const_scalar( 3 ),
        CTTL_LAMBDA_ASSERT( +Stack == 2u ),
        CTTL_LAMBDA_ASSERT( *Stack == 3 ),
        Stack--,
        CTTL_LAMBDA_ASSERT( +Stack == 1u ),
        CTTL_LAMBDA_ASSERT( *Stack == 2 )
    ).evaluate();

    return 0;
}
