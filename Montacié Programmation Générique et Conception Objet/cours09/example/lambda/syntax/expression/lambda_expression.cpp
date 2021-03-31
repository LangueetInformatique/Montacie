// lambda_expression.cpp
// Program demonstrates lambda expression (delayed expression),
// and delayed evaluation.

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

template< typename LambdaT >
void f( LambdaT lambda_ )
{
    lambda_.evaluate(); // delayed evaluation
}

void g()
{
    int var = 0;
    f( scalar( &var ) = 5 ); // delayed expression "var = 5"
    assert( var == 5 );
}

int main(/*int argc, char* argv[]*/)
{
    g();
    return 0;
}
