// vector_iterator.cpp
// Program demonstrates:
// - vector iterator,
// - navigation via prefix and postfix increment/decrement.

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    std::vector< int > vec( 3, 33 );     // vec: 33,33,33
    std::vector< int >::iterator it = vec.begin();
    std::vector< int >::iterator it2 = vec.end();

    lambda< std::vector< int > >::scalar_reference svec( &vec );
    lambda< std::vector< int >::iterator >::scalar_reference sit( &it );
    lambda< std::vector< int >::iterator >::scalar_reference sit2( &it2 );

    (
        CTTL_LAMBDA_ASSERT( sit != sit2 ),
        sit = sit + 3,
        CTTL_LAMBDA_ASSERT( sit == sit2 ),
        sit = alias::begin( &svec ),
        *sit,
        CTTL_LAMBDA_ASSERT( *sit == 33 ),
        *sit++ = 34,
        CTTL_LAMBDA_ASSERT( *sit == 33 ),
        CTTL_LAMBDA_ASSERT( *--sit == 34 )
    ).evaluate();

    assert( it != it2 );
    assert( it == vec.begin() );

    return 0;
}
