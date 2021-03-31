// node_insert_substring.cpp
// Program demonstrates substrings inserted at the
// specified cttl::node positions.

#define CTTL_TRACE_EVERYTHING

#include "cttl/cttl.h"
#include "lambda/lambda.h"
#include "utils/itos.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    typedef CTTL_STD_STRING ( *function_T ) ( size_t );

    std::string inp = "ABC";
    lambda< std::string >::scalar_reference sinp( &inp );

    node<> node1( inp );
    node<> node2 = node1;
    edge<> edge12( node1, node2, 0, 2 );

    lambda< node<> >::scalar_reference snode1( &node1 );
    lambda< node<> >::scalar_reference snode2( &node2 );
    lambda< edge<> >::scalar_reference sedge12( &edge12 );
    
    (   CTTL_LAMBDA_ASSERT( scalar( 3u ) == alias::offset( snode1 ) )
        ).evaluate();

    (   CTTL_LAMBDA_ASSERT( alias::text( sedge12 ) == scalar( std::string( "AB" ) ) )
        ).evaluate();

    (   alias::edge::insert_stay( &sedge12, &node1 )
        ).evaluate();

    // positions of nodes at insertion point remain unchanged:
    (   CTTL_LAMBDA_ASSERT( sinp == scalar( std::string( "ABCAB" ) ) )
        ).evaluate();

    (   CTTL_LAMBDA_ASSERT( scalar( 3u ) == alias::offset( snode1 ) )
        ).evaluate();

    (   CTTL_LAMBDA_ASSERT( scalar( 3u ) == alias::offset( snode2 ) )
        ).evaluate();

    (   CTTL_LAMBDA_ASSERT( alias::text( sedge12 ) == scalar( std::string( "AB" ) ) )
        ).evaluate();


    (   alias::edge::insert_go( &sedge12, &node1 )
        ).evaluate();

    // node positions adjusted:
    (   CTTL_LAMBDA_ASSERT( sinp == scalar( std::string( "ABCABAB" ) ) )
        ).evaluate();

    (   CTTL_LAMBDA_ASSERT( scalar( 5u ) == alias::offset( snode1 ) )
        ).evaluate();

    (   CTTL_LAMBDA_ASSERT( scalar( 5u ) == alias::offset( snode2 ) )
        ).evaluate();

    (   CTTL_LAMBDA_ASSERT( alias::text( sedge12 ) == scalar( std::string( "AB" ) ) )
        ).evaluate();

    assert( inp == "ABCABAB" );

    return 0;
}
