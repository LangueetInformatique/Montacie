// node_token_boundary.cpp
// Program searches for a group of digits in the input
// and makes additional space valiadation at the upper boundary
// of the matching token.

//#define CTTL_TRACE_EVERYTHING

#include <iostream>

#include "cttl/cttl.h"
#include "lambda/lambda.h"

int main()
{
    using namespace cttl;

    std::string inp = "ABC123 456";
    const_edge<> substring( inp );
    const_edge<> token = substring;

    lambda< char >::scalar ch; // temp character value
    lambda< node<> >::scalar_reference character( &token.first );

    size_t result =
        (
            // Non-terminal search:
            !!
            (
                // The grammar expression:
                token( entity( isdigit ) )
                +
                // Boolean switch parser:
                (
                    ch = character[ -1 ], 
                    *scalar(
                        CTTL_STATIC_ACTION(
                            std::ptr_fun( &isspace ),
                            ch.top()
                        )
                    )
                )
            )
    ).match( substring );

    assert( result != std::string::npos );
    assert( token == "456" );

    return 0;
}
