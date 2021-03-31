// sample code: functor.cpp
// demonstrates lexer function object invoked by the grammar rule.

#include "cttl/cttl.h"

using namespace cttl;

class lexer : public std::unary_function< const_edge<>, size_t >{
    char m_char;

public:
    lexer( char char_ )
        :   m_char( char_ )
    {}

    size_t operator() ( const_edge<>& edge_ ) const
    {
        return symbol( m_char ).match( edge_ );
    }
};


int main()
{
    std::string inp = "ZZZA";
    const_edge<> substring( inp );
    char letter = 'Z';

    // Construct grammar rule for a single character:
    lexer grammar( letter );
    
    // The following statement combines grammar production
    // named "grammar" with single character 'A':
    size_t result = ( +rule( grammar ) + 'A' ).match( substring );
    assert( result == 0 );             // assert match at the beginning of substring
    assert( substring.length() == 0 ); // make sure substring is fully consumed
    return 0;
}
