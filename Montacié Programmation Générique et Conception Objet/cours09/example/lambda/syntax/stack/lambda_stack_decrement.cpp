// lambda_stack_decrement.cpp
// Program demonstrates usage of overloaded prefix and
// postfix decrement operators for lambda stack primitive.

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    lambda< int >::scalar Variable;// instantiate integer scalar
    lambda< int >::stack Stack;    // instantiate std::stack< int >
    (
        Stack = const_scalar( 2 )^3^4^5,
        //<top>5,4,3,2<bottom>
        CTTL_LAMBDA_ASSERT( +Stack == scalar( 4u ) ),
        CTTL_LAMBDA_ASSERT( *Stack == 5 ),
        Variable = *Stack--,
        //<top>4,3,2<bottom>
        CTTL_LAMBDA_ASSERT( Variable == 5 ),
        CTTL_LAMBDA_ASSERT( +Stack == scalar( 3u ) ),
        CTTL_LAMBDA_ASSERT( *Stack == 4 ),
        Variable = *--Stack,
        //<top>3,2<bottom>
        CTTL_LAMBDA_ASSERT( Variable == 3 ),
        CTTL_LAMBDA_ASSERT( +Stack == scalar( 2u ) ),
        CTTL_LAMBDA_ASSERT( *Stack == 3 ),
        *--Stack = 7, // pop, then assign new value to top element
        CTTL_LAMBDA_ASSERT( +Stack == scalar( 1u ) ),
        CTTL_LAMBDA_ASSERT( *Stack == 7 ),
        //<top>7<bottom>
        // first, the top of stack gets assigned new
        // value of 6, then it is thrown away by postfix decrement:
        *Stack-- = 6,
        //<top><bottom>
        CTTL_LAMBDA_ASSERT( +Stack == scalar( 0u ) )
    ).evaluate();

    return 0;
}
