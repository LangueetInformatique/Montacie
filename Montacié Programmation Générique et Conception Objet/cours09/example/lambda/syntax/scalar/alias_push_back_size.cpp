// alias_push_back_size.cpp
// Program demonstrates scalar primitives used with helper
// functions alias::push_back and alias::size.

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    // create scalar lambda containing an integer:
    lambda< size_t >::scalar var;

    // create reference scalar for vector:
    std::vector< int > vect;
    lambda< std::vector< int > >::scalar_reference refvect( &vect );

    (
        alias::push_back( &refvect, 7 ) // vect.push_back( 7 )
        ,
        var = alias::size( refvect )    // var = vect.size()
    ).evaluate();

    assert( vect.back() == 7 );

    return 0;
}
