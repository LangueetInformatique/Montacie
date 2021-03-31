// kleene_star_vs_deref.cpp
// Program demonstrates usage of Kleene star and C++ dereference operator.

#define CTTL_TRACE_EVERYTHING

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    std::vector< int > vect;
    std::string inp = "abc";
    const_edge<> substring( inp );
    size_t result = (
        symbol( "abc" )
        +
        **scalar( action(
            &vect,
            std::mem_fun( &std::vector< int >::size )
        ))
    ).match( substring );

    assert( result == 0 );
    assert( substring.first.offset() == inp.length() );

    return 0;
}
