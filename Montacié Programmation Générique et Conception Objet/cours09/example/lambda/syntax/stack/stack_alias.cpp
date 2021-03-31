// stack_alias.cpp
// Program illustrates access to std::stack via alias helpers.

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    std::stack< size_t > st;
    lambda< std::stack< size_t > >::scalar_reference stack_ref( &st );

    (
        // Same as
        // assert( st.empty() );
        CTTL_LAMBDA_ASSERT( alias::empty( stack_ref ) ),

        // Same as
        // st.push( size_t( 5 ) );
        alias::push( &stack_ref, size_t( 5 ) ),

        // Same as
        // assert( st.top() == size_t( 5 ) );
        CTTL_LAMBDA_ASSERT( alias::top( stack_ref ) == scalar( 5u ) ),

        // Same as
        // assert( !st.empty() );
        CTTL_LAMBDA_ASSERT( !alias::empty( stack_ref ) ),

        // Same as
        // st.top() == size_t( 6 );
        alias::top( &stack_ref ) = scalar( 6 ),

        // Same as
        // assert( st.top() == size_t( 6 ) );
        CTTL_LAMBDA_ASSERT( alias::top( stack_ref ) == scalar( 6u ) )

    ).evaluate();

    return 0;
}
