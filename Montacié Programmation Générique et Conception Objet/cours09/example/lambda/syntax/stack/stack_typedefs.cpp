// stack_typedefs.cpp
// Program demonstrates usage of a standalone stack primitives
// in lambda expressions.

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

size_t int_2_size_t( int value_ )
{
    return value_;
}

int main(/*int argc, char* argv[]*/)
{
    cttl::lambda< int >::scalar Variable;
    cttl::lambda< size_t >::stack Stack;

    cttl::lambda< int >::scalar_reference VariableRef( &Variable.top() );
    cttl::lambda< size_t >::stack_reference StackRef( Stack.make_reference() );
    (
        VariableRef = 1234,
        StackRef^int_2_size_t = VariableRef,

        CTTL_LAMBDA_ASSERT( Variable == 1234 ),
        CTTL_LAMBDA_ASSERT( *Stack == scalar( 1234u ) ),

        Variable = 5678,
        StackRef^int_2_size_t = Variable, // "type conversion" translator

        CTTL_LAMBDA_ASSERT( VariableRef == 5678 ),
        CTTL_LAMBDA_ASSERT( *StackRef == scalar( 5678u ) )

    ).evaluate();

    return 0;
}
