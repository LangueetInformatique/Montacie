// value_translator_4_literal_constant.cpp
// Program demonstrates value translator for literal constant.

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    double var = 0.0;
    (
        ++( scalar( &var )^atof^"3.14159" )
    ).evaluate();
    assert( var == 3.14159 );
    return 0;
}
