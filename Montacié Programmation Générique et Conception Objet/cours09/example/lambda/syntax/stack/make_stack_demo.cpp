// make_stack_demo.cpp
// Program demonstrates usage of make_stack()
// helper function for the lambda stack primitive.

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

template< typename StackPrimitiveT >
typename StackPrimitiveT::value_T
auto_Cpp0X(
           StackPrimitiveT stack_,
           typename StackPrimitiveT::value_T value_
           )
{
    stack_.push( value_ );
    return stack_.top();
}

int main(/*int argc, char* argv[]*/)
{
    cttl::lambda< int >::scalar var = auto_Cpp0X( make_stack( 0 ), 5678 );
    assert( var.top() == 5678 );
    return 0;
}
