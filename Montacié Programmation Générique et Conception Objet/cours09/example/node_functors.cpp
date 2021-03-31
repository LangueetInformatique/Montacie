// sample code: node_functors.cpp
// demonstrates cttl::node_insert_go and cttl::node_insert_stay classes.

//#define NDEBUG    // must appear before assert.h is included to stop assertions from being compiled 
//#define CTTL_TRACE_EVERYTHING

#include <iostream>
#include "cttl/cttl.h"
#include "cttl/node_functors.h"

using namespace cttl;

struct parser {
    std::vector< node<> > start_nodes;
    std::vector< node<> > finish_nodes;

    // semantic actions:
    size_t accumulate_words( const_edge<>& edge_ )
    {
        // for each word that was found, remember starting and
        // ending positions in the corresponding vectors:
        start_nodes.push_back( edge_.first );
        finish_nodes.push_back( edge_.second );
        return edge_.second.offset();
    }
};

template< typename ParserT >
struct lexer : public ParserT {

    size_t start( const_edge< policy_space<> >& substr_ )
    {
        return (
                +( isalpha & rule( *this, &ParserT::accumulate_words ) )
        ).match( substr_ )
        ;
    }
};


int main(int argc, char* argv[])
{
    if ( argc == 1 ) {
        std::cout
            << "Usage: on command the line, enter some words to process, for example,"
            << std::endl
            << '\t'
            << argv[ 0 ]
            << " abc def ghi"
            << std::endl
            ;

        return 1;
    }

    // construct input string from the command line arguments:
    std::string inp;
    string_array2string( inp, &argv[ 1 ], ' ' );

    // construct substring to be parsed:
    const_edge< policy_space<> > substring( inp );

    // construct the parser:
    lexer< parser > word_parser;

    // count words:
    if ( word_parser.start( substring ) != std::string::npos ) {
        std::cout << "Input: " << inp << std::endl;

        // Modify input text by inserting word markers:
        std::for_each(
            word_parser.start_nodes.begin(),
            word_parser.start_nodes.end(),
            node_insert_go<>( "<WORD>" )
            );

        std::for_each(
            word_parser.finish_nodes.begin(),
            word_parser.finish_nodes.end(),
            node_insert_stay<>( "</WORD>" )
            );

        std::cout << "Output: " << inp << std::endl;

    } else {
        std::cout << "*** parser failed ***" << std::endl;
        return 1;
    }

    return 0;
}
