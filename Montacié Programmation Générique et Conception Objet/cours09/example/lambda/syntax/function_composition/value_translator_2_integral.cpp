// value_translator_2_integral.cpp
// Program demonstrates sequence translator to integral type,
// obtained as a position of the value inserted into
// a sequence container.

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    std::string inp = "XYZ";
    edge<> inp_substr( inp );
    lambda< edge<> >::scalar_reference substring( &inp_substr );
    size_t var = 0;
    std::vector< std::string > vect;
    (
        ++( scalar( &var )^vect^substring.top() ),
        CTTL_LAMBDA_ASSERT( scalar( &vect )[ 0 ] == scalar( std::string( "XYZ" ) ) ),
        CTTL_LAMBDA_ASSERT( scalar( &var ) == 0u ),
        alias::text( &substring, std::string( "ABC" ) ),
        CTTL_LAMBDA_ASSERT( alias::text( substring ) == scalar( std::string( "ABC" ) ) ),
        ++( scalar( &var )^vect^substring.top() ),
        CTTL_LAMBDA_ASSERT( scalar( &vect )[ 1 ] == scalar( std::string( "ABC" ) ) ),
        CTTL_LAMBDA_ASSERT( scalar( &var ) == 1u )
    ).evaluate();
    assert( var == 1 );
    assert( vect[ 0 ] == "XYZ" );
    assert( vect[ 1 ] == "ABC" );
    return 0;
}
