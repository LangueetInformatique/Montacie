// closure_toupper.cpp
// Program demonstrates conversion to uppercase using
// closure (delayed function call.)

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    std::string inp = "abc";
    const_edge<> substring( inp );
    lambda< char >::scalar ch; // temp character value
    lambda< node<> >::scalar character( substring.first );

    size_t result = (
        *(  // for each character,
            character.top()( first( isalpha ) ) // match single character
            +
            *(
                ch = character[ 0 ],            // get character value
                character[ 0 ] = *scalar(
                    CTTL_STATIC_ACTION(         // convert to UPPERCASE
                        std::ptr_fun( &toupper ),
                        ch.top()
                    )
                )
            )
        )
    ).match( substring );

    assert( result != std::string::npos );
    assert( inp == "ABC" );

    return 0;
}
