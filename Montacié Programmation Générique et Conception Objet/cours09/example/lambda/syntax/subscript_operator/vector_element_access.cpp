// vector_element_access.cpp
// Program demonstrates overloaded subscript operators.
// Subscript access to the elements of std::vector< std::string > via operator[].

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    std::vector< std::string > vec( 1 ); // vector with 1 element
    lambda< std::vector< std::string > >::scalar_reference
        vec_ref( &vec );
    lambda< std::string >::scalar str( std::string( "ABC" ) );
    (
        vec_ref[ 0 ] = str
        ,
        CTTL_LAMBDA_ASSERT( scalar( std::string( "ABC" ) ) == vec_ref[ 0 ] )
        ,
        CTTL_LAMBDA_ASSERT(
            scalar( std::string( "ABC" ) ) == alias::at( &vec_ref, size_t( 0 ) )
            )
        ,
        vec_ref[ 0 ] = scalar( std::string( "DEF" ) )
        ,
        CTTL_LAMBDA_ASSERT( scalar( std::string( "DEF" ) ) == vec_ref[ 0 ] )
        ,
        CTTL_LAMBDA_ASSERT(
            scalar( std::string( "DEF" ) ) == alias::at( &vec_ref, size_t( 0 ) )
            )

        ).evaluate();

    return 0;
}
