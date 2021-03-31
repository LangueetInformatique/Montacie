// arithmetic_interpreter.cpp

//#define NDEBUG    // define before assert.h to stop assertions from being compiled 
//#define CTTL_TRACE_EVERYTHING //define to turn tracing on
//#define CTTL_TRACE_RULES  //define to turn light tracing on

#include <iterator>    // needed for ostream_iterator
#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

#include "example/lambda/arithmetic_interpreter/lexer.h"
#include "example/lambda/arithmetic_interpreter/interpreter.h"

int main(int argc, char* argv[])
{
    assert( argc > 1 );
    std::string inp;
    string_array2string( inp, &argv[ 1 ], ' ' );
    const_edge<> value( inp );

    std::vector< int > tree( 1 );   // reserve one element for the header node
    std::vector< double > vector_doubles;

    // construct substring to be parsed:
    typedef const_edge< policy_space<> > substr_T;

    substr_T substring = value;

    calc_lexer< substr_T > lexer(
        tree,
        value,
        vector_doubles
        );

    if ( lexer.grammar( substring ) ) {

        interpreter inter( tree, vector_doubles );

        std::cout
            << std::endl
            << "result: "
            << inter.non_terminal( tree[ 0 ] )
            << std::endl
            ;

    } else {
        std::cout << "\t\t *** PARSER FAILED *** " << std::endl;
        return 1;
    }

    return 0;

} // main
