// set_pair_access.cpp
// Program demonstrates lambda access to std::set and std::pair.

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    // set
    lambda< std::set< char > >::scalar char_set;
    lambda< std::pair< std::set< char >::iterator, bool > >::scalar char_set_insert_result;
    (
        char_set_insert_result = alias::insert( &char_set, 'A' )
        ,
        CTTL_LAMBDA_ASSERT( scalar( &char_set_insert_result.top().second ) == scalar( true ) )
        ,
        char_set_insert_result = alias::insert( &char_set, 'A' )
        ,
        CTTL_LAMBDA_ASSERT( scalar( &char_set_insert_result.top().second ) == scalar( false ) )

        ).evaluate();

    lambda< std::set< char >::iterator >::scalar char_set_iterator;
    lambda< std::set< char >::const_iterator >::scalar char_set_const_iterator;
    (
        char_set_const_iterator = alias::find( &char_set, 'A' )
        ,
        char_set_const_iterator = alias::find( char_set, 'A' )
        ,
        CTTL_LAMBDA_ASSERT( char_set_const_iterator == alias::begin( char_set ) )
        ,
#if ( !defined( _MSC_VER ) ) // MSVC 8.0 defines _MSC_VER as 1400
        char_set_iterator = alias::find( char_set, 'A' ) // MS VC fails to compile
        ,
        CTTL_LAMBDA_ASSERT( char_set_iterator == alias::begin( char_set ) )
        ,
#endif // _MSC_VER
        char_set_const_iterator = alias::lower_bound( char_set, 'A' )
        ,
        CTTL_LAMBDA_ASSERT( char_set_const_iterator == alias::begin( char_set ) )
        ,
        char_set_const_iterator = alias::upper_bound( char_set, 'A' )
        ,
        CTTL_LAMBDA_ASSERT( char_set_const_iterator == alias::end( char_set ) )

        ).evaluate();

    return 0;
}
