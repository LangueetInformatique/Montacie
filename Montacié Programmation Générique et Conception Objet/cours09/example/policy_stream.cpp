// sample code: policy_stream.cpp

//#define CTTL_TRACE_EVERYTHING //define to turn tracing on

#include <iostream>
#include "cttl/cttl.h"

using namespace cttl;

struct policy_strict_stream : public policy_default
{
    typedef policy_strict_stream strict_policy_T;

    template< typename SubstrT >
    static size_t match( SubstrT& substr_ )
    {
        // Non-greedy by design - does nothing but appends new data:
        if ( std::cin.good() ) {
            if ( !substr_.length() ) {
            substr_.parent().append( 1, std::cin.get() );
            substr_.second.go_eof();
            }
        } else {
            // No more data from the stream is available:
            return std::string::npos;
        }
        return substr_.first.offset();
    }
}; // struct policy_relaxed_stream


struct policy_relaxed_stream
    :
    public policy_strict_stream,
    public policy_space< flag_follow_space >
{
    typedef policy_strict_stream strict_policy_T;

    template< typename SubstrT >
    static size_t match( SubstrT& substr_ )
    {
        // non-greedy implementation:
        size_t ungreedy_offset = substr_.first.offset();
        policy_space< flag_follow_space >::match( substr_ );
        while ( !substr_.length() ) {
            if ( policy_strict_stream::match( substr_ ) == std::string::npos ) {
                // No more data from the stream is available:
                return std::string::npos;
            }
            policy_space< flag_follow_space >::match( substr_ );
        }
        return ungreedy_offset;
    }
}; // struct policy_relaxed_stream


template< typename SubstrT >
struct lexer {

    static size_t alpha( SubstrT& substr_ )
    {
        return
            (
                +first( isalpha )             // Get as many alpha chars as you can,
                &                             // and, in strict mode,
                ( entity( isalpha ) + end() ) // verify that no white space is present.

            ).match( substr_ );
    }

    static size_t digit3( SubstrT& substr_ )
    {
        static const std::pair< int, int > TOKEN_LENGTH( 3, std::string::npos );
        return
            (
                // Matches exactly 3 digits:
                ( symbol() + TOKEN_LENGTH )   // Get any three characters
                &                             // and, in strict mode,
                ( entity( isdigit ) + end() ) // verify that they are 3 digits.

            ).match( substr_ );
    }

    static size_t hex48( SubstrT& substr_ )
    {
        static const std::pair< int, int > TOKEN_LENGTH( 4, 8 );
        return
            (
                // Matches 4 to 8 hex digits:
                ( first( isxdigit ) + TOKEN_LENGTH )
                &                              // and, in strict mode,
                ( entity( isxdigit ) + end() ) // verify that they are hex digits.

            ).match( substr_ );
    }

    static size_t start( SubstrT& substr_ )
    {
        return
            (
                CTTL_STATIC_RULE( &lexer< SubstrT >::digit3 )
                +
                CTTL_STATIC_RULE( &lexer< SubstrT >::alpha )
                +
                CTTL_STATIC_RULE( &lexer< SubstrT >::hex48 )

            ).match( substr_ );
    }

};// lexer


int main()
{
    std::string inp;
    typedef const_edge< policy_relaxed_stream > substr_T;
    substr_T substring( inp );
    const_edge<> fragment = substring;
    std::cout
        << "Enter 3-digit number, 1+ alpha chars, 4-8 hex digits, and semicolon:"
        << std::endl
        << "123 xyz 123abc ;"
        << std::endl
        << "\t\t(Any mismatch causes program to exit.)"
        << std::endl
        ;
    while(
        (
            fragment(
                CTTL_STATIC_RULE( &lexer< substr_T >::start )
            )
            +
            symbol( ';' )
        )
        .match( substring )
        !=
        std::string::npos
        )
    {
        std::cout << "Good match: /" << fragment << "/ -- try again:" << std::endl;
    }

    if ( substring.length() ) {
        std::cout << "Mismatch: " << substring << " -- exiting." << std::endl;
    }

    return 0;
}
