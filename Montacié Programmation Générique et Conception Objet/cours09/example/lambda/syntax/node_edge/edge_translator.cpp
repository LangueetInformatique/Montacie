// edge_translator.cpp
// Program demonstrates edge translator from text to int,
// and access to std::vector iterator.

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    std::string inp( "123" );
    const_edge< policy_space<> > substring( inp );
    const_edge<> data = substring;
    std::vector< int > vect( 1 );
    lambda< std::vector< int > >::scalar_reference scalar_v( &vect );
    lambda< std::vector< int >::iterator >::scalar it;
    size_t result = (
        data( entity( isdigit ) )
        +
        *(
            *alias::begin( &scalar_v ) = 4,
            it = alias::begin( &scalar_v ),
            *it = ++( scalar( 0 )^atoi^data ) // edge translator
        )
    ).match( substring );

    assert( result != std::string::npos );
    assert( vect[ 0 ] == 123 );

    (
        *it = *alias::begin( &scalar_v ),  // ok
        //*it = *alias::begin( scalar_v ), // will not compile
        *alias::begin( &scalar_v ) = 4
    ).evaluate();
    assert( vect[ 0 ] == 4 );
    return 0;
}
