// value_translator_4_stack.cpp
// Program demonstrates value translator for std::stack.

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    lambda< double >::stack dstack;
    (
        ++( dstack^atof^"7.77" ),
        CTTL_LAMBDA_ASSERT( +dstack == 1u ),
        CTTL_LAMBDA_ASSERT( *dstack == scalar( 7.77 ) )
    ).evaluate();

    return 0;
}
