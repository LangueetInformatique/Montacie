// sample code: number2words.cpp
// demonstrates mutability of the substring being parsed

//#define NDEBUG    // define before assert.h to stop assertions from being compiled 
//#define CTTL_TRACE_EVERYTHING
#include <iostream>

#include "cttl/cttl.h"

using namespace cttl;

struct numeric_parser {
    static size_t find_number( edge<>& edge_ )
    {
        return (
            entity( isdigit )
            &
            rule( numeric_parser::event_number )

        ).find( edge_ );
    }

    static size_t event_number( edge<>& edge_ ) //const
    {
        static const char* numbers[] = {
            "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
            "ten", "eleven", "twelve",
            "thir", "four", "fif", "six", "seven", "eigh", "nine"
        };

        // for details see http://www.straightdope.com/mailbag/mgazilli.html
        static const char* big_numbers[] = {
            "hundred", // has 2 zeros
            "thousand", // has 3 zeros
            "million", // has 6 zeros
            "billion", // has 9 zeros
            "trillion", // has 12 zeros
            "quadrillion", // has 15 zeros
            "quintillion", // has 18 zeros
            "sextillion", // has 21 zeros
            "septillion", // has 24 zeros
            "octillion", // has 27 zeros
            "nonillion", // has 30 zeros
            "decillion", // has 33 zeros
            "undecillion", // has 36 zeros
            "duodecillion", // has 39 zeros
            "tredecillion", // has 42 zeros
            "quattuordecillion", // has 45 zeros
            "quindecillion", // has 48 zeros
            "sexdecillion", // has 51 zeros
            "septendecillion", // has 54 zeros
            "octodecillion", // has 57 zeros
            "novemdecillion", // has 60 zeros
            "vigintillion", // has 63 zeros
            "\"gazillion\" "
        };

        int number_length = edge_.length();
        if ( number_length == 1 ) { // single digit
            edge_.text( numbers[ edge_.first[ 0 ] - '0' ] );
            return edge_.first.offset();
        }

        for ( int pos = 0; pos < number_length; pos += 3 ) {
            // for every triplet of numbers:

            size_t gazillion = 0;
            if ( pos && !( pos % 3 ) ) {
                // add a "gazillion" suffix
                gazillion = pos / 3;
                if ( gazillion >= sizeof( big_numbers ) / sizeof( char* ) )
                    gazillion = sizeof( big_numbers ) / sizeof( char* ) - 1;
            }

            if ( pos + 1 == number_length ) {   // single digit left
                if ( edge_.second[ -pos - 1 ] > '0' ) {
                    if ( gazillion ) {
                        edge_.second.insert_stay( "\x20" );
                        edge_.second.insert_stay( big_numbers[ gazillion ] );
                        gazillion = 0;
                    }

                    edge_.second.insert_stay( "\x20" );
                    edge_.second.insert_stay( numbers[ edge_.second[ -pos - 1 ] - '0' ] );
                }
                break;
            }

            // process pair of digits 00-99
            if ( edge_.second[ -pos - 2 ] == '1' ) {
                if ( gazillion ) {
                    edge_.second.insert_stay( "\x20" );
                    edge_.second.insert_stay( big_numbers[ gazillion ] );
                    gazillion = 0;
                }
                // teen and pre-teen number: process both digits
                edge_.second.insert_stay( "\x20" );
                if ( edge_.second[ -pos - 1 ] > '2' )
                    edge_.second.insert_stay( "teen" );

                edge_.second.insert_stay( numbers[ 10 + edge_.second[ -pos - 1 ] - '0' ] );

            } else {
                if ( edge_.second[ -pos - 1 ] > '0' ) {
                    if ( gazillion ) {
                        edge_.second.insert_stay( "\x20" );
                        edge_.second.insert_stay( big_numbers[ gazillion ] );
                        gazillion = 0;
                    }
                    // process right-side digit, 1-9
                    edge_.second.insert_stay( "\x20" );
                    edge_.second.insert_stay( numbers[ edge_.second[ -pos - 1 ] - '0' ] );
                }
                
                // process left-side digit
                if ( edge_.second[ -pos - 2 ] == '2' ) {        // twenty
                    if ( gazillion ) {
                        edge_.second.insert_stay( "\x20" );
                        edge_.second.insert_stay( big_numbers[ gazillion ] );
                        gazillion = 0;
                    }

                    edge_.second.insert_stay( "\x20" );
                    edge_.second.insert_stay( "twenty" );

                } else if ( edge_.second[ -pos - 2 ] > '0' ) {  // thirty, "fourty", ..., ninety
                    if ( gazillion ) {
                        edge_.second.insert_stay( "\x20" );
                        edge_.second.insert_stay( big_numbers[ gazillion ] );
                        gazillion = 0;
                    }

                    edge_.second.insert_stay( "\x20" );
                    edge_.second.insert_stay( "ty" );
                    edge_.second.insert_stay( numbers[ 10 + edge_.second[ -pos - 2 ] - '0' ] );
                }
            }

            if ( ( pos + 3 <= number_length ) && ( edge_.second[ -pos - 3 ] > '0' ) ) {
                if ( gazillion ) {
                    edge_.second.insert_stay( "\x20" );
                    edge_.second.insert_stay( big_numbers[ gazillion ] );
                    gazillion = 0;
                }

                // hundred-digit present
                edge_.second.insert_stay( "\x20" );
                edge_.second.insert_stay( big_numbers[ 0 ] );   // "hundred"
                edge_.second.insert_stay( "\x20" );
                edge_.second.insert_stay( numbers[ edge_.second[ -pos - 3 ] - '0' ] );
            }
        }

        edge_.text( "" );
        return edge_.first.offset();
    }

    static bool parse( edge<>& substr_ )
    {
        while ( find_number( substr_ ) != std::string::npos )
            ;
        return !substr_.length();
    }
};

int main(int argc, char* argv[])
{
    if ( argc != 2 ) {
        std::cout
            << "usage: on the command line,\nenter text to convert numbers to words"
            << std::endl
            ;
        return 1;
    }

    std::string inp( argv[ 1 ] );
    edge<> substring( inp );
    if ( !numeric_parser::parse( substring ) ) {
        std::cout << "*** parser failed ***";
        return 1;

    } else {
        std::cout
            << inp
            << std::endl;
            ;
    }

    return 0;
}
