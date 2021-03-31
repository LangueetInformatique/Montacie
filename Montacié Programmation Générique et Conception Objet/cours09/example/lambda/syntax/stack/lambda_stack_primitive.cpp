// lambda_stack_primitive.cpp
// Program demonstrates functionality of the lambda stack primitive.

#define CTTL_TRACE_RULES // automatically turns lambda tracing on #include

#include "cttl/cttl.h" 
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    lambda< int >::scalar Variable;     // instantiate integer scalar
    lambda< size_t >::scalar StackSize; // instantiate size_t scalar
    lambda< int >::stack Stack;         // instantiate std::stack< int >

    assert( Stack.size() == 0 );        // no elements exist so far
    Stack.push( 3 );                    // push new element
    //<top>3<bottom>
    assert( Stack.top() == 3 );         // verify result
    Stack.top() = 2;                    // write access to top element 
    //<top>2<bottom>
    assert( Stack.top() == 2 );         // verify result

    // overloaded stack operators              
    (
        Stack = 4,                      // Stack.push( 4 )
        //<top>4,2<bottom>
        Variable = *Stack,              // Variable = Stack.top()
        *Stack = 5,                     // Stack.top() = 5
        //<top>5,2<bottom>
        StackSize = Stack--,            // Variable = Stack.size (), Stack.pop()
        //<top>2<bottom>                // stack size before pop:
        CTTL_LAMBDA_ASSERT( StackSize == scalar( 2u ) ),
        StackSize = +Stack              // StackSize = Stack.size()
        //<top>2<bottom>
        ).evaluate();

    assert( StackSize.top() == 1 );
    assert( Stack.size() == 1 );
    assert( Stack.top() == 2 );

    return 0;
}
