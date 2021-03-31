// stack_as_scalar.cpp
// Program illustrates access to std::stack via lambda scalar primitive.

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    // instantiate integer scalar:
    lambda< int >::scalar Variable;
    // instantiate std::stack< int >:
    lambda< std::stack< int > >::scalar Scalar;

    (
        alias::push( &Scalar, 4 ),
        //<top>4<bottom>
        Variable = alias::top( Scalar ),
        alias::top( &Scalar ) = 5,
        //<top>5<bottom>
        Variable = alias::top( Scalar ),
        alias::pop( &Scalar ),
        //<top><bottom>
        CTTL_LAMBDA_ASSERT( Variable == 5 ),
        Variable = alias::size( Scalar )
        ).evaluate();

    assert( Variable.top() == 0 );

    return 0;
}
