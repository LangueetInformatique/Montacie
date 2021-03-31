// alias_text.cpp
// Program demonstrates alias::text() helper and std::string manipulation.

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    std::string inp = "hello";
    edge<> inp_substr( inp );
    lambda< edge<> >::scalar_reference substring( &inp_substr );
    lambda< std::string >::scalar str;

    // text, write
    ( alias::text( &substring, std::string( "bye" ) )
        ).evaluate();

    // text, read
    ( str = alias::text( substring )
        ).evaluate();

    ( CTTL_LAMBDA_ASSERT( str == scalar( std::string( "bye" ) ) )
        ).evaluate();

    assert( inp == "bye" );

    // basic_string push_back
    ( alias::basic_string::push_back( &str, 'X' )
        ).evaluate();

    ( CTTL_LAMBDA_ASSERT( str == scalar( std::string( "byeX" ) ) )
        ).evaluate();

    // append
    ( alias::append( &str, std::string( "YZ" ) )
        ).evaluate();

    ( CTTL_LAMBDA_ASSERT( str == scalar( std::string( "byeXYZ" ) ) )
        ).evaluate();

    // assign
    ( alias::assign( &str, std::string( "hi" ) )
        ).evaluate();

    ( CTTL_LAMBDA_ASSERT( str == scalar( std::string( "hi" ) ) )
        ).evaluate();
    // compare
    ( CTTL_LAMBDA_ASSERT( !alias::compare( str, std::string( "hi" ) ) )
        ).evaluate();

    // length
    ( CTTL_LAMBDA_ASSERT( scalar( std::string( "hi" ).length() ) == alias::length( str ) )
        ).evaluate();
        
    return 0;
}
