// edge_erase.cpp
// Program demonstrates substring erase
// by using alias::edge::erase() helper.

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    std::string inp( "XYZABC" );
    edge<> edge_target( inp, 3, inp.length() );
    lambda< edge<> >::scalar target( &edge_target );
    (
        CTTL_LAMBDA_ASSERT(
            alias::text( target ) == scalar( std::string( "ABC" ) )
            ),
        alias::edge::erase( &target ),
        CTTL_LAMBDA_ASSERT(
            alias::length( target ) == scalar( 0u )
            )
    ).evaluate();

    assert( inp == "XYZ" );
    return 0;
}
