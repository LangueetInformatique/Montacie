// closure_translator.cpp
// Program demonstrates CTTL_MEMBER_ACTION helper macro.

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

struct digit_parser {
    std::vector< std::string > vect_digit_names;
    lambda< char >::scalar sdigit;

    digit_parser()
        : vect_digit_names( 2 )
    {
        vect_digit_names[ 0 ] = "Zero";
        vect_digit_names[ 1 ] = "One";
    }

    std::string get_digit_name( char digit_ ) const
    {
        assert( digit_ == 0 || digit_ == 1 );
        return vect_digit_names[ digit_ ];
    }

    template< typename SubstrT >
    size_t grammar( SubstrT& edge_ )
    {
        return (
            *(
                first( isdigit )
                &
                *(
                    // calculate digit that got parsed:
                    sdigit = scalar( &edge_.first )[ 0 ] - '0',
                    // replace digit name:
                    ++(
                        scalar( &edge_ )
                        ^
                        CTTL_MEMBER_ACTION(
                            *this,
                            std::mem_fun( &digit_parser::get_digit_name ),
                            sdigit.top()
                        )
                    )
                    /*
                    // The same result using assignment:
                    scalar( &edge_ ) = 
                        *scalar( CTTL_MEMBER_ACTION(
                            *this,
                            std::mem_fun( &digit_parser::get_digit_name ),
                            sdigit.top()
                        )
                    )
                    */
                )
            )
        ).match( edge_ );
    }

};

int main(/*int argc, char* argv[]*/)
{
    std::string inp = "0110";
    typedef edge< policy_space<> > substr_T;
    substr_T substring( inp );
    typedef size_t ( digit_parser::* rule_T ) ( substr_T& );

    // invoke grammar production using CTTL function adaptor:
    digit_parser parser;
    size_t result = 
        (
            CTTL_MEMBER_RULE( parser, rule_T( &digit_parser::grammar< substr_T > ) )
        ).match( substring );

    assert( result != std::string::npos );

    return 0;
}
