// sample code: word_count.cpp
// demonstrates stateful parser and lexer implementation.

//#define NDEBUG    // must appear before assert.h is included to stop assertions from being compiled 
//#define CTTL_TRACE_EVERYTHING

#include <iostream>
#include "cttl/cttl.h"

using namespace cttl;

template< typename SubstrT >
struct base_parser {
    // parser defines two kinds of substrings:
    typedef SubstrT substr_T;
    typedef typename SubstrT::strict_edge_T strict_edge_T;

    // semantic actions:
    size_t count_words( strict_edge_T& ) const
    {
        return 0;
    }

    size_t replace_words( strict_edge_T& ) const
    {
        return 0;
    }
};

template< typename SubstrT >
struct parser : public base_parser< SubstrT > {

    // parser defines two kinds of substrings:
    typedef SubstrT substr_T;
    typedef typename SubstrT::strict_edge_T strict_edge_T;

    int count;

    parser( int count_ )
        :
    count( count_ )
    {
    }

    // semantic actions:
    size_t count_words( strict_edge_T& substr_ )
    {
        ++count;
        return substr_.second.offset();
    }

    size_t replace_words( strict_edge_T& substr_ )
    {
        substr_ = "<WORD/>";
        //substr_ = std::string( "<WORD/>" );
        //substr_.text( "<WORD/>" );
        return substr_.second.offset();
    }

};

template< typename ParserT >
struct lexer : public ParserT {

    // lexer defines two kinds of substrings:
    typedef typename ParserT::substr_T substr_T;
    typedef typename substr_T::strict_edge_T strict_edge_T;

    // lexer static data:
    std::set< std::string > keywords;

    lexer( int count_ = 0 )
        :
    ParserT( count_ )
    {
        // populate list of keywords:
        keywords.insert( "abc" );
        keywords.insert( "xyz" );
    }

    // grammar rule definitions
    size_t start( substr_T& substr_ )
    {
        return (
            // at least one word should be present,
            // but not a keyword:
            +(
                // invoke grammar rule
                CTTL_RULE( lexer< ParserT >::word )
                &
                // invoke semantic action
                CTTL_RULE( ParserT::count_words )
                &
                // invoke another semantic action
                CTTL_RULE( ParserT::replace_words )
            )

            ).match( substr_ )
            ;
    }

    size_t word( substr_T& substr_ ) const
    {
        // a word can anything made of alphabetic
        // characters, but not a keyword:
        return (

                isalpha
                -
                begin( keywords )

            ).match( substr_ );
    }
};


int main(int argc, char* argv[])
{
    if ( argc == 1 ) {
        std::cout
            << "Usage: on command the line, enter some words to count, for example,"
            << std::endl
            << '\t'
            << argv[ 0 ]
            << " one two three"
            << std::endl
            ;

        return 1;
    }

    // construct input string from the command line arguments:
    std::string inp;
    string_array2string( inp, &argv[ 1 ], ' ' );

    // construct substring to be parsed:
    //typedef const_edge< policy_space<> > substr_T;
    typedef edge< policy_space<> > substr_T;

    substr_T substring( inp );

    // construct the parser:
    lexer< parser< substr_T > > word_parser;

    // count words:
    if ( word_parser.start( substring ) != std::string::npos ) {
        std::cout << "Word count: " << word_parser.count << std::endl;

    } else {
        std::cout << "*** parser failed ***" << std::endl;
        return 1;
    }

    std::cout << "Input: " << inp << std::endl;
    return 0;
}
