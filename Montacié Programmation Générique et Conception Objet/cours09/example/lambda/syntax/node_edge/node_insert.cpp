// node_insert.cpp
// Program demonstrates cttl::node functionality.

#define CTTL_TRACE_EVERYTHING

#include "cttl/cttl.h"
#include "lambda/lambda.h"
#include "utils/itos.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    typedef CTTL_STD_STRING ( *function_T ) ( size_t );

    std::string inp;
    lambda< std::string >::scalar_reference sinp( &inp );

    node<> node1( inp );
    node<> node2 = node1;
    const_edge<> edge12( node1, node2 );

    lambda< node<> >::scalar_reference snode1( &node1 );
    lambda< node<> >::scalar_reference snode2( &node2 );
    lambda< const_edge<> >::scalar_reference sedge12( &edge12 );
    
    (
        CTTL_LAMBDA_ASSERT( scalar( 0u ) == alias::offset( snode1 ) ),

        snode1 -= scalar( std::string( "1" ) ),
        // positions of nodes at insertion point remain unchanged:
        CTTL_LAMBDA_ASSERT( sinp == scalar( std::string( "1" ) ) ),
        CTTL_LAMBDA_ASSERT( scalar( 0u ) == alias::offset( snode1 ) ),
        CTTL_LAMBDA_ASSERT( scalar( 0u ) == alias::offset( snode2 ) ),

        snode1 += scalar( std::string( "2" ) ),
        // positions of all nodes adjusted:
        CTTL_LAMBDA_ASSERT( sinp == scalar( std::string( "21" ) ) ),
        CTTL_LAMBDA_ASSERT( scalar( 1u ) == alias::offset( snode1 ) ),
        CTTL_LAMBDA_ASSERT( scalar( 1u ) == alias::offset( snode2 ) ),

        snode1 -= scalar( std::string( "3" ) ),
        CTTL_LAMBDA_ASSERT( sinp == scalar( std::string( "231" ) ) ),
        CTTL_LAMBDA_ASSERT( scalar( 1u ) == alias::offset( snode1 ) ),
        CTTL_LAMBDA_ASSERT( scalar( 1u ) == alias::offset( snode2 ) ),

        snode1 += scalar( std::string( "4" ) ),
        CTTL_LAMBDA_ASSERT( sinp == scalar( std::string( "2431" ) ) ),
        CTTL_LAMBDA_ASSERT( scalar( 2u ) == alias::offset( snode1 ) ),
        CTTL_LAMBDA_ASSERT( scalar( 2u ) == alias::offset( snode2 ) ),

        // translate node offset:
        ( sinp^function_T( &itos< size_t > ) ) = alias::offset( snode2 ),
        CTTL_LAMBDA_ASSERT( sinp == scalar( std::string( "2" ) ) ),
        snode1 = size_t( 0 ),                    // set node offset
        snode2 = size_t( 1 ),
        CTTL_LAMBDA_ASSERT( snode1 <= snode2 ),  // comapare node offsets

        // edge may be used anywhere in place of std::string:
        scalar( &edge12.first ) = snode1,
        scalar( &edge12.second ) = snode2,
        snode1 += sedge12,
        CTTL_LAMBDA_ASSERT( sinp == scalar( std::string( "22" ) ) )
    ).evaluate();

    assert( inp == "22" );

    return 0;
}
