// value_translators_mix.cpp
// Program demonstrates edge translator from text to int,
// and access to std::vector iterator.

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    std::string inp = "123 456";
    const_edge< policy_space<> > substring( inp );
    const_edge<> data = substring;
    std::vector< std::string > vect_str;

    std::vector< size_t > vect_int;
    std::vector< size_t >::iterator size_it = vect_int.begin();
    lambda< std::vector< size_t > >::scalar_reference size_vect_scalar( &vect_int );

    std::back_insert_iterator< std::vector< size_t > > back_ins( vect_int );
    lambda< std::back_insert_iterator< std::vector< size_t > > >::scalar it( &back_ins );

    size_t result = (
        +(
            data( entity( isdigit ) )
            +
            *(
                *it++ = ++( scalar( 0 )^atoi^"100" ),     // 100
                *it++ = ++( scalar( 0 )^atoi^data ),      // 123 456
                *it++ = ++( scalar( 0 )^vect_str^"300" ), // 300
                *it++ = ++( scalar( 0 )^vect_str^data ),  // 123 456
                *it++ = ( scalar( 0 )^vect_str = std::string( "400" ) ) // 400
            )
        )
    ).match( substring );

    assert( result != std::string::npos );
    // vect_str: 300 123 400   300 456 400
    assert( vect_str.at( 0 ) == "300" );
    assert( vect_str.at( 1 ) == "123" );
    assert( vect_str.at( 2 ) == "400" );
    assert( vect_str.at( 3 ) == "300" );
    assert( vect_str.at( 4 ) == "456" );
    assert( vect_str.at( 5 ) == "400" );

    // vect_int: 100 123 0 1 2   100 456 3 4 5
    assert( vect_int.at( 0 ) == 100 );
    assert( vect_int.at( 1 ) == 123 );
    assert( vect_int.at( 2 ) == 0   );
    assert( vect_int.at( 3 ) == 1   );
    assert( vect_int.at( 4 ) == 2   );

    assert( vect_int.at( 5 ) == 100 );
    assert( vect_int.at( 6 ) == 456 );
    assert( vect_int.at( 7 ) == 3   );
    assert( vect_int.at( 8 ) == 4   );
    assert( vect_int.at( 9 ) == 5   );

    return 0;
}
