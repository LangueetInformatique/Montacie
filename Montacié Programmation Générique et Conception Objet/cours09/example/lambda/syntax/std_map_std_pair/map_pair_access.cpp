// map_pair_access.cpp
// Program demonstrates lambda access to std::map and std::pair.

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    //map
    lambda< std::map< int, int > >::scalar
        hmap;

    lambda< std::map< int, int >::iterator >::scalar
        hm_iter;

    lambda< std::pair< const int, int > >::scalar 
        int_pair( std::make_pair( 10, 20 ) );

    lambda< std::pair< std::map< int, int >::iterator, bool > >::scalar
        hm_insert_result;

    lambda< std::pair<
        std::map< int, int >::const_iterator,
        std::map< int, int >::const_iterator >
    >::scalar
        hm_range_result;

    (
        hm_insert_result = alias::insert( &hmap, int_pair.top() )
        ,
        CTTL_LAMBDA_ASSERT(
            scalar( &hm_insert_result.top().second ) == scalar( true )
            )
        ,
        hm_insert_result = alias::insert( &hmap, int_pair.top() )
        ,
        CTTL_LAMBDA_ASSERT(
            scalar( &hm_insert_result.top().second ) == scalar( false )
            )
        ,
        scalar( &int_pair.top().second ) == 40
        ,
        hm_insert_result =
            alias::insert( &hmap, std::pair< const int, int >( 30, 40 ) )
        ,
        CTTL_LAMBDA_ASSERT(
            scalar( &hm_insert_result.top().second ) == scalar( true )
            )
        ,
        hm_range_result = alias::equal_range( hmap, 30 )
        ,
        CTTL_LAMBDA_ASSERT(
            scalar( &hm_range_result.top().first )
            !=
            scalar( &hm_range_result.top().second )
            )

        ).evaluate();

    return 0;
}
