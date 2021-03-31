// lambda_double.cpp
// Program demonstrates lambda expression (delayed expression),
// and delayed evaluation.

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

double amount = 0.0;

template< typename LambdaT >
void f( LambdaT lambda_ )
{
    assert( amount == 0.0 );
    lambda_.evaluate(); // delayed evaluation
    assert( amount == 5.0 );
}

int main(/*int argc, char* argv[]*/)
{
    f( scalar( &amount ) = scalar( 5.0 ) ); // delayed expression "amount = 5.0"
    return 0;
}
