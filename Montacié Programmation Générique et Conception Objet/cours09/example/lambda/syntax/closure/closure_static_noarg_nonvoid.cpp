// closure_static_noarg_nonvoid.cpp
// Program demonstrates calling non-void function with no arguments.

#include "cttl/cttl.h"
#include "lambda/lambda.h"

int const& free_f()
{
    static const int value = 1;
    return value;
}

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    lambda< int >::scalar sint;
    (
        sint = *scalar(
            CTTL_STATIC_ACTION_NOARG(
                int const&,
                &free_f
            )
        ),
        CTTL_LAMBDA_ASSERT( sint == 1 )
    ).evaluate();

    return 0;
}
