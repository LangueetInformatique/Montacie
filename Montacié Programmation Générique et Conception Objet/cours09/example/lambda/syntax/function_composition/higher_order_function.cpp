// higher_order_function.cpp
// Program demonstrates higher-order function and composition of functions.

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int F( int x_ )
{
    return x_ * 2;
}

int G( int x_ )
{
    return x_ * 3;
}

int main(/*int argc, char* argv[]*/)
{
    int var = 0;

    (
        scalar( &var )^F^G = 5

    ).evaluate();

    assert( var == 30 );

    return 0;
}
