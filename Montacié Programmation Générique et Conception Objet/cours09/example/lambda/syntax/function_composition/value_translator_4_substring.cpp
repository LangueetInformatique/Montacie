// value_translator_4_substring.cpp
// Program demonstrates value translator for CTTL substring.

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    std::string inp = "456";
    const_edge<> substring( inp );
    const_edge<>& edge_ref = substring;
    int var = 0;
    (
        ++( scalar( &var )^atoi^edge_ref )
    ).evaluate();
    assert( var == 456 );
    return 0;
}
