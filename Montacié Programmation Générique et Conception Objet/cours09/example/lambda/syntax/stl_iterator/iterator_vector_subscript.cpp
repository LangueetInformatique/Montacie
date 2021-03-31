// iterator_vector_subscript.cpp
// Program demonstrates:
// - STL iterator access
// - std::vector
// - overloaded subscript operator

#define CTTL_TRACE_RULES   // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    // create vector with three elements: ( 33, 33, 33 )
    std::vector< int > vec( 3, 33 );
    std::vector< int >::iterator it;

    // create integer scalar:
    lambda< int >::scalar sint;

    // create vector scalar:
    lambda< std::vector< int > >::scalar_reference svec( &vec );

    // create iterator scalar:
    lambda< std::vector< int >::iterator >::scalar_reference sit( &it );

    (
        sit = alias::begin ( &svec ),
        CTTL_LAMBDA_ASSERT( *sit == scalar( 33 ) ),
        *sit = scalar( 34 ),
        CTTL_LAMBDA_ASSERT( *sit == scalar( 34 ) ),
        CTTL_LAMBDA_ASSERT( svec[ const_scalar( 0 ) ] == scalar( 34 ) )
    ).evaluate();

    return 0;
}
