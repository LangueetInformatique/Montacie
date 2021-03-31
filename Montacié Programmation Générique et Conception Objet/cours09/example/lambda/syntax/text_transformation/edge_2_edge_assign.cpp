// edge_2_edge_assign.cpp
// Program demonstrates std::string to cttl::edge assignment
// and alias::text() helper usage.

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    std::string inp( "XYZABC" );
    const_edge<> edge_source( inp, 3, inp.length() );
    edge<> edge_target( edge_source.first, edge_source.second, 0, 3 );

    lambda< const_edge<> >::scalar_reference source( &edge_source );
    lambda< edge<> >::scalar target( &edge_target );
    (
        CTTL_LAMBDA_ASSERT(
            alias::text( target ) == scalar( std::string( "XYZ" ) )
            ),
        target = alias::text( source ),
        CTTL_LAMBDA_ASSERT(
            alias::text( target ) == scalar( std::string( "ABC" ) )
            )
    ).evaluate();

    assert( inp == "ABCABC" );
    return 0;
}
