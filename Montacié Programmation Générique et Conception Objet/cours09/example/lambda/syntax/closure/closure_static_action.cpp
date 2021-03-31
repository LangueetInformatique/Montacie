// closure_static_action.cpp
// Program demonstrates calling void function with one argument.

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

// function with mutable argument
void fm( int& arg_ )
{
    ++arg_;
}

// function with constant argument
void fc( int arg_ )
{
    std::cout
        << arg_
        << std::endl
        ;
}

int main(/*int argc, char* argv[]*/)
{
    // construct and initialize scalar:
    lambda< int >::scalar sint( 28 );

    (
        *scalar(
            CTTL_STATIC_ACTION(
                std::ptr_fun( &fm ),
                &sint.top()
            )
        )
    ).evaluate();

    assert( sint.top() == 29 );

    (
        *scalar(
            CTTL_STATIC_ACTION(
                std::ptr_fun( &fc ),
                sint.top()
            )
        )
    ).evaluate();

    return 0;
}
