// sample code: mutable_substring.cpp
// demonstrates cttl concept of a mutable substring

//#define NDEBUG    // must appear before assert.h is included to stop assertions from being compiled 
//#define CTTL_TRACE_EVERYTHING

#include <iostream>
#include "cttl/cttl.h"

using namespace cttl;

struct digit_parser {

    static size_t rule_digit( edge<>& edge_ )
    {
        return (
            +(
                first( isdigit )
                &
                rule( digit_parser::event_digit )
            )
        ).match( edge_ );
    }

    static size_t event_digit( edge<>& edge_ )
    {
        // a single digit is found
        static const char* digits[] = {
            "zero;", "one;", "two;", "three;", "four;",
            "five;", "six;", "seven;", "eight;", "nine;"
        };

        size_t digit = edge_.first[ 0 ] - '0';
        assert( digit < ( sizeof( digits ) / sizeof( char ) ) );
        edge_.text( digits[ digit ] );
        return edge_.second.offset();
    }
};

int main(int argc, char* argv[])
{
    if ( argc == 1 ) {
        std::cout
            << "Usage: on the command line, enter a "
            << std::endl
            << "number to convert its digits to words,"
            << std::endl
            << "for example:"
            << std::endl
            << '\t'
            << argv[ 0 ]
            << " 123"
            << std::endl
            ;
        return 1;
    }

    std::string inp = argv[ 1 ];
    edge<> substring( inp );
    if ( digit_parser::rule_digit( substring ) == std::string::npos ) {
        std::cout
            << "*** error *** no digits found at the beginning of the input"
            << std::endl
            ;
        return 1;
    }

    std::cout
        << inp
        << std::endl
        ;
    return 0;
}
