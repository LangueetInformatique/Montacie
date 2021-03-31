// stream_output_iterator.cpp
// Program demonstrates the usage of stream output iterator adaptor.

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include <iostream>
#include <iterator> 
#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    lambda< std::ostream_iterator< int > >::scalar
        output( std::ostream_iterator< int >( std::cout, "<-output" ) );
    ( *output++ = scalar( 8 ) ).evaluate();
    ( *output = scalar( 9 ) ).evaluate();
    ( ++output ).evaluate();
    ( *output = scalar( 10 ), output++ ).evaluate();

    return 0;
}
