// node_edge_alias.cpp
// Program illustrates access to cttl::node and cttl::edge
// via alias helper functions.

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    std::string inp = "hello!";
    edge<> inp_substr( inp );
    lambda< edge<> >::scalar_reference substring( &inp_substr );
    lambda< node<> >::scalar_reference inp_first( &inp_substr.first );
    lambda< node<> >::scalar_reference inp_second( &inp_substr.second );

    ( CTTL_LAMBDA_ASSERT(
        alias::identity( inp_first, substring.top().second ) != 0
        )
        ).evaluate();

    // line
    ( CTTL_LAMBDA_ASSERT(
        alias::line( inp_first ) == scalar( size_t( 1 ) ) )
        ).evaluate();

    // node::insert_go, insert_stay
    (   alias::insert_go( &inp_second, std::string( "one" ) ),
        alias::insert_stay( &inp_second, std::string( "two" ) )
        ).evaluate();

    ( CTTL_LAMBDA_ASSERT(
        alias::text( substring ) == scalar( std::string( "hello!one" ) ) )
        ).evaluate();

    // length
    ( CTTL_LAMBDA_ASSERT(
        scalar( std::string( "hello!one" ).length() ) == alias::length( substring ) )
        ).evaluate();

    // text_toupper
    ( alias::text_toupper( &substring )
        ).evaluate();

    ( CTTL_LAMBDA_ASSERT(
        alias::text( substring ) == scalar( std::string( "HELLO!ONE" ) ) )
        ).evaluate();

    // text_swap
    edge<> edge_tail = inp_substr;
    ( alias::text_swap( &substring, &edge_tail )
        ).evaluate();

    ( CTTL_LAMBDA_ASSERT(
        scalar( std::string( "HELLO!ONE" ) ) == alias::text( scalar( &edge_tail ) ) )
        ).evaluate();


    return 0;
}
