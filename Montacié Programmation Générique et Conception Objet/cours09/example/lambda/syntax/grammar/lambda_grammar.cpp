// lambda_grammar.cpp
// Program parses tokens and inserts them into the stack.
// Demonstrates lambda grammar, stack, kleene star, and epsilon parser.

//#define CTTL_TRACE_EVERYTHING

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

size_t parse(
             const_edge< policy_space<> >& substr_,
             std::stack< std::string >& str_stack_
             )
{
    return
        (
            *(
                entity( isalpha )
                &
                *(
                    scalar( &str_stack_ ) = scalar( &substr_ )
                )
            )
        ).match( substr_ )
        ;
}

int main(/*int argc, char* argv[]*/)
{
    std::stack< std::string > str_stack;
    std::string inp = "abc def ghi";
    const_edge< policy_space<> > substring( inp );
    if ( parse( substring, str_stack ) == std::string::npos ) {
        std::cout << "*** parser failed ***" << std::endl;
        return 1;
    }
    assert( str_stack.size() == 3 );
    assert( str_stack.top() == "ghi" );
    return 0;
}
