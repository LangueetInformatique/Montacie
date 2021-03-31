// scalar_types_mix.cpp
// Program demonstrates usage of miscellaneous scalar types
// in lambda expressions.

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    cttl::lambda< int >::scalar Variable;
    cttl::lambda< std::vector< int > >::scalar Vector;

    cttl::lambda< int >::scalar_reference VariableRef( &Variable.top() );
    cttl::lambda< std::vector< int > >::scalar_reference VectorRef( &Vector.top() );
    (
        VariableRef = 1234,
        alias::push_back( &VectorRef, VariableRef.top() ),

        CTTL_LAMBDA_ASSERT( Variable == 1234 ),
        CTTL_LAMBDA_ASSERT( alias::back( Vector ) == 1234 ),

        Variable = 5678,
        alias::push_back( &Vector, Variable.top() ),

        CTTL_LAMBDA_ASSERT( VariableRef == 5678 ),
        CTTL_LAMBDA_ASSERT( alias::back( VectorRef ) == 5678 )

    ).evaluate();

    return 0;
}
