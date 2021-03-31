// stl_container.cpp
// Program demonstrates access to STL containers:
// std::vector< int > and std::stack< std::string >.

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    lambda< std::vector< int >::size_type >::scalar var( 3 );
    lambda< std::vector< int > >::scalar vect;
    
    (
        alias::push_back( &vect, 7 )
        ,
        var = alias::size( vect )
    ).evaluate();

    assert( var.top() == 1 );
    assert( vect.top()[ 0 ] == 7 );

    std::stack< std::string > str_stack;
    std::string inp = "hello, stack!";
    edge<> substring( inp );
    (
        scalar( &str_stack ) = scalar( std::string( "one" ) )
        ,
        scalar( &str_stack ) = scalar( &substring )
    ).evaluate();

    assert( str_stack.size() == 2 );

    return 0;
}
