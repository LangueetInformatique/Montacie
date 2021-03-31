// operator_xor.cpp
// Program demonstrates overloaded operator_xor() helper function.

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include <iostream>
#include <iterator>
#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    lambda< std::ostream_iterator< int > >::scalar
        output( std::ostream_iterator< int >( std::cout, "<-result " ) );
    (
        *output++ = operator_xor( scalar( 0 ), scalar( 0 ) ),
        *output++ = operator_xor( scalar( 0 ), scalar( 1 ) ),
        *output++ = operator_xor( scalar( 1 ), scalar( 0 ) ),
        *output++ = operator_xor( scalar( 1 ), scalar( 1 ) )
    ).evaluate();

    return 0;
}

/*
Output:

( = ( ^  0  0 )(*-> ? )0<-result ( -> ? )++),
( = ( ^  0  1 )(*-> ? )1<-result ( -> ? )++),
( = ( ^  1  0 )(*-> ? )1<-result ( -> ? )++),
( = ( ^  1  1 )(*-> ? )0<-result ( -> ? )++)

*/
