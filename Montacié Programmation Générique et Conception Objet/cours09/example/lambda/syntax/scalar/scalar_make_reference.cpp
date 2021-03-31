// scalar_make_reference.cpp
// Program demonstrates usage of make_reference()
// member function for scalar lambda primitives.

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

template< typename ScalarRefT >
void push_data( ScalarRefT depository_, typename ScalarRefT::value_T value_ )
{
    depository_.push( value_ );
}

int main(/*int argc, char* argv[]*/)
{
    cttl::lambda< int >::scalar var = 1234;
    assert( var.top() == 1234 );
    push_data( var.make_reference(), 5678 );
    assert( var.top() == 5678 );
    push_data( var.make_reference().make_reference(), 9999 );
    assert( var.top() == 9999 );
    return 0;
}
