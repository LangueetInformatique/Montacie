// closure_static_noarg.cpp
// Program demonstrates calling void function with no arguments.

#include "cttl/cttl.h"
#include "lambda/lambda.h"

void free_f()
{
}

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    (
        *scalar(
            CTTL_STATIC_ACTION_NOARG(
                void,
                &free_f
            )
        )
    ).evaluate();

    return 0;
}
